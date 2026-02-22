{$ifdef UACPI_OVERRIDE_ARCH_HELPERS}

{$I uacpi_arch_helpers.inc}

{$else UACPI_OVERRIDE_ARCH_HELPERS}

type
  Tuacpi_cpu_flags = Cardinal;
  Tuacpi_thread_id = Pointer;

const
  UACPI_THREAD_ID_NONE = Tuacpi_thread_id(-1);

{$endif UACPI_OVERRIDE_ARCH_HELPERS}
