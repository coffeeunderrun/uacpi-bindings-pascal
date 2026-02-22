unit uacpi;

{$packrecords C}

interface

{$I status.inc}
{$I types.inc}
{$I log.inc}

{$I acpi.inc}
{$I tables.inc}

(*
 * Set up early access to the table subsystem. What this means is:
 * - uacpi_table_find() and similar API becomes usable before the call to
 *   uacpi_initialize().
 * - No kernel API besides logging and map/unmap will be invoked at this stage,
 *   allowing for heap and scheduling to still be fully offline.
 * - The provided 'temporary_buffer' will be used as a temporary storage for the
 *   internal metadata about the tables (list, reference count, addresses,
 *   sizes, etc).
 * - The 'temporary_buffer' is replaced with a normal heap buffer allocated via
 *   uacpi_kernel_alloc() after the call to uacpi_initialize() and can therefore
 *   be reclaimed by the kernel.
 *
 * The approximate overhead per table is 56 bytes, so a buffer of 4096 bytes
 * yields about 73 tables in terms of capacity. uACPI also has an internal
 * static buffer for tables, "UACPI_STATIC_TABLE_ARRAY_LEN", which is configured
 * as 16 descriptors in length by default.
 *
 * This function is used to initialize the barebones mode, see
 * UACPI_BAREBONES_MODE in config.h for more information.
 *)
function uacpi_setup_early_table_access(
  temporary_buffer: Pointer;
  buffer_size: uacpi_size
): uacpi_status; cdecl; external;

(*
 * Reset the global uACPI state by freeing all internally allocated data
 * structures & resetting any global variables. After this call, uACPI must be
 * re-initialized from scratch to be used again.
 *
 * This is called by uACPI automatically if a fatal error occurs during a call
 * to uacpi_initialize/uacpi_namespace_load etc. in order to prevent accidental
 * use of partially uninitialized subsystems.
 *)
procedure uacpi_state_reset; cdecl; external;

implementation

end.
