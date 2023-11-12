#if defined __has_attribute
#  if __has_attribute (noobfuscate)
#    define ATTR_NOOBFUSCATE __attribute__ ((noobfuscate))
#  else
#    error "noobfuscate attribute not supported"
#  endif
#endif

void ATTR_NOOBFUSCATE my_function(void)
{
    // function implementation
}

void my_functxion (void) __attribute__((noobfuscate));