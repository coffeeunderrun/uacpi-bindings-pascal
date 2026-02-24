{$ifndef UACPI_BAREBONES_MODE}

function uacpi_install_fixed_event_handler(
  event: Tuacpi_fixed_event; handler: Tuacpi_interrupt_handler; user: Tuacpi_handle
): Tuacpi_status;
begin
  result := UACPI_STATUS_COMPILED_OUT;
end;

function uacpi_uninstall_fixed_event_handler(
  event: Tuacpi_fixed_event
): Tuacpi_status;
begin
  result := UACPI_STATUS_COMPILED_OUT;
end;

function uacpi_enable_fixed_event(event: Tuacpi_fixed_event): Tuacpi_status;
begin
  result := UACPI_STATUS_COMPILED_OUT;
end;

function uacpi_disable_fixed_event(event: Tuacpi_fixed_event): Tuacpi_status;
begin
  result := UACPI_STATUS_COMPILED_OUT;
end;

function uacpi_clear_fixed_event(event: Tuacpi_fixed_event): Tuacpi_status;
begin
  result := UACPI_STATUS_COMPILED_OUT;
end;

function uacpi_fixed_event_info(
    event: Tuacpi_fixed_event; out out_info: Tuacpi_event_info
): Tuacpi_status;
begin
  result := UACPI_STATUS_COMPILED_OUT;
end;

function uacpi_gpe_info(
   gpe_device: Puacpi_namespace_node; idx: Tuacpi_u16;
   out out_info: Tuacpi_event_info
): Tuacpi_status;
begin
  result := UACPI_STATUS_COMPILED_OUT;
end;

function uacpi_install_gpe_handler(
  gpe_device: Puacpi_namespace_node; idx: Tuacpi_u16;
  triggering: Tuacpi_gpe_triggering; handler: Tuacpi_gpe_handler; ctx: Tuacpi_handle
): Tuacpi_status;
begin
  result := UACPI_STATUS_COMPILED_OUT;
end;

function uacpi_install_gpe_handler_raw(
  gpe_device: Puacpi_namespace_node; idx: Tuacpi_u16;
  triggering: Tuacpi_gpe_triggering; handler: Tuacpi_gpe_handler; ctx: Tuacpi_handle
): Tuacpi_status;
begin
  result := UACPI_STATUS_COMPILED_OUT;
end;

function uacpi_uninstall_gpe_handler(
  gpe_device: Puacpi_namespace_node; idx: Tuacpi_u16; handler: Tuacpi_gpe_handler
): Tuacpi_status;
begin
  result := UACPI_STATUS_COMPILED_OUT;
end;

function uacpi_setup_gpe_for_wake(
  gpe_device: Puacpi_namespace_node; idx: Tuacpi_u16;
  wake_device: Puacpi_namespace_node
): Tuacpi_status;
begin
  result := UACPI_STATUS_COMPILED_OUT;
end;

function uacpi_enable_gpe_for_wake(
  gpe_device: Puacpi_namespace_node; idx: Tuacpi_u16
): Tuacpi_status;
begin
  result := UACPI_STATUS_COMPILED_OUT;
end;

function uacpi_disable_gpe_for_wake(
  gpe_device: Puacpi_namespace_node; idx: Tuacpi_u16
): Tuacpi_status;
begin
  result := UACPI_STATUS_COMPILED_OUT;
end;

function uacpi_finalize_gpe_initialization: Tuacpi_status;
begin
  result := UACPI_STATUS_COMPILED_OUT;
end;

function uacpi_enable_gpe(
  gpe_device: Puacpi_namespace_node; idx: Tuacpi_u16
): Tuacpi_status;
begin
  result := UACPI_STATUS_COMPILED_OUT;
end;

function uacpi_disable_gpe(
  gpe_device: Puacpi_namespace_node; idx: Tuacpi_u16
): Tuacpi_status;
begin
  result := UACPI_STATUS_COMPILED_OUT;
end;

function uacpi_clear_gpe(
  gpe_device: Puacpi_namespace_node; idx: Tuacpi_u16
): Tuacpi_status;
begin
  result := UACPI_STATUS_COMPILED_OUT;
end;

function uacpi_suspend_gpe(
  gpe_device: Puacpi_namespace_node; idx: Tuacpi_u16
): Tuacpi_status;
begin
  result := UACPI_STATUS_COMPILED_OUT;
end;

function uacpi_resume_gpe(
  gpe_device: Puacpi_namespace_node; idx: Tuacpi_u16
): Tuacpi_status;
begin
  result := UACPI_STATUS_COMPILED_OUT;
end;

function uacpi_finish_handling_gpe(
  gpe_device: Puacpi_namespace_node; idx: Tuacpi_u16
): Tuacpi_status;
begin
  result := UACPI_STATUS_COMPILED_OUT;
end;

function uacpi_mask_gpe(
  gpe_device: Puacpi_namespace_node; idx: Tuacpi_u16
): Tuacpi_status;
begin
  result := UACPI_STATUS_COMPILED_OUT;
end;

function uacpi_unmask_gpe(
  gpe_device: Puacpi_namespace_node; idx: Tuacpi_u16
): Tuacpi_status;
begin
  result := UACPI_STATUS_COMPILED_OUT;
end;

function uacpi_disable_all_gpes: Tuacpi_status;
begin
  result := UACPI_STATUS_COMPILED_OUT;
end;

function uacpi_enable_all_runtime_gpes: Tuacpi_status;
begin
  result := UACPI_STATUS_COMPILED_OUT;
end;

function uacpi_enable_all_wake_gpes: Tuacpi_status;
begin
  result := UACPI_STATUS_COMPILED_OUT;
end;

function uacpi_install_gpe_block(
    gpe_device: Puacpi_namespace_node; address: Tuacpi_u64;
    address_space: Tuacpi_address_space; num_registers: Tuacpi_u16;
    irq: Tuacpi_u32
): Tuacpi_status;
begin
  result := UACPI_STATUS_COMPILED_OUT;
end;

function uacpi_uninstall_gpe_block(
    gpe_device: Puacpi_namespace_node
): Tuacpi_status;
begin
  result := UACPI_STATUS_COMPILED_OUT;
end;

{$endif UACPI_BAREBONES_MODE}
