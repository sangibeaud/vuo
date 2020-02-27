/**
 * @file
 * VuoEventLoop implementation.
 *
 * @copyright Copyright © 2012–2020 Kosada Incorporated.
 * This code may be modified and distributed under the terms of the MIT License.
 * For more information, see https://vuo.org/license.
 */

#include "VuoEventLoop.h"
#include "VuoLog.h"
#include "VuoCompositionState.h"

#ifndef NS_RETURNS_INNER_POINTER
#define NS_RETURNS_INNER_POINTER
#endif
#import <AppKit/AppKit.h>

#include <dlfcn.h>

/**
 * Is the current thread the main thread?
 */
static bool VuoEventLoop_isMainThread(void)
{
	static void **mainThread;
	static dispatch_once_t once = 0;
	dispatch_once(&once, ^{
		mainThread = (void **)dlsym(RTLD_SELF, "VuoApp_mainThread");
		if (!mainThread)
			mainThread = (void **)dlsym(RTLD_DEFAULT, "VuoApp_mainThread");

		if (!mainThread)
		{
			VUserLog("Error: Couldn't find VuoApp_mainThread.");
			VuoLog_backtrace();
			exit(1);
		}

		if (!*mainThread)
		{
			VUserLog("Error: VuoApp_mainThread isn't set.");
			VuoLog_backtrace();
			exit(1);
		}
	});

	return *mainThread == (void *)pthread_self();
}

/**
 * Handles one or more blocks or application events (e.g., keypresses, mouse moves, window state changes).
 *
 * If an NSApp is available:
 *
 *    - If `mode` is VuoEventLoop_WaitIndefinitely, waits until an NSEvent arrives, processes the event, and returns.
 *    - If `mode` is VuoEventLoop_RunOnce, processes an NSEvent (if one is ready), and returns.
 *
 * If there's no NSApp, executes the CFRunLoop:
 *
 *    - If `mode` is VuoEventLoop_WaitIndefinitely, returns when the CFRunLoop exits.
 *    - If `mode` is VuoEventLoop_RunOnce, returns immediately after a single CFRunLoop iteration.
 *
 * In either case, when `mode` is VuoEventLoop_WaitIndefinitely, @ref VuoEventLoop_break will cause this function to return immediately.
 *
 * @threadMain
 */
void VuoEventLoop_processEvent(VuoEventLoopMode mode)
{
	if (!VuoEventLoop_isMainThread())
	{
		VUserLog("Error: VuoEventLoop_processEvent must be called from the main thread.");
		VuoLog_backtrace();
		exit(1);
	}

	NSAutoreleasePool *pool = [NSAutoreleasePool new];

	// Can't just use `NSApp` directly, since the composition might not link to AppKit.
	id *nsAppGlobal = (id *)dlsym(RTLD_DEFAULT, "NSApp");

	// Support running either with or without an NSApplication.
	if (nsAppGlobal && *nsAppGlobal)
	{
		// http://www.cocoawithlove.com/2009/01/demystifying-nsapplication-by.html
		// https://stackoverflow.com/questions/6732400/cocoa-integrate-nsapplication-into-an-existing-c-mainloop

		// When the composition is ready to stop, it posts a killswitch NSEvent,
		// to ensure that this function returns immediately.
		NSEvent *event = [*nsAppGlobal nextEventMatchingMask:NSAnyEventMask
												   untilDate:(mode == VuoEventLoop_WaitIndefinitely ? [NSDate distantFuture] : [NSDate distantPast])
													  inMode:NSDefaultRunLoopMode
													 dequeue:YES];
		[*nsAppGlobal sendEvent:event];
		[*nsAppGlobal updateWindows];
	}
	else
	{
		// This blocks until CFRunLoopStop() is called.
		// When the composition is ready to stop (or switch into NSApplication mode), it calls CFRunLoopStop().
		if (mode == VuoEventLoop_WaitIndefinitely)
			CFRunLoopRun();
		else
			CFRunLoopRunInMode(kCFRunLoopDefaultMode, 0, false);
	}

	[pool drain];
}

/**
 * Interrupts @ref VuoEventLoop_processEvent while it is waiting.
 *
 * @threadAny
 */
void VuoEventLoop_break(void)
{
	// Can't just use `NSApp` directly, since the composition might not link to AppKit.
	id *nsAppGlobal = (id *)dlsym(RTLD_DEFAULT, "NSApp");

	if (nsAppGlobal && *nsAppGlobal)
	{
		// Send an event, to ensure VuoEventLoop_processEvent()'s call to `nextEventMatchingMask:…` returns immediately.
		// -[NSApplication postEvent:atStart:] must be called from the main thread.
		dispatch_async(dispatch_get_main_queue(), ^{
			NSEvent *killswitch = [NSEvent otherEventWithType:NSApplicationDefined
								   location:NSMakePoint(0,0)
							  modifierFlags:0
								  timestamp:0
							   windowNumber:0
									context:nil
									subtype:0
									  data1:0
									  data2:0];
			[*nsAppGlobal postEvent:killswitch atStart:NO];
		});
	}
	else
		// https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/Multithreading/RunLoopManagement/RunLoopManagement.html#//apple_ref/doc/uid/10000057i-CH16-SW26
		// says this can be called from any thread.
		CFRunLoopStop(CFRunLoopGetMain());
}

