{$ifndef UACPI_BAREBONES_MODE}

(*
 * Install a Notify() handler to a device node.
 * A handler installed to the root node will receive all notifications, even if
 * a device already has a dedicated Notify handler.
 * 'handler_context' is passed to the handler on every invocation.
 *)
function uacpi_install_notify_handler(
    node: Puacpi_namespace_node;
    handler: Tuacpi_notify_handler;
    handler_context: Tuacpi_handle
): Tuacpi_status; cdecl; external;

function uacpi_uninstall_notify_handler(
    node: Puacpi_namespace_node;
    handler: Tuacpi_notify_handler
): Tuacpi_status; cdecl; external;

{$endif UACPI_BAREBONES_MODE}
