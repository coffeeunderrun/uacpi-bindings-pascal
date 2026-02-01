unit uacpi;

interface

{$I status.inc}
{$I types.inc}
{$I log.inc}

function uacpi_setup_early_table_access(Buffer: Pointer; Size: uacpi_size): uacpi_status; cdecl; external;

implementation

end.
