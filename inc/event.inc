{$ifndef UACPI_BAREBONES_MODE}

type
  Tuacpi_fixed_event = (
    UACPI_FIXED_EVENT_TIMER_STATUS = 1,
    UACPI_FIXED_EVENT_POWER_BUTTON,
    UACPI_FIXED_EVENT_SLEEP_BUTTON,
    UACPI_FIXED_EVENT_RTC,
    UACPI_FIXED_EVENT_MAX = UACPI_FIXED_EVENT_RTC
  );

function uacpi_install_fixed_event_handler(
  event: Tuacpi_fixed_event; handler: Tuacpi_interrupt_handler; user: Tuacpi_handle
): Tuacpi_status; {$ifdef UACPI_REDUCED_HARDWARE}inline;{$else}external;{$endif}

function uacpi_uninstall_fixed_event_handler(
  event: Tuacpi_fixed_event
): Tuacpi_status; {$ifdef UACPI_REDUCED_HARDWARE}inline;{$else}external;{$endif}

(*
 * Enable/disable a fixed event. Note that the event is automatically enabled
 * upon installing a handler to it.
 *)
function uacpi_enable_fixed_event(event: Tuacpi_fixed_event): Tuacpi_status; {$ifdef UACPI_REDUCED_HARDWARE}inline;{$else}external;{$endif}

function uacpi_disable_fixed_event(event: Tuacpi_fixed_event): Tuacpi_status; {$ifdef UACPI_REDUCED_HARDWARE}inline;{$else}external;{$endif}

function uacpi_clear_fixed_event(event: Tuacpi_fixed_event): Tuacpi_status; {$ifdef UACPI_REDUCED_HARDWARE}inline;{$else}external;{$endif}

type
  Tuacpi_event_info = (
    // Event is enabled in software
    UACPI_EVENT_INFO_ENABLED = (1 shl 0),

    // Event is enabled in software (only for wake)
    UACPI_EVENT_INFO_ENABLED_FOR_WAKE = (1 shl 1),

    // Event is masked
    UACPI_EVENT_INFO_MASKED = (1 shl 2),

    // Event has a handler attached
    UACPI_EVENT_INFO_HAS_HANDLER = (1 shl 3),

    // Hardware enable bit is set
    UACPI_EVENT_INFO_HW_ENABLED = (1 shl 4),

    // Hardware status bit is set
    UACPI_EVENT_INFO_HW_STATUS = (1 shl 5)
  );

function uacpi_fixed_event_info(
    event: Tuacpi_fixed_event; out out_info: Tuacpi_event_info
): Tuacpi_status; {$ifdef UACPI_REDUCED_HARDWARE}inline;{$else}external;{$endif}

function uacpi_gpe_info(
   gpe_device: Puacpi_namespace_node; idx: Tuacpi_u16;
   out out_info: Tuacpi_event_info
): Tuacpi_status; {$ifdef UACPI_REDUCED_HARDWARE}inline;{$else}external;{$endif}

// Set if the handler wishes to reenable the GPE it just handled
const
  UACPI_GPE_REENABLE = (1 shl 7);

type
  Tuacpi_gpe_handler = function(
    ctx: Tuacpi_handle; gpe_device: Puacpi_namespace_node; idx: Tuacpi_u16
  ): Tuacpi_interrupt_ret; cdecl;

  Tuacpi_gpe_triggering = (
    UACPI_GPE_TRIGGERING_LEVEL = 0,
    UACPI_GPE_TRIGGERING_EDGE = 1,
    UACPI_GPE_TRIGGERING_MAX = UACPI_GPE_TRIGGERING_EDGE
  );

function uacpi_gpe_triggering_to_string(triggering: Tuacpi_gpe_triggering): Puacpi_char; external;

(*
 * Installs a handler to the provided GPE at 'idx' controlled by device
 * 'gpe_device'. The GPE is automatically disabled & cleared according to the
 * configured triggering upon invoking the handler. The event is optionally
 * re-enabled (by returning UACPI_GPE_REENABLE from the handler)
 *
 * NOTE: 'gpe_device' may be null for GPEs managed by \_GPE
 *)
