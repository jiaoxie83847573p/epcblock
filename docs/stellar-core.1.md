% epc-core(1)
% epc Development Foundation
%

# NAME

epc-core - Core daemon for epc payment network

# SYNOPSYS

epc-core [OPTIONS]

# DESCRIPTION

epc is a decentralized, federated peer-to-peer network that allows
people to send payments in any asset anywhere in the world
instantaneously, and with minimal fee. `epc-core` is the core
component of this network. `epc-core` is a C++ implementation of
the epc Consensus Protocol configured to construct a chain of
ledgers that are guaranteed to be in agreement across all the
participating nodes at all times.

## Configuration file

In most modes of operation, epc-core requires a configuration
file.  By default, it looks for a file called `epc-core.cfg` in
the current working directory, but this default can be changed by the
`--conf` command-line option.  The configuration file is in TOML
syntax.  The full set of supported directives can be found in
`%prefix%/share/doc/epc-core_example.cfg`.

%commands%

# EXAMPLES

See `%prefix%/share/doc/*.cfg` for some example epc-core
configuration files

# FILES

epc-core.cfg
:   Configuration file (in current working directory by default)

# SEE ALSO

<https://www.epc.org/developers/epc-core/software/admin.html>
:   epc-core administration guide

<https://www.epc.org>
:   Home page of epc development foundation

# BUGS

Please report bugs using the github issue tracker:\
<https://github.com/epc/epc-core/issues>
