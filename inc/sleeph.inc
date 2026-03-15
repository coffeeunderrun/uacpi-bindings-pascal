{$ifndef UACPI_BAREBONES_MODE}

(*
 * Set the firmware waking vector in FACS.
 *
 * 'addr32' is the real mode entry-point address
 * 'addr64' is the protected mode entry-point address
 *)
function uacpi_set_waking_vector(
    addr32: Tuacpi_phys_addr; addr64: Tuacpi_phys_addr
): Tuacpi_status; cdecl; external; {$ifdef UACPI_REDUCED_HARDWARE}inline;{$else}external;{$endif}

type
  Tuacpi_sleep_state = (
    UACPI_SLEEP_STATE_S0 = 0,
    UACPI_SLEEP_STATE_S1,
    UACPI_SLEEP_STATE_S2,
    UACPI_SLEEP_STATE_S3,
    UACPI_SLEEP_STATE_S4,
    UACPI_SLEEP_STATE_S5,
    UACPI_SLEEP_STATE_MAX = UACPI_SLEEP_STATE_S5
  );

(*
 * Prepare for a given sleep state.
 *)
function uacpi_prepare_for_sleep_state(state: Tuacpi_sleep_state): Tuacpi_status; cdecl; external;

(*
 * Enter the given sleep state after preparation.
 *)
function uacpi_enter_sleep_state(state: Tuacpi_sleep_state): Tuacpi_status; cdecl; external;

(*
 * Prepare to leave the given sleep state.
 *)
function uacpi_prepare_for_wake_from_sleep_state(state: Tuacpi_sleep_state): Tuacpi_status; cdecl; external;

(*
 * Wake from the given sleep state.
 *)
function uacpi_wake_from_sleep_state(state: Tuacpi_sleep_state): Tuacpi_status; cdecl; external;

(*
 * Attempt reset via the FADT reset register.
 *)
function uacpi_reboot: Tuacpi_status; cdecl; external;

{$endif UACPI_BAREBONES_MODE}
