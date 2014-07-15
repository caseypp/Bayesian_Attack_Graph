#
# (C) Tenable Network Security, Inc.
#


include("compat.inc");


if (description)
{
  script_id(58321);
  script_version("$Revision: 1.3 $");
  script_cvs_date("$Date: 2012/03/20 14:04:16 $");

  script_bugtraq_id(52359);
  script_osvdb_id(79869);
  script_xref(name:"EDB-ID", value:"18624");
  script_xref(name:"Secunia", value:"47661");

  script_name(english:"2X Client TuxClientSystem ActiveX InstallClient() Method Arbitrary MSI Package Installation");
  script_summary(english:"Checks version of the control");
 
  script_set_attribute(
    attribute:"synopsis",
    value:
"An ActiveX control on the remote Windows host could allow
installation of arbitrary programs."
  );
  script_set_attribute(
    attribute:"description", 
    value:
"The version of the TuxClientSystem ActiveX control, part of the 2X
Client, installed on the remote Windows host is earlier than 10.1
Build 1239.  As such, its 'InstallClient()' method reportedly accepts
a URL to an MSI package and allows installation of an application
without explicit user approval. 

If an attacker can trick an administrator on the affected system into
viewing a malicious HTML document, he could leverage this issue to
install an arbitrary application on the system."
  );
  script_set_attribute(
    attribute:"solution", 
    value:
"Upgrade to 2X Client 10.1 Build 1239 as that is reported to address
the vulnerability."
  );
  script_set_cvss_base_vector("CVSS2#AV:N/AC:M/Au:N/C:C/I:C/A:C");
  script_set_cvss_temporal_vector("CVSS2#E:F/RL:OF/RC:C");
  script_set_attribute(attribute:"exploitability_ease", value:"Exploits are available");
  script_set_attribute(attribute:"exploit_available", value:"true");

  script_set_attribute(attribute:"vuln_publication_date", value:"2012/03/08");
  script_set_attribute(attribute:"patch_publication_date", value:"2012/03/01");
  script_set_attribute(attribute:"plugin_publication_date", value:"2012/03/12");

  script_set_attribute(attribute:"plugin_type", value:"local");
  script_end_attributes();
 
  script_category(ACT_GATHER_INFO);
  script_family(english:"Windows");

  script_copyright(english:"This script is Copyright (C) 2012 Tenable Network Security, Inc.");

  script_dependencies("smb_hotfixes.nasl");
  script_require_keys("SMB/Registry/Enumerated");
  script_require_ports(139, 445);

  exit(0);
}


include("global_settings.inc");
include("misc_func.inc");
include("smb_func.inc");
include("smb_activex_func.inc");


get_kb_item_or_exit("SMB/Registry/Enumerated");
if (activex_init() != ACX_OK) exit(1, "activex_init() failed.");


clsid = "{F5DF8D65-559D-4B75-8562-5302BD2F5F20}";
fixed_version = "10.1.1239.0";


# Determine if the control is installed.
file = activex_get_filename(clsid:clsid);
if (isnull(file))
{
  activex_end();
  exit(1, "activex_get_filename() returned NULL.");
}
if (!file)
{
  activex_end();
  exit(0, "The control is not installed since the class id '"+clsid+"' is not defined on the remote host.");
}


# Get its version.
version = activex_get_fileversion(clsid:clsid);
if (!version)
{
  activex_end();
  exit(1, "Failed to get file version of '"+file+"'.");
}
ver_pat = "^([0-9]+\.[0-9]+)\.([0-9]+)\.[0-9]+$";
version_ui = ereg_replace(pattern:ver_pat, replace:"\1 Build \2", string:version);


# And check it.
info = '';
rc = activex_check_fileversion(clsid:clsid, fix:fixed_version);
if (rc == TRUE)
{
  if (report_paranoia > 1 || activex_get_killbit(clsid:clsid) != TRUE)
  {
    fixed_version_ui = ereg_replace(pattern:ver_pat, replace:"\1 Build \2", string:fixed_version);

    info += '\n  Class Identifier  : ' + clsid +
            '\n  Filename          : ' + file + 
            '\n  Installed version : ' + version_ui + 
            '\n  Fixed version     : ' + fixed_version_ui + '\n';
  }
}
activex_end();


# Report findings.
if (info)
{
  if (report_paranoia > 1)
  {
    report = info +
      '\n' +
      'Note, though, that Nessus did not check whether the kill bit was\n' +
      "set for the control's CLSID because of the Report Paranoia setting" + '\n' +
      'in effect when this scan was run.\n';
  }
  else
  {
    report = info +
      '\n' +
      'Moreover, its kill bit is not set so it is accessible via Internet\n' +
      'Explorer.\n';
  }

  if (report_verbosity > 0) security_hole(port:kb_smb_transport(), extra:report);
  else security_hole(kb_smb_transport());

  exit(0);
}
else
{
  if (rc == FALSE) exit(0, "The control is not affected since it is version "+version_ui+".");
  else if (rc == TRUE) exit(0, "Version "+version_ui+" of the control is installed, but its kill bit is set.");
  else exit(1, "activex_check_fileversion() failed.");
}
