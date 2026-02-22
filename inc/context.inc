(*
 * Set the minimum log level to be accepted by the logging facilities. Any logs
 * below this level are discarded and not passed to uacpi_kernel_log, etc.
 *
 * 0 is treated as a special value that resets the setting to the default value.
 *
 * E.g. for a log level of UACPI_LOG_INFO:
 *   UACPI_LOG_DEBUG -> discarded
 *   UACPI_LOG_TRACE -> discarded
 *   UACPI_LOG_INFO -> allowed
 *   UACPI_LOG_WARN -> allowed
 *   UACPI_LOG_ERROR -> allowed
 *)
procedure uacpi_context_set_log_level(log_level: uacpi_log_level); cdecl; external;

(*
 * Enables table checksum validation at installation time instead of first use.
 * Note that this makes uACPI map the entire table at once, which not all
 * hosts are able to handle at early init.
 *)
procedure uacpi_context_set_proactive_table_checksum(enabled: uacpi_bool); cdecl; external;
