if (NOT CMAKE_SCRIPT_MODE_FILE)

	# Create tests that run this CMakeLists.txt file as a script (below).
	add_test(NAME TestManualPDFLinks
		COMMAND ${CMAKE_COMMAND}
			-DPROJECT_SOURCE_DIR=${PROJECT_SOURCE_DIR}
			-DTestManualPDFLinks=ON
			-DVuo_VERSION=${Vuo_VERSION}
			-P ${CMAKE_CURRENT_LIST_FILE}
	)
	set_property(TEST TestManualPDFLinks PROPERTY SKIP_REGULAR_EXPRESSION TestManualPDFLinksSkipped)
	add_test(NAME TestAlex
		COMMAND ${CMAKE_COMMAND}
			-DPROJECT_SOURCE_DIR=${PROJECT_SOURCE_DIR}
			-DTestAlex=ON
			-DVuo_VERSION=${Vuo_VERSION}
			-P ${CMAKE_CURRENT_LIST_FILE}
	)

else()

	# See TestNodes for tests of deprecated nodes in documentation compositions.
	# See TestVuoEditor for tests of menu items in VuoManual.txt.

	if (TestManualPDFLinks)
		# Ensure the links in the PDF manual aren't broken.

		# Test the pre-compressed (VuoPackagePDFManual) version,
		# since pdf-link-checker can't parse the compressed version.
		set(PDF ../../documentation/VuoManual-en-solarized.pdf)

		if (NOT EXISTS ${PDF})
			message("TestManualPDFLinksSkipped: ${PDF} doesn't exist")
			return()
		endif()

		execute_process(
			COMMAND pdf-link-checker ${PDF}
			OUTPUT_VARIABLE out
			ERROR_VARIABLE out)
		string(REPLACE "\n" ";" out "${out}")
		cmake_policy(SET CMP0007 NEW)
		string(JOIN "|" regexes
			# Ignore errors due to this not-yet-released Vuo version.
			api.vuo.org/${Vuo_VERSION}/.*404
			doc.vuo.org/${Vuo_VERSION}/.*404
			# Ignore sites that block our link checker.
			leapmotion.com.*403
			503:.Service.Unavailable
			# Ignore temporary failures.
			Reason:.unknown
		)
		list(FILTER out EXCLUDE REGEX ${regexes})
		list(SORT out)
		list(LENGTH out outLen)
		if (outLen GREATER 0)
			string(REPLACE ";" "\n" out "${out}")
			message(FATAL_ERROR "error: Found broken links in the PDF manual:\n${out}")
		endif()
	endif()

	if (TestAlex)
		# Check for potentially harmful language.
		execute_process(
			WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
			COMMAND /usr/bin/env PATH=/opt/homebrew/bin:/usr/local/bin alex --quiet --why .
			RESULT_VARIABLE ret
		)
		if (ret)
			message(FATAL_ERROR "error: alex reported issues.")
		endif()
	endif()

endif()
