	export	FooOffset
	import	foo

	area	.rdata, data, readonly

FooOffset dcd foo
    reloc 8 ; IMAGE_REL_ARM64_SECREL in winnt.h

	end
