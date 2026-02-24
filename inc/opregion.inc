{$ifndef UACPI_BAREBONES_MODE}

(*
 * Install an address space handler to a device node.
 * The handler is recursively connected to all of the operation regions of
 * type 'space' underneath 'device_node'. Note that this recursion stops as
 * soon as another device node that already has an address space handler of
 * this type installed is encountered.
 *)
function uacpi_install_address_space_handler(
    device_node: Puacpi_namespace_node;
    space: Tuacpi_address_space;
    handler: Tuacpi_region_handler;
    handler_context: Tuacpi_handle
): Tuacpi_status; cdecl; external;

(*
 * Uninstall the handler of type 'space' from a given device node.
 *)
function uacpi_uninstall_address_space_handler(
    device_node: Puacpi_namespace_node;
    space: Tuacpi_address_space
): Tuacpi_status; cdecl; external;

(*
 * Execute _REG(space, ACPI_REG_CONNECT) for all of the opregions with this
 * address space underneath this device. This should only be called manually
 * if you want to register an early handler that must be available before the
 * call to uacpi_namespace_initialize().
 *)
function uacpi_reg_all_opregions(
    device_node: Puacpi_namespace_node;
    space: Tuacpi_address_space
): Tuacpi_status; cdecl; external;

{$endif UACPI_BAREBONES_MODE}
