VuoCompileLibraries(
	VuoAppLaunch.m
)
target_sources(vuo.app.libraries PRIVATE
	VuoAppLaunch.h
)

VuoCompileNodes(
	vuo.app.keepSystemAwake.m
	vuo.app.launch.c
	vuo.app.openDocument.c
	vuo.app.openUrl.c
	vuo.app.shell.c
	vuo.app.stopComposition.c
)

VuoNodeSet()