/**
 * Interrupts @ref VuoEventLoop_processEvent if it's currently blocking, so that it can process NSEvents next time it's invoked.
 *
 * @threadAny
 */
void VuoEventLoop_switchToAppMode(void)
{
	// https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/Multithreading/RunLoopManagement/RunLoopManagement.html#//apple_ref/doc/uid/10000057i-CH16-SW26
	// says this can be called from any thread.
	CFRunLoopStop(CFRunLoopGetMain());
}

/**
 * Returns false if the app is currently waiting on user input in a modal dialog or a window sheet.
 *
 * @threadMain
 */
bool VuoEventLoop_mayBeTerminated(void)
{
	if (!VuoEventLoop_isMainThread())
	{
		VUserLog("Error: VuoEventLoop_mayBeTerminated must be called from the main thread.");
		VuoLog_backtrace();
		exit(1);
	}

	// Can't just use `NSApp` directly, since the composition might not link to AppKit.
	id *nsAppGlobal = (id *)dlsym(RTLD_DEFAULT, "NSApp");
	if (!nsAppGlobal || !*nsAppGlobal)
		return true;

	if ([*nsAppGlobal modalWindow])
		return false;

	for (NSWindow *window in [*nsAppGlobal windows])
		if ([window attachedSheet])
			return false;

	return true;
}

/**
 * Returns the Dispatch attribute for `QOS_CLASS_USER_INTERACTIVE`.
 *
 * Apple's documentation says:
 * "The use of this QOS class should be limited to […] view drawing, animation, etc."
 *
 * @threadAny
 */
dispatch_queue_attr_t VuoEventLoop_getDispatchInteractiveAttribute(void)
{
	static dispatch_queue_attr_t attr = 0;
	static dispatch_once_t once = 0;
	dispatch_once(&once, ^{
		attr = dispatch_queue_attr_make_with_qos_class(DISPATCH_QUEUE_SERIAL, QOS_CLASS_USER_INTERACTIVE, 0);
	});
	return attr;
}

/**
 * Installs SIGINT and SIGTERM handlers, to cleanly shut down the composition.
 *
 * @threadMain
 */
void VuoEventLoop_installSignalHandlers(void)
{
	typedef void (*vuoStopCompositionType)(struct VuoCompositionState *);
	vuoStopCompositionType vuoStopComposition = (vuoStopCompositionType)dlsym(RTLD_SELF, "vuoStopComposition");
	if (!vuoStopComposition)
		vuoStopComposition = (vuoStopCompositionType)dlsym(RTLD_DEFAULT, "vuoStopComposition");
	if (!vuoStopComposition)
	{
		VUserLog("Warning: Couldn't find vuoStopComposition symbol; not installing clean-shutdown signal handlers.");
		return;
	}

	// Disable default signal handlers so libdispatch can catch them.
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);

	// Use libdispatch to handle signals instead of `signal`/`sigaction`
	// since `vuoStopComposition()` uses non-signal-safe functions such as `malloc`.
	void (^stop)(void) = ^{
		vuoStopComposition(NULL);
	};
	dispatch_source_t sigintSource  = dispatch_source_create(DISPATCH_SOURCE_TYPE_SIGNAL, SIGINT,  0, dispatch_get_main_queue());
	dispatch_source_t sigquitSource = dispatch_source_create(DISPATCH_SOURCE_TYPE_SIGNAL, SIGQUIT, 0, dispatch_get_main_queue());
	dispatch_source_t sigtermSource = dispatch_source_create(DISPATCH_SOURCE_TYPE_SIGNAL, SIGTERM, 0, dispatch_get_main_queue());
	dispatch_source_set_event_handler(sigintSource,  stop);
	dispatch_source_set_event_handler(sigquitSource, stop);
	dispatch_source_set_event_handler(sigtermSource, stop);
	dispatch_resume(sigintSource);
	dispatch_resume(sigquitSource);
	dispatch_resume(sigtermSource);
}

/**
 * Disable "App Nap" since even if our timers are set to `DISPATCH_TIMER_STRICT`,
 * the OS still prevents the process from running smoothly while taking a nap.
 * https://b33p.net/kosada/node/12685
 *
 * @threadMain
 */
void VuoEventLoop_disableAppNap(void)
{
	id activityToken = [[NSProcessInfo processInfo] performSelector:@selector(beginActivityWithOptions:reason:)
		withObject: (id)((0x00FFFFFFULL | (1ULL << 20)) & ~(1ULL << 14)) // NSActivityUserInitiated & ~NSActivitySuddenTerminationDisabled
		withObject: @"Many Vuo compositions need to process input and send output even when the app's window is not visible."];

	[activityToken retain];
}
