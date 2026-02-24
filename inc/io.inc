{$ifndef UACPI_BAREBONES_MODE}

function uacpi_gas_read(const gas: Pacpi_gas; out value: Tuacpi_u64): Tuacpi_status; cdecl; external;
function uacpi_gas_write(const gas: Pacpi_gas; value: Tuacpi_u64): Tuacpi_status; cdecl; external;

type
  Puacpi_mapped_gas = ^Tuacpi_mapped_gas;
  Tuacpi_mapped_gas = record end;

(*
 * Map a GAS for faster access in the future. The handle returned via
 * 'out_mapped' must be freed & unmapped using uacpi_unmap_gas() when
 * no longer needed.
 *)
function uacpi_map_gas(const gas: Pacpi_gas; out out_mapped: Puacpi_mapped_gas): Tuacpi_status; cdecl; external;
procedure uacpi_unmap_gas(mapped: Puacpi_mapped_gas); cdecl; external;

(*
 * Same as uacpi_gas_{read,write} but operates on a pre-mapped handle for faster
 * access and/or ability to use in critical sections/irq contexts.
 *)
function uacpi_gas_read_mapped(const gas: Puacpi_mapped_gas; out value: Tuacpi_u64): Tuacpi_status; cdecl; external;
function uacpi_gas_write_mapped(const gas: Puacpi_mapped_gas; value: Tuacpi_u64): Tuacpi_status; cdecl; external;

{$endif UACPI_BAREBONES_MODE}