function uacpi_install_gpe_handler(
  gpe_device: Puacpi_namespace_node; idx: Tuacpi_u16;
  triggering: Tuacpi_gpe_triggering; handler: Tuacpi_gpe_handler; ctx: Tuacpi_handle
): Tuacpi_status; {$ifdef UACPI_REDUCED_HARDWARE}inline;{$else}external;{$endif}

(*
 * Installs a raw handler to the provided GPE at 'idx' controlled by device
 * 'gpe_device'. The handler is dispatched immediately after the event is
 * received, status & enable bits are untouched.
 *
 * NOTE: 'gpe_device' may be null for GPEs managed by \_GPE
 *)
function uacpi_install_gpe_handler_raw(
  gpe_device: Puacpi_namespace_node; idx: Tuacpi_u16;
  triggering: Tuacpi_gpe_triggering; handler: Tuacpi_gpe_handler; ctx: Tuacpi_handle
): Tuacpi_status; {$ifdef UACPI_REDUCED_HARDWARE}inline;{$else}external;{$endif}

function uacpi_uninstall_gpe_handler(
  gpe_device: Puacpi_namespace_node; idx: Tuacpi_u16; handler: Tuacpi_gpe_handler
): Tuacpi_status; {$ifdef UACPI_REDUCED_HARDWARE}inline;{$else}external;{$endif}

(*
 * Marks the GPE 'idx' managed by 'gpe_device' as wake-capable. 'wake_device' is
 * optional and configures the GPE to generate an implicit notification whenever
 * an event occurs.
 *
 * NOTE: 'gpe_device' may be null for GPEs managed by \_GPE
 *)
function uacpi_setup_gpe_for_wake(
  gpe_device: Puacpi_namespace_node; idx: Tuacpi_u16;
  wake_device: Puacpi_namespace_node
): Tuacpi_status; {$ifdef UACPI_REDUCED_HARDWARE}inline;{$else}external;{$endif}

(*
 * Mark a GPE managed by 'gpe_device' as enabled/disabled for wake. The GPE must
 * have previously been marked by calling uacpi_gpe_setup_for_wake. This
 * function only affects the GPE enable register state following the call to
 * uacpi_gpe_enable_all_for_wake.
 *
 * NOTE: 'gpe_device' may be null for GPEs managed by \_GPE
 *)
function uacpi_enable_gpe_for_wake(
  gpe_device: Puacpi_namespace_node; idx: Tuacpi_u16
): Tuacpi_status; {$ifdef UACPI_REDUCED_HARDWARE}inline;{$else}external;{$endif}

function uacpi_disable_gpe_for_wake(
  gpe_device: Puacpi_namespace_node; idx: Tuacpi_u16
): Tuacpi_status; {$ifdef UACPI_REDUCED_HARDWARE}inline;{$else}external;{$endif}

(*
 * Finalize GPE initialization by enabling all GPEs not configured for wake and
 * having a matching AML handler detected.
 *
 * This should be called after the kernel power managment subsystem has
 * enumerated all of the devices, executing their _PRW methods etc., and
 * marking those it wishes to use for wake by calling uacpi_setup_gpe_for_wake
 * or uacpi_mark_gpe_for_wake.
 *)
function uacpi_finalize_gpe_initialization: Tuacpi_status; {$ifdef UACPI_REDUCED_HARDWARE}inline;{$else}external;{$endif}

(*
 * Enable/disable a general purpose event managed by 'gpe_device'. Internally
 * this uses reference counting to make sure a GPE is not disabled until all
 * possible users of it do so. GPEs not marked for wake are enabled
 * automatically so this API is only needed for wake events or those that don't
 * have a corresponding AML handler.
 *
 * NOTE: 'gpe_device' may be null for GPEs managed by \_GPE
 *)
function uacpi_enable_gpe(
  gpe_device: Puacpi_namespace_node; idx: Tuacpi_u16
): Tuacpi_status; {$ifdef UACPI_REDUCED_HARDWARE}inline;{$else}external;{$endif}

function uacpi_disable_gpe(
  gpe_device: Puacpi_namespace_node; idx: Tuacpi_u16
): Tuacpi_status; {$ifdef UACPI_REDUCED_HARDWARE}inline;{$else}external;{$endif}

