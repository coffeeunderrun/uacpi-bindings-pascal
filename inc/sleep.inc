function uacpi_set_waking_vector(
    addr32: Tuacpi_phys_addr; addr64: Tuacpi_phys_addr
): Tuacpi_status;
begin
  result := UACPI_STATUS_COMPILED_OUT;
end;
