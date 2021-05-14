	export	FooOffset
	import	foo

	area	.rdata, data, readonly

FooOffset dcd foo
    reloc 0xF ; IMAGE_REL_ARM_SECREL in winnt.h

	end
