VuoTest(NAME TestVuoCompilerBitcodeGenerator
	SOURCE TestVuoCompilerBitcodeGenerator.cc
	GMALLOC_ELIGIBLE
)
target_link_libraries(TestVuoCompilerBitcodeGenerator
	PRIVATE
	TestVuoCompiler
)