(*
 * Clear the status bit of the event 'idx' managed by 'gpe_device'.
 *
 * NOTE: 'gpe_device' may be null for GPEs managed by \_GPE
 *)
function uacpi_clear_gpe(
  gpe_device: Puacpi_namespace_node; idx: Tuacpi_u16
): Tuacpi_status; {$ifdef UACPI_REDUCED_HARDWARE}inline;{$else}external;{$endif}

(*
 * Suspend/resume a general purpose event managed by 'gpe_device'. This bypasses
 * the reference counting mechanism and unconditionally clears/sets the
 * corresponding bit in the enable registers. This is used for switching the GPE
 * to poll mode.
 *
 * NOTE: 'gpe_device' may be null for GPEs managed by \_GPE
 *)
function uacpi_suspend_gpe(
  gpe_device: Puacpi_namespace_node; idx: Tuacpi_u16
): Tuacpi_status; {$ifdef UACPI_REDUCED_HARDWARE}inline;{$else}external;{$endif}

function uacpi_resume_gpe(
  gpe_device: Puacpi_namespace_node; idx: Tuacpi_u16
): Tuacpi_status; {$ifdef UACPI_REDUCED_HARDWARE}inline;{$else}external;{$endif}

(*
 * Finish handling the GPE managed by 'gpe_device' at 'idx'. This clears the
 * status registers if it hasn't been cleared yet and re-enables the event if
 * it was enabled before.
 *
 * NOTE: 'gpe_device' may be null for GPEs managed by \_GPE
 *)
function uacpi_finish_handling_gpe(
  gpe_device: Puacpi_namespace_node; idx: Tuacpi_u16
): Tuacpi_status; {$ifdef UACPI_REDUCED_HARDWARE}inline;{$else}external;{$endif}

(*
 * Hard mask/umask a general purpose event at 'idx' managed by 'gpe_device'.
 * This is used to permanently silence an event so that further calls to
 * enable/disable as well as suspend/resume get ignored. This might be necessary
 * for GPEs that cause an event storm due to the kernel's inability to properly
 * handle them. The only way to enable a masked event is by a call to unmask.
 *
 * NOTE: 'gpe_device' may be null for GPEs managed by \_GPE
 *)
function uacpi_mask_gpe(
  gpe_device: Puacpi_namespace_node; idx: Tuacpi_u16
): Tuacpi_status; {$ifdef UACPI_REDUCED_HARDWARE}inline;{$else}external;{$endif}

function uacpi_unmask_gpe(
  gpe_device: Puacpi_namespace_node; idx: Tuacpi_u16
): Tuacpi_status; {$ifdef UACPI_REDUCED_HARDWARE}inline;{$else}external;{$endif}

(*
 * Disable all GPEs currently set up on the system.
 *)
function uacpi_disable_all_gpes: Tuacpi_status; {$ifdef UACPI_REDUCED_HARDWARE}inline;{$else}external;{$endif}

(*
 * Enable all GPEs not marked as wake. This is only needed after the system
 * wakes from a shallow sleep state and is called automatically by wake code.
 *)
function uacpi_enable_all_runtime_gpes: Tuacpi_status; {$ifdef UACPI_REDUCED_HARDWARE}inline;{$else}external;{$endif}

(*
 * Enable all GPEs marked as wake. This is only needed before the system goes
 * to sleep is called automatically by sleep code.
 *)
function uacpi_enable_all_wake_gpes: Tuacpi_status; {$ifdef UACPI_REDUCED_HARDWARE}inline;{$else}external;{$endif}

(*
 * Install/uninstall a new GPE block, usually defined by a device in the
 * namespace with a _HID of ACPI0006.
 *)
function uacpi_install_gpe_block(
    gpe_device: Puacpi_namespace_node; address: Tuacpi_u64;
    address_space: Tuacpi_address_space; num_registers: Tuacpi_u16;
    irq: Tuacpi_u32
): Tuacpi_status; {$ifdef UACPI_REDUCED_HARDWARE}inline;{$else}external;{$endif}

function uacpi_uninstall_gpe_block(
    gpe_device: Puacpi_namespace_node
): Tuacpi_status; {$ifdef UACPI_REDUCED_HARDWARE}inline;{$else}external;{$endif}

{$endif UACPI_BAREBONES_MODE}
