VuoCompileTypes(
	VuoControlCode.c
	VuoNumberFormat.c
)
target_sources(vuo.text.types PRIVATE
	VuoControlCode.h
	VuoNumberFormat.h
)

VuoCompileGenericNodes(
	vuo.text.split.c
	vuo.text.split.stream.c
)

VuoCompileNodes(
	vuo.text.append.c
	vuo.text.areEqual.c
	vuo.text.case.c
	vuo.text.compare.c
	vuo.text.countCharacters.c
	vuo.text.cut.c
	vuo.text.find.c
	vuo.text.format.number.c
	vuo.text.get.ascii.c
	vuo.text.insert.c
	vuo.text.make.ascii.c
	vuo.text.make.controlCode.c
	vuo.text.populated.c
	vuo.text.removeHtml.c
	vuo.text.replace.c
)

VuoNodeSet()
