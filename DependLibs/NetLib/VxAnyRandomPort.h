//============================================================================
// Copyright (C) 2013 Brett R. Jones
// Issued to MIT style license by Brett R. Jones in 2017
//
// You may use, copy, modify, merge, publish, distribute, sub-license, and/or sell this software
// provided this Copyright is not modified or removed and is included all copies or substantial portions of the Software
//
// This code is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
// bjones.engineer@gmail.com
// http://www.nolimitconnect.com
//============================================================================

// the list paired ports available first pair is skipped
// other pairs are available ports no include the beginning of range and end of range

// list of ports register with icann etc (last updated 2009-06-19)
//PORT NUMBERS
//
//(last updated 2009-06-19)
//
//The port numbers are divided into three ranges: the Well Known Ports,
//the Registered Ports, and the Dynamic and/or Private Ports.
//
//The Well Known Ports are those from 0 through 1023.
//The Registered Ports are those from 1024 through 49151
//
//DCCP Registered ports SHOULD NOT be used without IANA registration.
//The registration procedure is defined in [RFC4340], Section 19.9.
//
//The Dynamic and/or Private Ports are those from 49152 through 65535
//
//WELL KNOWN PORT NUMBERS
//
//The Well Known Ports are assigned by the IANA and on most systems can
//only be used by system (or root) processes or by programs executed by
//privileged users.
//
//The range for assigned ports managed by the IANA is 0-1023.
//
//Port Assignments:
//
//Keyword         Decimal    Description                     References
//-------         -------    -----------                     ----------
0,//                  0/tcp    Reserved
//                  0/udp    Reserved
//#                          Jon Postel <postel&isi.edu>
//spr-itunes        0/tcp    Shirt Pocket netTunes
//spl-itunes        0/tcp    Shirt Pocket launchTunes
//#                          David Nanian <dnanian&shirt-pocket.com> 28 September 2007
//tcpmux            1/tcp    TCP Port Service Multiplexer
//tcpmux            1/udp    TCP Port Service Multiplexer
//#                          Mark Lottor <MKL&nisc.sri.com>
//compressnet       2/tcp    Management Utility
//compressnet       2/udp    Management Utility
//compressnet       3/tcp    Compression Process
//compressnet       3/udp    Compression Process
//#                          Bernie Volz <volz&cisco.com>
//#                 4/tcp    Unassigned
//#                 4/udp    Unassigned
//rje               5/tcp    Remote Job Entry
//rje               5/udp    Remote Job Entry
//#                          Jon Postel <postel&isi.edu>
//#                 6/tcp    Unassigned
//#                 6/udp    Unassigned
7,//echo              7/tcp    Echo
7,//echo              7/udp    Echo
//#                          Jon Postel <postel&isi.edu>
//#                 8/tcp    Unassigned
//#                 8/udp    Unassigned
9,//discard           9/tcp    Discard 
//discard           9/udp    Discard 
//#                          Jon Postel <postel&isi.edu> 
//discard           9/sctp   Discard  
//#                          IETF TSVWG
//#                          Randall Stewart <rrs&cisco.com>
//#                          [RFC4960]
9,//discard           9/dccp   Discard SC:DISC
//#                          IETF dccp WG, Eddie Kohler <kohler&cs.ucla.edu>, [RFC4340]
//#                10/tcp    Unassigned
//#                10/udp    Unassigned
11,//systat           11/tcp    Active Users
11,//systat           11/udp    Active Users
//#                          Jon Postel <postel&isi.edu>
//#                12/tcp    Unassigned
//#                12/udp    Unassigned
13,//daytime          13/tcp    Daytime (RFC 867)
13,//daytime          13/udp    Daytime (RFC 867)
//#                          Jon Postel <postel&isi.edu>
//#                14/tcp    Unassigned
//#                14/udp    Unassigned
//#                15/tcp    Unassigned [was netstat]
//#                15/udp    Unassigned
//#                16/tcp    Unassigned
//#                16/udp    Unassigned
17,//qotd             17/tcp    Quote of the Day
//qotd             17/udp    Quote of the Day
//#                          Jon Postel <postel&isi.edu>
//msp              18/tcp    Message Send Protocol
//msp              18/udp    Message Send Protocol
//#                          Rina Nethaniel <---none--->
//chargen          19/tcp    Character Generator
//chargen          19/udp    Character Generator
//ftp-data         20/tcp    File Transfer [Default Data]
//ftp-data         20/udp    File Transfer [Default Data]
//#                          Jon Postel <postel&isi.edu>
//ftp-data         20/sctp   FTP
//#                          IETF TSVWG
//#                          Randall Stewart <rrs&cisco.com>
//#                          [RFC4960]
//ftp              21/tcp    File Transfer [Control]
//ftp              21/udp    File Transfer [Control]
//#                          Jon Postel <postel&isi.edu>
//ftp              21/sctp   FTP
//#                          IETF TSVWG
//#                          Randall Stewart <rrs&cisco.com>
//#                          [RFC4960]
//ssh              22/tcp    The Secure Shell (SSH) Protocol
//ssh              22/udp    The Secure Shell (SSH) Protocol
//#                          [RFC4251]
//ssh              22/sctp   SSH
//#                          IETF TSVWG
//#                          Randall Stewart <rrs&cisco.com>
//#                          [RFC4960]
//telnet           23/tcp    Telnet
//telnet           23/udp    Telnet
//#                          Jon Postel <postel&isi.edu>
//                 24/tcp    any private mail system
//                 24/udp    any private mail system
//#                          Rick Adams <rick&UUNET.UU.NET>
//smtp             25/tcp    Simple Mail Transfer
//smtp             25/udp    Simple Mail Transfer
25,//#                          Jon Postel <postel&isi.edu>
//#                26/tcp    Unassigned
//#                26/udp    Unassigned
27,//nsw-fe           27/tcp    NSW User System FE
27,//nsw-fe           27/udp    NSW User System FE
//#                          Robert Thomas <BThomas&F.BBN.COM>
//#                28/tcp    Unassigned
//#                28/udp    Unassigned
29,//msg-icp          29/tcp    MSG ICP
29,//msg-icp          29/udp    MSG ICP
//#                          Robert Thomas <BThomas&F.BBN.COM>
//#                30/tcp    Unassigned
//#                30/udp    Unassigned
31,//msg-auth         31/tcp    MSG Authentication
//msg-auth         31/udp    MSG Authentication
//#                          Robert Thomas <BThomas&F.BBN.COM>
//#                32/tcp    Unassigned
//#                32/udp    Unassigned
//dsp              33/tcp    Display Support Protocol
//dsp              33/udp    Display Support Protocol
33,//#                          Ed Cain <cain&edn-unix.dca.mil>
//#                34/tcp    Unassigned
//#                34/udp    Unassigned
35,//                 35/tcp    any private printer server
35,//                 35/udp    any private printer server
//#                          Jon Postel <postel&isi.edu>
//#                36/tcp    Unassigned
//#                36/udp    Unassigned
37,//time             37/tcp    Time
//time             37/udp    Time
//#                          Jon Postel <postel&isi.edu>
//rap              38/tcp    Route Access Protocol
//rap              38/udp    Route Access Protocol
//#                          Robert Ullmann <ariel&world.std.com>
//rlp              39/tcp    Resource Location Protocol
//rlp              39/udp    Resource Location Protocol
39,//#                          Mike Accetta <MIKE.ACCETTA&CMU-CS-A.EDU>
//#                40/tcp    Unassigned
//#                40/udp    Unassigned
41,//graphics         41/tcp    Graphics
//graphics         41/udp    Graphics
//name             42/tcp    Host Name Server
//name             42/udp    Host Name Server
//nameserver       42/tcp    Host Name Server
//nameserver       42/udp    Host Name Server
//nicname          43/tcp    Who Is
//nicname          43/udp    Who Is
//mpm-flags        44/tcp    MPM FLAGS Protocol
//mpm-flags        44/udp    MPM FLAGS Protocol
//mpm              45/tcp    Message Processing Module [recv]
//mpm              45/udp    Message Processing Module [recv]
//mpm-snd          46/tcp    MPM [default send]
//mpm-snd          46/udp    MPM [default send]
//#                          Jon Postel <postel&isi.edu>
//ni-ftp           47/tcp    NI FTP
//ni-ftp           47/udp    NI FTP
//#                          Steve Kille <S.Kille&isode.com>
//auditd           48/tcp    Digital Audit Daemon
//auditd           48/udp    Digital Audit Daemon
//#                          Larry Scott <scott&zk3.dec.com>
//tacacs           49/tcp    Login Host Protocol (TACACS)
//tacacs           49/udp    Login Host Protocol (TACACS)
//#                          Pieter Ditmars <pditmars&BBN.COM>
//re-mail-ck       50/tcp    Remote Mail Checking Protocol
//re-mail-ck       50/udp    Remote Mail Checking Protocol
//#                          Steve Dorner <s-dorner&UIUC.EDU>
//la-maint         51/tcp    IMP Logical Address Maintenance
//la-maint         51/udp    IMP Logical Address Maintenance
//#                          Andy Malis <malis_a&timeplex.com>
//xns-time         52/tcp    XNS Time Protocol
//xns-time         52/udp    XNS Time Protocol
//#                          Susie Armstrong <Armstrong.wbst128@XEROX>
//domain           53/tcp    Domain Name Server
//domain           53/udp    Domain Name Server
//#                          Paul Mockapetris <PVM&ISI.EDU>
//xns-ch           54/tcp    XNS Clearinghouse
//xns-ch           54/udp    XNS Clearinghouse
//#                          Susie Armstrong <Armstrong.wbst128@XEROX>
//isi-gl           55/tcp    ISI Graphics Language
//isi-gl           55/udp    ISI Graphics Language
//xns-auth         56/tcp    XNS Authentication
//xns-auth         56/udp    XNS Authentication
//#                          Susie Armstrong <Armstrong.wbst128@XEROX>
//                 57/tcp    any private terminal access
//                 57/udp    any private terminal access
//#                          Jon Postel <postel&isi.edu>
//xns-mail         58/tcp    XNS Mail
//xns-mail         58/udp    XNS Mail
//#                          Susie Armstrong <Armstrong.wbst128@XEROX>
59,//                 59/tcp    any private file service
//                 59/udp    any private file service
//#                          Jon Postel <postel&isi.edu>
//                 60/tcp    Unassigned
//                 60/udp    Unassigned
61,//ni-mail          61/tcp    NI MAIL
//ni-mail          61/udp    NI MAIL
//#                          Steve Kille <S.Kille&isode.com>
//acas             62/tcp    ACA Services
//acas             62/udp    ACA Services
//#                          E. Wald <ewald&via.enet.dec.com>
//whois++          63/tcp    whois++
//whois++          63/udp    whois++
//#                          Rickard Schoultz <schoultz&sunet.se>
//covia            64/tcp    Communications Integrator (CI)
//covia            64/udp    Communications Integrator (CI)
//#                          Dan Smith <dan.smith&den.galileo.com>
//tacacs-ds        65/tcp    TACACS-Database Service
//tacacs-ds        65/udp    TACACS-Database Service
//#                          Kathy Huber <khuber&bbn.com>
//sql*net          66/tcp    Oracle SQL*NET
//sql*net          66/udp    Oracle SQL*NET
//#                          Jack Haverty <jhaverty&ORACLE.COM>
//bootps           67/tcp    Bootstrap Protocol Server
//bootps           67/udp    Bootstrap Protocol Server
//bootpc           68/tcp    Bootstrap Protocol Client
//bootpc           68/udp    Bootstrap Protocol Client
//#                          Bill Croft <Croft&SUMEX-AIM.STANFORD.EDU>
//tftp             69/tcp    Trivial File Transfer
//tftp             69/udp    Trivial File Transfer
//#                          David Clark <ddc&LCS.MIT.EDU>
//gopher           70/tcp    Gopher
//gopher           70/udp    Gopher
//#                          Mark McCahill <mpm&boombox.micro.umn.edu>
//netrjs-1         71/tcp    Remote Job Service
//netrjs-1         71/udp    Remote Job Service
//netrjs-2         72/tcp    Remote Job Service
//netrjs-2         72/udp    Remote Job Service
//netrjs-3         73/tcp    Remote Job Service
//netrjs-3         73/udp    Remote Job Service
//netrjs-4         74/tcp    Remote Job Service
//netrjs-4         74/udp    Remote Job Service
//#                          Bob Braden <Braden&ISI.EDU>
//                 75/tcp    any private dial out service
//                 75/udp    any private dial out service
//#                          Jon Postel <postel&isi.edu>
//deos             76/tcp    Distributed External Object Store
//deos             76/udp    Distributed External Object Store
//#                          Robert Ullmann <ariel&world.std.com>
//                 77/tcp    any private RJE service
//                 77/udp    any private RJE service
//#                          Jon Postel <postel&isi.edu>
//vettcp           78/tcp    vettcp
//vettcp           78/udp    vettcp
//#                          Christopher Leong <leong&kolmod.mlo.dec.com>
//finger           79/tcp    Finger
//finger           79/udp    Finger
//#                          David Zimmerman <dpz&RUTGERS.EDU>
//#                          Unauthorized use by some mail users (see [RFC4146] for details)
//http             80/tcp    World Wide Web HTTP
//http             80/udp    World Wide Web HTTP
//www              80/tcp    World Wide Web HTTP
//www              80/udp    World Wide Web HTTP
//www-http         80/tcp    World Wide Web HTTP
//www-http         80/udp    World Wide Web HTTP
//#                          Tim Berners-Lee <timbl&W3.org>
//http             80/sctp   HTTP
//#                          IETF TSVWG
//#                          Randall Stewart <rrs&cisco.com>
80,//#                          [RFC4960]
//#                81        Unassigned (Removed on 2007-09-06)
82,//xfer             82/tcp    XFER Utility
//xfer             82/udp    XFER Utility
//#                          Thomas M. Smith <Thomas.M.Smith&lmco.com>
//mit-ml-dev       83/tcp    MIT ML Device
//mit-ml-dev       83/udp    MIT ML Device
//#                          David Reed <--none--->
//ctf              84/tcp    Common Trace Facility
//ctf              84/udp    Common Trace Facility
//#                          Hugh Thomas <thomas&oils.enet.dec.com>
//mit-ml-dev       85/tcp    MIT ML Device
//mit-ml-dev       85/udp    MIT ML Device
//#                          David Reed <--none--->
//mfcobol          86/tcp    Micro Focus Cobol
//mfcobol          86/udp    Micro Focus Cobol
//#                          Simon Edwards <--none--->
//                 87/tcp    any private terminal link
//                 87/udp    any private terminal link
//#                          Jon Postel <postel&isi.edu>
//kerberos         88/tcp    Kerberos
//kerberos         88/udp    Kerberos
//#                          B. Clifford Neuman <bcn&isi.edu>
//su-mit-tg        89/tcp    SU/MIT Telnet Gateway
//su-mit-tg        89/udp    SU/MIT Telnet Gateway
//#                          Mark Crispin <MRC&PANDA.COM>
//########### PORT 90 also being used unofficially by Pointcast #########
//dnsix            90/tcp    DNSIX Securit Attribute Token Map
//dnsix            90/udp    DNSIX Securit Attribute Token Map
//#                          Charles Watt <watt&sware.com>
//mit-dov          91/tcp    MIT Dover Spooler
//mit-dov          91/udp    MIT Dover Spooler
//#                          Eliot Moss <EBM&XX.LCS.MIT.EDU>
//npp              92/tcp    Network Printing Protocol
//npp              92/udp    Network Printing Protocol
//#                          Louis Mamakos <louie&sayshell.umd.edu>
//dcp              93/tcp    Device Control Protocol
//dcp              93/udp    Device Control Protocol
//#                          Daniel Tappan <Tappan&BBN.COM>
//objcall          94/tcp    Tivoli Object Dispatcher
//objcall          94/udp    Tivoli Object Dispatcher
//#                          Tom Bereiter <--none--->
//supdup           95/tcp    SUPDUP
//supdup           95/udp    SUPDUP
//#                          Mark Crispin <MRC&PANDA.COM>
//dixie            96/tcp    DIXIE Protocol Specification
//dixie            96/udp    DIXIE Protocol Specification
//#                Tim Howes <Tim.Howes&terminator.cc.umich.edu>
//swift-rvf        97/tcp    Swift Remote Virtural File Protocol
//swift-rvf        97/udp    Swift Remote Virtural File Protocol
//#                          Maurice R. Turcotte
//#                <mailrus!uflorida!rm1!dnmrt%rmatl&uunet.UU.NET> 
//tacnews          98/tcp    TAC News
//tacnews          98/udp    TAC News
//#                          Jon Postel <postel&isi.edu>
//metagram         99/tcp    Metagram Relay
//metagram         99/udp    Metagram Relay
//#                          Geoff Goodfellow <Geoff&FERNWOOD.MPK.CA.US>
//newacct         100/tcp    [unauthorized use]
//hostname        101/tcp    NIC Host Name Server
//hostname        101/udp    NIC Host Name Server
//#                          Jon Postel <postel&isi.edu>
//iso-tsap        102/tcp    ISO-TSAP Class 0
//iso-tsap        102/udp    ISO-TSAP Class 0
//#                          Marshall Rose <mrose&dbc.mtview.ca.us>
//gppitnp         103/tcp    Genesis Point-to-Point Trans Net
//gppitnp         103/udp    Genesis Point-to-Point Trans Net
//acr-nema        104/tcp    ACR-NEMA Digital Imag. & Comm. 300
//acr-nema        104/udp    ACR-NEMA Digital Imag. & Comm. 300
//#                          Patrick McNamee <--none--->
//cso             105/tcp    CCSO name server protocol
//cso             105/udp    CCSO name server protocol
//#                          Martin Hamilton <martin&mrrl.lut.as.uk>           
//csnet-ns        105/tcp    Mailbox Name Nameserver
//csnet-ns        105/udp    Mailbox Name Nameserver
//#                          Marvin Solomon <solomon&CS.WISC.EDU>
//3com-tsmux      106/tcp    3COM-TSMUX
//3com-tsmux      106/udp    3COM-TSMUX
//#                          Jeremy Siegel <jzs&NSD.3Com.COM>
//##########      106        Unauthorized use by insecure poppassd protocol
//rtelnet         107/tcp    Remote Telnet Service
//rtelnet         107/udp    Remote Telnet Service
//#                          Jon Postel <postel&isi.edu>
//snagas          108/tcp    SNA Gateway Access Server
//snagas          108/udp    SNA Gateway Access Server
//#                          Kevin Murphy <murphy&sevens.lkg.dec.com>
//pop2            109/tcp    Post Office Protocol - Version 2
//pop2            109/udp    Post Office Protocol - Version 2
//#                          Joyce K. Reynolds <jkrey&isi.edu>
//pop3            110/tcp    Post Office Protocol - Version 3
//pop3            110/udp    Post Office Protocol - Version 3
//#                          Marshall Rose <mrose&dbc.mtview.ca.us>
//sunrpc          111/tcp    SUN Remote Procedure Call
//sunrpc          111/udp    SUN Remote Procedure Call
//#                          Chuck McManis <cmcmanis&freegate.net>
//mcidas          112/tcp    McIDAS Data Transmission Protocol
//mcidas          112/udp    McIDAS Data Transmission Protocol
//#                          Glenn Davis <support&unidata.ucar.edu>
//ident           113/tcp    
//auth            113/tcp    Authentication Service
113,//auth            113/udp    Authentication Service
//#                          Mike St. Johns <stjohns&arpa.mil>
//#               114        Deprecated June 2004
115,//sftp            115/tcp    Simple File Transfer Protocol
//sftp            115/udp    Simple File Transfer Protocol
//#                          Mark Lottor <MKL&nisc.sri.com>
//ansanotify      116/tcp    ANSA REX Notify
//ansanotify      116/udp    ANSA REX Notify
//#                          Nicola J. Howarth <njh&ansa.co.uk>
//uucp-path       117/tcp    UUCP Path Service
//uucp-path       117/udp    UUCP Path Service
//sqlserv         118/tcp    SQL Services
//sqlserv         118/udp    SQL Services
//#                          Larry Barnes <barnes&broke.enet.dec.com>
//nntp            119/tcp    Network News Transfer Protocol
//nntp            119/udp    Network News Transfer Protocol
//#                          Phil Lapsley <phil&UCBARPA.BERKELEY.EDU>
//cfdptkt         120/tcp    CFDPTKT
//cfdptkt         120/udp    CFDPTKT
//#                          John Ioannidis <ji&close.cs.columbia.ed>
//erpc            121/tcp    Encore Expedited Remote Pro.Call
//erpc            121/udp    Encore Expedited Remote Pro.Call
//#                          Jack O'Neil <---none--->
//smakynet        122/tcp    SMAKYNET
//smakynet        122/udp    SMAKYNET
//#                          Pierre Arnaud <pierre.arnaud&iname.com>
//ntp             123/tcp    Network Time Protocol
//ntp             123/udp    Network Time Protocol
//#                          Dave Mills <Mills&HUEY.UDEL.EDU>
//ansatrader      124/tcp    ANSA REX Trader
//ansatrader      124/udp    ANSA REX Trader
//#                          Nicola J. Howarth <njh&ansa.co.uk>
//locus-map       125/tcp    Locus PC-Interface Net Map Ser
//locus-map       125/udp    Locus PC-Interface Net Map Ser
//#                          Eric Peterson <lcc.eric&SEAS.UCLA.EDU>
//nxedit		126/tcp    NXEdit
//nxedit		126/udp    NXEdit
//#			   Don Payette <Don.Payette&unisys.com>
//###########Port 126 Previously assigned to application below#######
//#unitary         126/tcp    Unisys Unitary Login
//#unitary         126/udp    Unisys Unitary Login
//#                          <feil&kronos.nisd.cam.unisys.com>
//###########Port 126 Previously assigned to application above#######
//locus-con       127/tcp    Locus PC-Interface Conn Server
//locus-con       127/udp    Locus PC-Interface Conn Server
//#                          Eric Peterson <lcc.eric&SEAS.UCLA.EDU>
//gss-xlicen      128/tcp    GSS X License Verification
//gss-xlicen      128/udp    GSS X License Verification
//#                          John Light <johnl&gssc.gss.com>
//pwdgen          129/tcp    Password Generator Protocol
//pwdgen          129/udp    Password Generator Protocol
//#                          Frank J. Wacho <WANCHO&WSMR-SIMTEL20.ARMY.MIL>
//cisco-fna       130/tcp    cisco FNATIVE
//cisco-fna       130/udp    cisco FNATIVE
//cisco-tna       131/tcp    cisco TNATIVE
//cisco-tna       131/udp    cisco TNATIVE
//cisco-sys       132/tcp    cisco SYSMAINT
//cisco-sys       132/udp    cisco SYSMAINT
//statsrv         133/tcp    Statistics Service
//statsrv         133/udp    Statistics Service
//#                          Dave Mills <Mills&HUEY.UDEL.EDU>
//ingres-net      134/tcp    INGRES-NET Service
//ingres-net      134/udp    INGRES-NET Service
//#                          Mike Berrow <---none--->
//epmap           135/tcp    DCE endpoint resolution
//epmap           135/udp    DCE endpoint resolution
//#                          Joe Pato <pato&apollo.hp.com>
//profile         136/tcp    PROFILE Naming System           
//profile         136/udp    PROFILE Naming System           
//#                          Larry Peterson <llp&ARIZONA.EDU>
//netbios-ns      137/tcp    NETBIOS Name Service    
//netbios-ns      137/udp    NETBIOS Name Service    
//netbios-dgm     138/tcp    NETBIOS Datagram Service
//netbios-dgm     138/udp    NETBIOS Datagram Service
//netbios-ssn     139/tcp    NETBIOS Session Service
//netbios-ssn     139/udp    NETBIOS Session Service
//#                          Jon Postel <postel&isi.edu>
//emfis-data      140/tcp    EMFIS Data Service
//emfis-data      140/udp    EMFIS Data Service
//emfis-cntl      141/tcp    EMFIS Control Service
//emfis-cntl      141/udp    EMFIS Control Service
//#                          Gerd Beling <GBELING&ISI.EDU>
//bl-idm          142/tcp    Britton-Lee IDM           
//bl-idm          142/udp    Britton-Lee IDM           
//#                          Susie Snitzer <---none--->
//imap            143/tcp    Internet Message Access Protocol
//imap            143/udp    Internet Message Access Protocol
//#                          Mark Crispin <MRC&CAC.Washington.EDU>
//uma 		144/tcp    Universal Management Architecture
//uma		144/udp    Universal Management Architecture
//#			   Jay Whitney <jw&powercenter.com>
//uaac            145/tcp    UAAC Protocol             
//uaac            145/udp    UAAC Protocol             
//#                          David A. Gomberg <gomberg&GATEWAY.MITRE.ORG>
//iso-tp0         146/tcp    ISO-IP0
//iso-tp0         146/udp    ISO-IP0
//iso-ip          147/tcp    ISO-IP
//iso-ip          147/udp    ISO-IP
//#                          Marshall Rose <mrose&dbc.mtview.ca.us>
//jargon          148/tcp    Jargon
//jargon          148/udp    Jargon
//#			   Bill Weinman <wew&bearnet.com>
//aed-512         149/tcp    AED 512 Emulation Service           
//aed-512         149/udp    AED 512 Emulation Service           
//#                          Albert G. Broscius <broscius&DSL.CIS.UPENN.EDU>
//sql-net         150/tcp    SQL-NET                    
//sql-net         150/udp    SQL-NET                    
//#                          Martin Picard <<---none--->
//hems            151/tcp    HEMS                              
//hems            151/udp    HEMS                              
//bftp            152/tcp    Background File Transfer Program 
//bftp            152/udp    Background File Transfer Program 
//#                          Annette DeSchon <DESCHON&ISI.EDU>
//sgmp            153/tcp    SGMP                    
//sgmp            153/udp    SGMP                    
//#                          Marty Schoffstahl <schoff&NISC.NYSER.NET>
//netsc-prod      154/tcp    NETSC                             
//netsc-prod      154/udp    NETSC                             
//netsc-dev       155/tcp    NETSC                             
//netsc-dev       155/udp    NETSC                             
//#                          Sergio Heker <heker&JVNCC.CSC.ORG>
//sqlsrv          156/tcp    SQL Service                  
//sqlsrv          156/udp    SQL Service                  
//#                          Craig Rogers <Rogers&ISI.EDU>
//knet-cmp        157/tcp    KNET/VM Command/Message Protocol
//knet-cmp        157/udp    KNET/VM Command/Message Protocol
//#                          Gary S. Malkin <GMALKIN&XYLOGICS.COM>
//pcmail-srv      158/tcp    PCMail Server                 
//pcmail-srv      158/udp    PCMail Server                 
//#                          Mark L. Lambert <markl&PTT.LCS.MIT.EDU>
//nss-routing     159/tcp    NSS-Routing                  
//nss-routing     159/udp    NSS-Routing                  
//#                          Yakov Rekhter <Yakov&IBM.COM>
//sgmp-traps      160/tcp    SGMP-TRAPS                
//sgmp-traps      160/udp    SGMP-TRAPS                
//#                          Marty Schoffstahl <schoff&NISC.NYSER.NET>
//snmp            161/tcp    SNMP
//snmp            161/udp    SNMP
//snmptrap        162/tcp    SNMPTRAP
//snmptrap        162/udp    SNMPTRAP
//#                          Marshall Rose <mrose&dbc.mtview.ca.us>
//cmip-man        163/tcp    CMIP/TCP Manager   
//cmip-man        163/udp    CMIP/TCP Manager   
//cmip-agent      164/tcp    CMIP/TCP Agent     
//cmip-agent      164/udp    CMIP/TCP Agent     
//#                          Amatzia Ben-Artzi <---none--->
//xns-courier     165/tcp    Xerox                          
//xns-courier     165/udp    Xerox                          
//#                          Susie Armstrong <Armstrong.wbst128&XEROX.COM>
//s-net           166/tcp    Sirius Systems          
//s-net           166/udp    Sirius Systems          
//#                          Brian Lloyd <brian&lloyd.com>
//namp            167/tcp    NAMP                    
//namp            167/udp    NAMP                    
//#                          Marty Schoffstahl <schoff&NISC.NYSER.NET>
//rsvd            168/tcp    RSVD                              
//rsvd            168/udp    RSVD                              
//#                          Previous contact: Neil Todd <mcvax!ist.co.uk!neil&UUNET.UU.NET>
//#                          Current contact: Alan Sandell <alan.sandell&ist.co.uk> 01 May 2008
//send            169/tcp    SEND                              
//send            169/udp    SEND                              
//#                          William D. Wisner <wisner&HAYES.FAI.ALASKA.EDU>
//print-srv       170/tcp    Network PostScript              
//print-srv       170/udp    Network PostScript              
//#                          Brian Reid <reid&DECWRL.DEC.COM>
//multiplex       171/tcp    Network Innovations Multiplex
//multiplex       171/udp    Network Innovations Multiplex
//cl/1            172/tcp    Network Innovations CL/1     
//cl/1            172/udp    Network Innovations CL/1     
//#                          Kevin DeVault <<---none--->
//xyplex-mux      173/tcp    Xyplex                          
//xyplex-mux      173/udp    Xyplex                          
//#                          Bob Stewart <STEWART&XYPLEX.COM>
//mailq           174/tcp    MAILQ                               
//mailq           174/udp    MAILQ                               
//#                          Rayan Zachariassen <rayan&AI.TORONTO.EDU>
//vmnet           175/tcp    VMNET                                
//vmnet           175/udp    VMNET  
//#                          Christopher Tengi <tengi&Princeton.EDU>
//genrad-mux      176/tcp    GENRAD-MUX                      
//genrad-mux      176/udp    GENRAD-MUX                      
//#                          Ron Thornton <thornton&qm7501.genrad.com>
//xdmcp           177/tcp    X Display Manager Control Protocol  
//xdmcp           177/udp    X Display Manager Control Protocol  
//#                          Robert W. Scheifler <RWS&XX.LCS.MIT.EDU>
//nextstep        178/tcp    NextStep Window Server     
//nextstep        178/udp    NextStep Window Server     
//#                          Leo Hourvitz <leo&NEXT.COM>
//bgp             179/tcp    Border Gateway Protocol             
//bgp             179/udp    Border Gateway Protocol             
//#                          Kirk Lougheed <LOUGHEED&MATHOM.CISCO.COM>
//bgp             179/sctp   BGP
//#                          IETF TSVWG
//#                          Randall Stewart <rrs&cisco.com>
//#                          [RFC4960]
//ris             180/tcp    Intergraph                         
//ris             180/udp    Intergraph                         
//#                          Dave Buehmann <ingr!daveb&UUNET.UU.NET>
//unify           181/tcp    Unify                  
//unify           181/udp    Unify                  
//#                          Mark Ainsley <ianaportmaster&unify.com>
//audit           182/tcp    Unisys Audit SITP                  
//audit           182/udp    Unisys Audit SITP                  
//#                          Gil Greenbaum <gcole&nisd.cam.unisys.com>
//ocbinder        183/tcp    OCBinder                     
//ocbinder        183/udp    OCBinder                     
//ocserver        184/tcp    OCServer                     
//ocserver        184/udp    OCServer                     
//#                          Jerrilynn Okamura <--none--->
//remote-kis      185/tcp    Remote-KIS                        
//remote-kis      185/udp    Remote-KIS                        
//kis             186/tcp    KIS Protocol                      
//kis             186/udp    KIS Protocol                      
//#                          Ralph Droms <rdroms&NRI.RESTON.VA.US>
//aci             187/tcp    Application Communication Interface
//aci             187/udp    Application Communication Interface
//#                          Rick Carlos <rick.ticipa.csc.ti.com>
//mumps           188/tcp    Plus Five's MUMPS            
//mumps           188/udp    Plus Five's MUMPS            
//#                          Hokey Stenn <hokey&PLUS5.COM>
//qft             189/tcp    Queued File Transport        
//qft             189/udp    Queued File Transport        
//#                          Wayne Schroeder <schroeder&SDS.SDSC.EDU>
//gacp            190/tcp    Gateway Access Control Protocol
//gacp            190/udp    Gateway Access Control Protocol
//#                          C. Philip Wood <cpw&LANL.GOV>
//prospero        191/tcp    Prospero Directory Service      
//prospero        191/udp    Prospero Directory Service      
//#                          B. Clifford Neuman <bcn&isi.edu>
//osu-nms         192/tcp    OSU Network Monitoring System       
//osu-nms         192/udp    OSU Network Monitoring System       
//#                          Doug Karl <KARL-D&OSU-20.IRCC.OHIO-STATE.EDU>
//srmp            193/tcp    Spider Remote Monitoring Protocol 
//srmp            193/udp    Spider Remote Monitoring Protocol 
//#                          Ted J. Socolofsky <Teds&SPIDER.CO.UK>
//irc             194/tcp    Internet Relay Chat Protocol        
//irc             194/udp    Internet Relay Chat Protocol        
//#                          Jarkko Oikarinen <jto&TOLSUN.OULU.FI>
//dn6-nlm-aud     195/tcp    DNSIX Network Level Module Audit    
//dn6-nlm-aud     195/udp    DNSIX Network Level Module Audit    
//dn6-smm-red     196/tcp    DNSIX Session Mgt Module Audit Redir
//dn6-smm-red     196/udp    DNSIX Session Mgt Module Audit Redir
//#                          Lawrence Lebahn <DIA3&PAXRV-NES.NAVY.MIL>
//dls             197/tcp    Directory Location Service        
//dls             197/udp    Directory Location Service        
//dls-mon         198/tcp    Directory Location Service Monitor
//dls-mon         198/udp    Directory Location Service Monitor
//#                          Scott Bellew <smb&cs.purdue.edu>
//smux            199/tcp    SMUX
//smux            199/udp    SMUX
//#                          Marshall Rose <mrose&dbc.mtview.ca.us>
//src             200/tcp    IBM System Resource Controller
//src             200/udp    IBM System Resource Controller
//#                          Gerald McBrearty <---none--->
//at-rtmp         201/tcp    AppleTalk Routing Maintenance       
//at-rtmp         201/udp    AppleTalk Routing Maintenance       
//at-nbp          202/tcp    AppleTalk Name Binding              
//at-nbp          202/udp    AppleTalk Name Binding              
//at-3            203/tcp    AppleTalk Unused                    
//at-3            203/udp    AppleTalk Unused                    
//at-echo         204/tcp    AppleTalk Echo                      
//at-echo         204/udp    AppleTalk Echo                      
//at-5            205/tcp    AppleTalk Unused                    
//at-5            205/udp    AppleTalk Unused                    
//at-zis          206/tcp    AppleTalk Zone Information          
//at-zis          206/udp    AppleTalk Zone Information          
//at-7            207/tcp    AppleTalk Unused                    
//at-7            207/udp    AppleTalk Unused                    
//at-8            208/tcp    AppleTalk Unused                    
//at-8            208/udp    AppleTalk Unused                    
//#                          Rob Chandhok <chandhok&gnome.cs.cmu.edu>
//qmtp            209/tcp    The Quick Mail Transfer Protocol
//qmtp            209/udp    The Quick Mail Transfer Protocol
//#                          Dan Bernstein <djb&silverton.berkeley.edu>
//z39.50          210/tcp    ANSI Z39.50
//z39.50          210/udp    ANSI Z39.50
//#                          Mark H. Needleman <markn&sirsi.com> 
//914c/g          211/tcp    Texas Instruments 914C/G Terminal
//914c/g          211/udp    Texas Instruments 914C/G Terminal
//#                          Bill Harrell <---none--->
//anet            212/tcp    ATEXSSTR   
//anet            212/udp    ATEXSSTR   
//#                          Jim Taylor <taylor&heart.epps.kodak.com>
//ipx             213/tcp    IPX         	                      
//ipx             213/udp    IPX                                
//#                          Don Provan <donp&xlnvax.novell.com>
//vmpwscs         214/tcp    VM PWSCS                         
//vmpwscs         214/udp    VM PWSCS                         
//#                          Dan Shia <dset!shia&uunet.UU.NET>
//softpc          215/tcp    Insignia Solutions
//softpc          215/udp    Insignia Solutions
//#                          Martyn Thomas <---none--->
//CAIlic          216/tcp    Computer Associates Int'l License Server
//CAIlic          216/udp    Computer Associates Int'l License Server
//#                          Chuck Spitz <spich04&cai.com>
//dbase           217/tcp    dBASE Unix
//dbase           217/udp    dBASE Unix
//#                          Don Gibson
//#            <sequent!aero!twinsun!ashtate.A-T.COM!dong&uunet.UU.NET> 
//mpp             218/tcp    Netix Message Posting Protocol
//mpp             218/udp    Netix Message Posting Protocol
//#                          Shannon Yeh <yeh&netix.com>
//uarps           219/tcp    Unisys ARPs               
//uarps           219/udp    Unisys ARPs               
//#                          Ashok Marwaha <---none--->
//imap3           220/tcp    Interactive Mail Access Protocol v3
//imap3           220/udp    Interactive Mail Access Protocol v3
//#                          James Rice <RICE&SUMEX-AIM.STANFORD.EDU>
//fln-spx         221/tcp    Berkeley rlogind with SPX auth   
//fln-spx         221/udp    Berkeley rlogind with SPX auth   
//rsh-spx         222/tcp    Berkeley rshd with SPX auth      
//rsh-spx         222/udp    Berkeley rshd with SPX auth      
//cdc             223/tcp    Certificate Distribution Center  
//cdc             223/udp    Certificate Distribution Center  
//#               Kannan Alagappan <kannan&sejour.enet.dec.com>
//########### Possible Conflict of Port 222 with "Masqdialer"##############
//### Contact for Masqdialer is Charles Wright <cpwright&villagenet.com>###
//masqdialer	224/tcp    masqdialer
//masqdialer	224/udp    masqdialer
//#			   Charles Wright <cpwright&villagenet.com>
//#               225-241    Reserved
//#                          Jon Postel <postel&isi.edu>
//direct          242/tcp    Direct
//direct          242/udp    Direct
//#                          Herb Sutter <HerbS&cntc.com>
//sur-meas        243/tcp    Survey Measurement          
//sur-meas        243/udp    Survey Measurement          
//#                          Dave Clark <ddc&LCS.MIT.EDU>
//inbusiness      244/tcp    inbusiness
//inbusiness      244/udp    inbusiness
//#			   Derrick Hisatake <derrick.i.hisatake&intel.com>
//link            245/tcp    LINK
//link            245/udp    LINK
//dsp3270         246/tcp    Display Systems Protocol        
//dsp3270         246/udp    Display Systems Protocol        
//#                          Weldon J. Showalter <Gamma&MINTAKA.DCA.MIL>
//subntbcst_tftp  247/tcp    SUBNTBCST_TFTP
//subntbcst_tftp  247/udp    SUBNTBCST_TFTP
//#			   John Fake <fake&us.ibm.com>
//bhfhs		248/tcp    bhfhs
//bhfhs		248/udp    bhfhs
//#			   John Kelly <johnk&bellhow.com>
//#               249-255    Reserved
//#                          Jon Postel <postel&isi.edu>
//rap             256/tcp    RAP
//rap             256/udp    RAP
//#                          J.S. Greenfield <greeny&raleigh.ibm.com>
//set             257/tcp    Secure Electronic Transaction
257,//set             257/udp    Secure Electronic Transaction
//#                          Donald Eastlake <dee3&torque.pothole.com>
//#		258	   Unassigned (Removed 2006-09-13)
259,//esro-gen        259/tcp    Efficient Short Remote Operations
//esro-gen        259/udp    Efficient Short Remote Operations
//#                          Mohsen Banan <mohsen&rostam.neda.com>
//openport        260/tcp    Openport
//openport        260/udp    Openport
//#                          John Marland <jmarland&dean.openport.com>
//nsiiops 	261/tcp    IIOP Name Service over TLS/SSL
//nsiiops		261/udp    IIOP Name Service over TLS/SSL
//#                          Jeff Stewart <jstewart&netscape.com>
//arcisdms	262/tcp    Arcisdms
//arcisdms	262/udp	   Arcisdms
//#			   Russell Crook (rmc&sni.ca>
//hdap		263/tcp    HDAP
//hdap		263/udp    HDAP
//#			   Troy Gau <troy&zyxel.com>
//bgmp		264/tcp    BGMP
//bgmp		264/udp    BGMP
//#			   Dave Thaler <thalerd&eecs.umich.edu>
//x-bone-ctl	265/tcp    X-Bone CTL
//x-bone-ctl	265/udp    X-Bone CTL
//#			   Joe Touch <touch&isi.edu>
//sst             266/tcp    SCSI on ST
//sst             266/udp    SCSI on ST
//#                          Donald D. Woelz <don&genroco.com>
//td-service      267/tcp    Tobit David Service Layer
//td-service      267/udp    Tobit David Service Layer
//td-replica      268/tcp    Tobit David Replica
//td-replica      268/udp    Tobit David Replica
//#                          Franz-Josef Leuders <development&tobit.com>
//manet           269/tcp    MANET Protocols
269,//manet           269/udp    MANET Protocols                 
//#                          [RFC5498]
//#               270-279    Unassigned
280,//http-mgmt       280/tcp    http-mgmt
//http-mgmt       280/udp    http-mgmt
//#                          Adrian Pell
//#                          <PELL_ADRIAN/HP-UnitedKingdom_m6&hplb.hpl.hp.com>
//personal-link   281/tcp	   Personal Link
//personal-link	281/udp    Personal Link
//#                          Dan Cummings <doc&cnr.com>
//cableport-ax	282/tcp    Cable Port A/X
//cableport-ax	282/udp    Cable Port A/X
//#                          Craig Langfahl <Craig_J_Langfahl&ccm.ch.intel.com>
//rescap          283/tcp    rescap
//rescap          283/udp    rescap
//#                          Paul Hoffman <phoffman&imc.org>
//corerjd         284/tcp    corerjd
284,//corerjd         284/udp    corerjd
//#			               Chris Thornhill <port_contact&cjt.ca>
//#               285        Unassigned  
286,//fxp            286/tcp     FXP Communication
//fxp            286/udp     FXP Communication
//#                          James Darnall <james_r_darnall&sbcglobal.net>  
//k-block         287/tcp    K-BLOCK
287,//k-block         287/udp    K-BLOCK
//#                          Simon P Jackson <jacko&kring.co.uk>    
//#               288-307    Unassigned
308,//novastorbakcup	308/tcp    Novastor Backup
//novastorbakcup	308/udp    Novastor Backup
//#			   Brian Dickman <brian&novastor.com>
//entrusttime     309/tcp    EntrustTime    
//entrusttime     309/udp    EntrustTime    
//#                          Peter Whittaker <pww&entrust.com>
//bhmds		310/tcp        bhmds
//bhmds 		310/udp        bhmds
//#			   John Kelly <johnk&bellhow.com>
//asip-webadmin	311/tcp    AppleShare IP WebAdmin
//asip-webadmin	311/udp    AppleShare IP WebAdmin
//#			   Ann Huang <annhuang&apple.com>
//vslmp		312/tcp    VSLMP
//vslmp		312/udp    VSLMP
//#			   Gerben Wierda <Gerben_Wierda&RnA.nl>
//magenta-logic	313/tcp    Magenta Logic
//magenta-logic	313/udp	   Magenta Logic
//#			   Karl Rousseau <kr&netfusion.co.uk>
//opalis-robot	314/tcp    Opalis Robot
//opalis-robot	314/udp    Opalis Robot
//#			   Laurent Domenech, Opalis <ldomenech&opalis.com>
//dpsi		315/tcp    DPSI
//dpsi		315/udp    DPSI
//#			   Tony Scamurra <Tony&DesktopPaging.com>
//decauth		316/tcp    decAuth
//decauth		316/udp    decAuth
//#			   Michael Agishtein <misha&unx.dec.com>
//zannet		317/tcp    Zannet
//zannet		317/udp    Zannet
//#			   Zan Oliphant <zan&accessone.com>
//pkix-timestamp	318/tcp    PKIX TimeStamp
//pkix-timestamp	318/udp    PKIX TimeStamp
//#			   Robert Zuccherato <robert.zuccherato&entrust.com>
//ptp-event	319/tcp    PTP Event
//ptp-event	319/udp    PTP Event
//ptp-general	320/tcp    PTP General
//ptp-general	320/udp    PTP General
//#			   John Eidson <eidson&hpl.hp.com>
//pip		321/tcp    PIP
//pip		321/udp    PIP
//#			   Gordon Mohr <gojomo&usa.net>
//rtsps		322/tcp    RTSPS
322,//rtsps		322/udp    RTSPS
//#			   Anders Klemets <anderskl&microsoft.com>
//#               323-332    Unassigned
333,//texar		333/tcp    Texar Security Port
333,//texar		333/udp    Texar Security Port
//#			   Eugen Bacic <ebacic&texar.com>
//#		334-343    Unassigned
344,//pdap            344/tcp    Prospero Data Access Protocol
//pdap            344/udp    Prospero Data Access Protocol
//#                          B. Clifford Neuman <bcn&isi.edu>
//pawserv         345/tcp    Perf Analysis Workbench
//pawserv         345/udp    Perf Analysis Workbench
//zserv           346/tcp    Zebra server
//zserv           346/udp    Zebra server
//fatserv         347/tcp    Fatmen Server
//fatserv         347/udp    Fatmen Server
//csi-sgwp        348/tcp    Cabletron Management Protocol
//csi-sgwp        348/udp    Cabletron Management Protocol
//mftp            349/tcp    mftp
//mftp            349/udp    mftp
//#                          Dave Feinleib <davefe&microsoft.com>
//matip-type-a    350/tcp    MATIP Type A
//matip-type-a    350/udp    MATIP Type A
//#                          Alain Robert <arobert&par.sita.int>
//#                          [RFC2351]
//matip-type-b    351/tcp    MATIP Type B
//matip-type-b    351/udp    MATIP Type B
//#                          Alain Robert <arobert&par.sita.int>
//#                          [RFC2351]
//# The following entry records an unassigned but widespread use
//bhoetty		351/tcp	   bhoetty (added 5/21/97)
//bhoetty		351/udp    bhoetty
//#			   John Kelly <johnk&bellhow.com>
//dtag-ste-sb	352/tcp	   DTAG (assigned long ago)
//dtag-ste-sb	352/udp	   DTAG
//#			   Ruediger Wald <wald&ez-darmstadt.telekom.de>
//# The following entry records an unassigned but widespread use
//bhoedap4	352/tcp    bhoedap4 (added 5/21/97)
//bhoedap4	352/udp    bhoedap4
//#			   John Kelly <johnk&bellhow.com>
//ndsauth		353/tcp    NDSAUTH
//ndsauth		353/udp    NDSAUTH
//#			   Jayakumar Ramalingam <jayakumar&novell.com>
//bh611		354/tcp	   bh611
//bh611		354/udp    bh611
//#			   John Kelly <johnk&bellhow.com>
//datex-asn	355/tcp	   DATEX-ASN
//datex-asn	355/udp    DATEX-ASN
//#			   Kenneth Vaughn <kvaughn&mail.viggen.com>
//cloanto-net-1	356/tcp    Cloanto Net 1
//cloanto-net-1	356/udp    Cloanto Net 1
//#			   Michael Battilana <mcb-iana&cloanto.com>
//bhevent		357/tcp	   bhevent
//bhevent		357/udp    bhevent
//#			   John Kelly <johnk&bellhow.com>
//shrinkwrap	358/tcp    Shrinkwrap
//shrinkwrap	358/udp    Shrinkwrap
//#			   Bill Simpson <wsimpson&greendragon.com>
//nsrmp	        359/tcp    Network Security Risk Management Protocol
//nsrmp      	359/udp    Network Security Risk Management Protocol
//#			   Eric Jacksch <jacksch&tenebris.ca>
//scoi2odialog	360/tcp    scoi2odialog
//scoi2odialog	360/udp    scoi2odialog
//#			   Keith Petley <keithp&sco.COM>
//semantix	361/tcp    Semantix
//semantix	361/udp    Semantix
//#		   	   Semantix <xsSupport&semantix.com>
//srssend		362/tcp    SRS Send
//srssend		362/udp    SRS Send
//#			   Curt Mayer <curt&emergent.com>
//rsvp_tunnel	363/tcp    RSVP Tunnel
//rsvp_tunnel	363/udp    RSVP Tunnel
//#			   Andreas Terzis <terzis&cs.ucla.edu>
//aurora-cmgr	364/tcp    Aurora CMGR
//aurora-cmgr	364/udp    Aurora CMGR
//#			   Philip Budne <budne&auroratech.com>
//dtk		365/tcp    DTK
//dtk		365/udp    DTK
//#			   Fred Cohen <fc&all.net>
//odmr		366/tcp    ODMR
//odmr		366/udp    ODMR
//#			   Randall Gellens <randy&qualcomm.com>
//mortgageware	367/tcp    MortgageWare
//mortgageware	367/udp    MortgageWare
//#			   Ole Hellevik <oleh&interlinq.com>
//qbikgdp		368/tcp    QbikGDP
//qbikgdp		368/udp    QbikGDP
//#			   Adrien de Croy <adrien&qbik.com>
//rpc2portmap	369/tcp    rpc2portmap 
//rpc2portmap	369/udp    rpc2portmap
//codaauth2	370/tcp    codaauth2
//codaauth2	370/udp    codaauth2
//#			   Robert Watson <robert&cyrus.watson.org>
//clearcase       371/tcp    Clearcase
//clearcase       371/udp    Clearcase
//#                          Dave LeBlang <leglang&atria.com>
//ulistproc       372/tcp    ListProcessor
//ulistproc       372/udp    ListProcessor
//#                          Anastasios Kotsikonas <tasos&cs.bu.edu>
//legent-1        373/tcp    Legent Corporation
//legent-1        373/udp    Legent Corporation
//legent-2        374/tcp    Legent Corporation
//legent-2        374/udp    Legent Corporation
//#                          Keith Boyce <---none--->
//hassle          375/tcp    Hassle
//hassle          375/udp    Hassle
//#                          Reinhard Doelz <doelz&comp.bioz.unibas.ch>
//nip             376/tcp    Amiga Envoy Network Inquiry Proto   
//nip             376/udp    Amiga Envoy Network Inquiry Proto
//#                          Heinz Wrobel <hwrobel&gmx.de>
//tnETOS          377/tcp    NEC Corporation
//tnETOS          377/udp    NEC Corporation
//dsETOS          378/tcp    NEC Corporation
//dsETOS          378/udp    NEC Corporation
//#                          Tomoo Fujita <tf&arc.bs1.fc.nec.co.jp>
//is99c           379/tcp    TIA/EIA/IS-99 modem client
//is99c           379/udp    TIA/EIA/IS-99 modem client
//is99s           380/tcp    TIA/EIA/IS-99 modem server
//is99s           380/udp    TIA/EIA/IS-99 modem server
//#                          Frank Quick <fquick&qualcomm.com>
//hp-collector    381/tcp    hp performance data collector
//hp-collector    381/udp    hp performance data collector
//hp-managed-node 382/tcp    hp performance data managed node
//hp-managed-node 382/udp    hp performance data managed node
//hp-alarm-mgr    383/tcp    hp performance data alarm manager
//hp-alarm-mgr    383/udp    hp performance data alarm manager
//#                          Frank Blakely <frankb&hpptc16.rose.hp.com>
//arns            384/tcp    A Remote Network Server System
//arns            384/udp    A Remote Network Server System
//#                          David Hornsby <djh&munnari.OZ.AU>
//ibm-app         385/tcp    IBM Application
//ibm-app         385/udp    IBM Application
//#                          Lisa Tomita <---none--->
//asa             386/tcp    ASA Message Router Object Def.
//asa             386/udp    ASA Message Router Object Def.
//#                          Steve Laitinen <laitinen&brutus.aa.ab.com>
//aurp            387/tcp    Appletalk Update-Based Routing Pro.
//aurp            387/udp    Appletalk Update-Based Routing Pro.
//#                          Chris Ranch <cranch&novell.com>
//unidata-ldm     388/tcp    Unidata LDM  
//unidata-ldm     388/udp    Unidata LDM 
//#                          Glenn Davis <support&unidata.ucar.edu>
//ldap            389/tcp    Lightweight Directory Access Protocol
//ldap            389/udp    Lightweight Directory Access Protocol
//#                          Tim Howes <Tim.Howes&terminator.cc.umich.edu>
//uis             390/tcp    UIS
//uis             390/udp    UIS
//#                          Ed Barron <---none---> 
//synotics-relay  391/tcp    SynOptics SNMP Relay Port
//synotics-relay  391/udp    SynOptics SNMP Relay Port
//synotics-broker 392/tcp    SynOptics Port Broker Port
//synotics-broker 392/udp    SynOptics Port Broker Port
//#                          Illan Raab <iraab&synoptics.com>
//meta5           393/tcp    Meta5
//meta5           393/udp    Meta5
//#                          Jim Kanzler <jim.kanzler&meta5.com>
//embl-ndt        394/tcp    EMBL Nucleic Data Transfer
//embl-ndt        394/udp    EMBL Nucleic Data Transfer
//#                          Peter Gad <peter&bmc.uu.se>
//netcp           395/tcp    NETscout Control Protocol
//netcp           395/udp    NETscout Control Protocol
//#                          Anil Singhal <---none--->
//netware-ip      396/tcp    Novell Netware over IP
//netware-ip      396/udp    Novell Netware over IP
//mptn            397/tcp    Multi Protocol Trans. Net.
//mptn            397/udp    Multi Protocol Trans. Net.
//#                          Soumitra Sarkar <sarkar&vnet.ibm.com>
//kryptolan       398/tcp    Kryptolan
//kryptolan       398/udp    Kryptolan
//#                          Peter de Laval <pdl&sectra.se>
//iso-tsap-c2     399/tcp    ISO Transport Class 2 Non-Control over TCP
//iso-tsap-c2     399/udp    ISO Transport Class 2 Non-Control over UDP
//#                          Yanick Pouffary <pouffary&taec.enet.dec.com>
//osb-sd          400/tcp    Oracle Secure Backup
//osb-sd          400/udp    Oracle Secure Backup
//#                          Formerly was Workstation Solutions
//#                          Previous Contact: Jim Ward <jimw&worksta.com>
//#                          Current Contact: Joseph Dziedzic <tony.dziedzic&oracle.com> 06 June 2008
//ups             401/tcp    Uninterruptible Power Supply
//ups             401/udp    Uninterruptible Power Supply
//#                          Previous Contact: Charles Bennett <chuck&benatong.com>
//#                          Current Contact: Charles Bennett <bennettc&ohio.edu> 29 August 2008
//genie           402/tcp    Genie Protocol
//genie           402/udp    Genie Protocol
//#                          Mark Hankin <---none--->
//decap           403/tcp    decap
//decap           403/udp    decap
//nced            404/tcp    nced
//nced            404/udp    nced
//ncld            405/tcp    ncld
//ncld            405/udp    ncld
//#                          Richard Jones <---none--->
//imsp            406/tcp    Interactive Mail Support Protocol
//imsp            406/udp    Interactive Mail Support Protocol
//#                          John Myers <jgm+&cmu.edu>
//timbuktu        407/tcp    Timbuktu
//timbuktu        407/udp    Timbuktu
//#                          Marc Epard <marc&netopia.com>
//prm-sm          408/tcp    Prospero Resource Manager Sys. Man.
//prm-sm          408/udp    Prospero Resource Manager Sys. Man.
//prm-nm          409/tcp    Prospero Resource Manager Node Man.
//prm-nm          409/udp    Prospero Resource Manager Node Man.
//#                          B. Clifford Neuman <bcn&isi.edu>
//decladebug      410/tcp    DECLadebug Remote Debug Protocol
//decladebug      410/udp    DECLadebug Remote Debug Protocol
//#                          Anthony Berent <anthony.berent&reo.mts.dec.com>
//rmt             411/tcp    Remote MT Protocol
//rmt             411/udp    Remote MT Protocol
//#                          Peter Eriksson <pen&lysator.liu.se>
//synoptics-trap  412/tcp    Trap Convention Port
//synoptics-trap  412/udp    Trap Convention Port
//#                          Illan Raab <iraab&synoptics.com>
//smsp            413/tcp    Storage Management Services Protocol
//smsp            413/udp    Storage Management Services Protocol
//#                          Murthy Srinivas <murthy&novell.com>
//infoseek        414/tcp    InfoSeek
//infoseek        414/udp    InfoSeek
//#                          Steve Kirsch <stk&infoseek.com>
//bnet            415/tcp    BNet
//bnet            415/udp    BNet
//#                          Jim Mertz <JMertz+RV09&rvdc.unisys.com>
//silverplatter   416/tcp    Silverplatter
//silverplatter   416/udp    Silverplatter
//#                          Peter Ciuffetti <petec&silverplatter.com>
//onmux           417/tcp    Onmux
//onmux           417/udp    Onmux
//#                          Stephen Hanna <hanna&world.std.com>
//hyper-g         418/tcp    Hyper-G
//hyper-g         418/udp    Hyper-G
//#                          Frank Kappe <fkappe&iicm.tu-graz.ac.at>
//ariel1          419/tcp    Ariel 1
//ariel1          419/udp    Ariel 1
//#                          Joel Karafin <jkarafin&infotrieve.com>
//smpte           420/tcp    SMPTE
//smpte           420/udp    SMPTE
//#                          Si Becker <71362.22&CompuServe.COM>
//ariel2          421/tcp    Ariel 2
//ariel2          421/udp    Ariel 2
//ariel3          422/tcp    Ariel 3
//ariel3          422/udp    Ariel 3 
//#                          Joel Karafin <jkarafin&infotrieve.com>
//opc-job-start   423/tcp    IBM Operations Planning and Control Start
//opc-job-start   423/udp    IBM Operations Planning and Control Start
//opc-job-track   424/tcp    IBM Operations Planning and Control Track
//opc-job-track   424/udp    IBM Operations Planning and Control Track
//#                          Conny Larsson  <cocke&VNET.IBM.COM>
//icad-el         425/tcp    ICAD
//icad-el         425/udp    ICAD
//#		           Larry Stone	<lcs&icad.com>
//smartsdp        426/tcp    smartsdp
//smartsdp        426/udp    smartsdp
//#                          Marie-Pierre Belanger <belanger_marie&emc.com>
//svrloc          427/tcp    Server Location
//svrloc          427/udp    Server Location
//#                          <veizades&ftp.com>
//ocs_cmu         428/tcp    OCS_CMU
//ocs_cmu         428/udp    OCS_CMU
//ocs_amu         429/tcp    OCS_AMU
//ocs_amu         429/udp    OCS_AMU
//#                          Florence Wyman <wyman&peabody.plk.af.mil>
//utmpsd          430/tcp    UTMPSD
//utmpsd          430/udp    UTMPSD
//utmpcd          431/tcp    UTMPCD
//utmpcd          431/udp    UTMPCD
//iasd            432/tcp    IASD  
//iasd            432/udp    IASD  
//#                          Nir Baroz <nbaroz&encore.com>
//nnsp            433/tcp    NNSP
//nnsp            433/udp    NNSP
//#                          Rob Robertson <rob&gangrene.berkeley.edu>
//mobileip-agent  434/tcp    MobileIP-Agent
//mobileip-agent  434/udp    MobileIP-Agent
//mobilip-mn      435/tcp    MobilIP-MN
//mobilip-mn      435/udp    MobilIP-MN
//#                          Kannan Alagappan <kannan&sejour.lkg.dec.com>
//dna-cml         436/tcp    DNA-CML   
//dna-cml         436/udp    DNA-CML   
//#                          Dan Flowers <flowers&smaug.lkg.dec.com>
//comscm          437/tcp    comscm
//comscm          437/udp    comscm
//#                          Jim Teague <teague&zso.dec.com>
//dsfgw           438/tcp    dsfgw
//dsfgw           438/udp    dsfgw
//#                          Andy McKeen <mckeen&osf.org>
//dasp            439/tcp    dasp      Thomas Obermair
//dasp            439/udp    dasp      tommy&inlab.m.eunet.de
//#                          Thomas Obermair <tommy&inlab.m.eunet.de>
//sgcp            440/tcp    sgcp      
//sgcp            440/udp    sgcp      
//#                          Marshall Rose <mrose&dbc.mtview.ca.us>
//decvms-sysmgt   441/tcp    decvms-sysmgt
//decvms-sysmgt   441/udp    decvms-sysmgt
//#                          Lee Barton <barton&star.enet.dec.com>
//cvc_hostd       442/tcp    cvc_hostd
//cvc_hostd       442/udp    cvc_hostd
//#                          Bill Davidson <billd&equalizer.cray.com>
//https           443/tcp    http protocol over TLS/SSL
//https           443/udp    http protocol over TLS/SSL
//#                          Kipp E.B. Hickman <kipp&mcom.com>
//https           443/sctp   HTTPS
//#                          IETF TSVWG
//#                          Randall Stewart <rrs&cisco.com>
//#                          [RFC4960]
//snpp            444/tcp    Simple Network Paging Protocol
//snpp            444/udp    Simple Network Paging Protocol
//#                          [RFC1568]
//microsoft-ds    445/tcp    Microsoft-DS
//microsoft-ds    445/udp    Microsoft-DS
//#                          Pradeep Bahl <pradeepb&microsoft.com>
//ddm-rdb         446/tcp    DDM-Remote Relational Database Access
//ddm-rdb         446/udp    DDM-Remote Relational Database Access
//ddm-dfm         447/tcp    DDM-Distributed File Management
//ddm-dfm         447/udp    DDM-Distributed File Management
//#                          Steven Ritland <srr&us.ibm.com>
//ddm-ssl         448/tcp    DDM-Remote DB Access Using Secure Sockets
//ddm-ssl         448/udp    DDM-Remote DB Access Using Secure Sockets
//#			               Steven Ritland <srr&us.ibm.com>
//as-servermap    449/tcp    AS Server Mapper
//as-servermap    449/udp    AS Server Mapper
//#                          Barbara Foss <BGFOSS&rchvmv.vnet.ibm.com>
//tserver         450/tcp    Computer Supported Telecomunication Applications
//tserver         450/udp    Computer Supported Telecomunication Applications
//#                          Harvey S. Schultz <harvey&acm.org>
//sfs-smp-net     451/tcp    Cray Network Semaphore server
//sfs-smp-net     451/udp    Cray Network Semaphore server
//sfs-config	452/tcp    Cray SFS config server
//sfs-config	452/udp    Cray SFS config server
//#                          Walter Poxon <wdp&ironwood.cray.com>
//creativeserver  453/tcp    CreativeServer
//creativeserver  453/udp    CreativeServer
//contentserver   454/tcp    ContentServer
//contentserver   454/udp    ContentServer
//creativepartnr  455/tcp    CreativePartnr
//creativepartnr  455/udp    CreativePartnr
//#                          Jesus Ortiz <jesus_ortiz&emotion.com>
//macon-tcp       456/tcp    macon-tcp
//macon-udp       456/udp    macon-udp
//#                          Yoshinobu Inoue
//#                          <shin&hodaka.mfd.cs.fujitsu.co.jp>
//scohelp         457/tcp    scohelp
//scohelp         457/udp    scohelp
//#                          Faith Zack <faithz&sco.com>
//appleqtc        458/tcp    apple quick time
//appleqtc        458/udp    apple quick time
//#                          Murali Ranganathan 
//#                          <murali_ranganathan&quickmail.apple.com>
//ampr-rcmd       459/tcp    ampr-rcmd              
//ampr-rcmd       459/udp    ampr-rcmd              
//#                          Rob Janssen <rob&sys3.pe1chl.ampr.org>
//skronk          460/tcp    skronk
//skronk          460/udp    skronk
//#                          Henry Strickland <strick&yak.net>
//datasurfsrv     461/tcp    DataRampSrv
//datasurfsrv     461/udp    DataRampSrv
//datasurfsrvsec  462/tcp    DataRampSrvSec
//datasurfsrvsec  462/udp    DataRampSrvSec
//#                          Diane Downie <downie&jibe.MV.COM>
//alpes           463/tcp    alpes
//alpes           463/udp    alpes
//#                          Alain Durand <Alain.Durand&imag.fr>
//kpasswd         464/tcp    kpasswd
//kpasswd         464/udp    kpasswd
//#                          Theodore Ts'o <tytso&MIT.EDU>
//urd             465/tcp    URL Rendesvous Directory for SSM
//igmpv3lite      465/udp    IGMP over UDP for SSM 
//#                          Toerless Eckert <eckert&cisco.com>
//digital-vrc     466/tcp    digital-vrc
//digital-vrc     466/udp    digital-vrc
//#                          Peter Higginson <higginson&mail.dec.com>
//mylex-mapd      467/tcp    mylex-mapd
//mylex-mapd      467/udp    mylex-mapd
//#                          Gary Lewis <GaryL&hq.mylex.com>
//photuris        468/tcp    proturis
//photuris        468/udp    proturis
//#                          Bill Simpson <Bill.Simpson&um.cc.umich.edu>
//rcp             469/tcp    Radio Control Protocol
//rcp             469/udp    Radio Control Protocol
//#                          Jim Jennings +1-708-538-7241
//scx-proxy       470/tcp    scx-proxy
//scx-proxy       470/udp    scx-proxy
//#                          Scott Narveson <sjn&cray.com>
//mondex          471/tcp    Mondex
//mondex          471/udp    Mondex
//#                          Bill Reding <redingb&nwdt.natwest.co.uk>
//ljk-login       472/tcp    ljk-login
//ljk-login       472/udp    ljk-login
//#                          LJK Software, Cambridge, Massachusetts
//#                          <support&ljk.com>
//hybrid-pop      473/tcp    hybrid-pop
//hybrid-pop      473/udp    hybrid-pop
//#                          Rami Rubin <rami&hybrid.com>
//tn-tl-w1        474/tcp    tn-tl-w1
//tn-tl-w2        474/udp    tn-tl-w2
//#                          Ed Kress <eskress&thinknet.com>
//tcpnethaspsrv   475/tcp    tcpnethaspsrv
//tcpnethaspsrv   475/udp    tcpnethaspsrv
//#                          Charlie Hava <charlie&aladdin.co.il>
//tn-tl-fd1       476/tcp    tn-tl-fd1
//tn-tl-fd1       476/udp    tn-tl-fd1
//#                          Ed Kress <eskress&thinknet.com>
//ss7ns           477/tcp    ss7ns
//ss7ns           477/udp    ss7ns
//#                          Jean-Michel URSCH <ursch&taec.enet.dec.com>
//spsc            478/tcp    spsc
//spsc            478/udp    spsc
//#                          Mike Rieker <mikea&sp32.com>
//iafserver       479/tcp    iafserver
//iafserver       479/udp    iafserver
//iafdbase        480/tcp    iafdbase
//iafdbase        480/udp    iafdbase
//#                          ricky&solect.com <Rick Yazwinski>
//ph              481/tcp    Ph service
//ph              481/udp    Ph service
//#                          Roland Hedberg <Roland.Hedberg&umdac.umu.se>
//bgs-nsi         482/tcp    bgs-nsi
//bgs-nsi         482/udp    bgs-nsi
//#                          Jon Saperia <saperia&bgs.com>         
//ulpnet          483/tcp    ulpnet
//ulpnet          483/udp    ulpnet
//#                          Kevin Mooney <kevinm&bfs.unibol.com>
//integra-sme     484/tcp    Integra Software Management Environment
//integra-sme     484/udp    Integra Software Management Environment
//#                          Randall Dow <rand&randix.net>
//powerburst      485/tcp    Air Soft Power Burst
//powerburst      485/udp    Air Soft Power Burst
//#                          <gary&airsoft.com>
//avian           486/tcp    avian
//avian           486/udp    avian
//#                          Robert Ullmann 
//#                          <Robert_Ullmann/CAM/Lotus.LOTUS&crd.lotus.com>
//saft            487/tcp    saft Simple Asynchronous File Transfer
//saft            487/udp    saft Simple Asynchronous File Transfer
//#                          Ulli Horlacher <framstag&rus.uni-stuttgart.de>
//gss-http        488/tcp    gss-http
//gss-http        488/udp    gss-http
//#                          Doug Rosenthal <rosenthl&krypton.einet.net>
//nest-protocol   489/tcp    nest-protocol
//nest-protocol   489/udp    nest-protocol
//#                          Gilles Gameiro <ggameiro&birdland.com>
//micom-pfs       490/tcp    micom-pfs
//micom-pfs       490/udp    micom-pfs
//#                          David Misunas <DMisunas&micom.com>
//go-login        491/tcp    go-login
//go-login        491/udp    go-login
//#                          Troy Morrison <troy&graphon.com>
//ticf-1          492/tcp    Transport Independent Convergence for FNA
//ticf-1          492/udp    Transport Independent Convergence for FNA
//ticf-2          493/tcp    Transport Independent Convergence for FNA
//ticf-2          493/udp    Transport Independent Convergence for FNA
//#                          Mamoru Ito <Ito&pcnet.ks.pfu.co.jp>
//pov-ray         494/tcp    POV-Ray
//pov-ray         494/udp    POV-Ray
//#                          POV-Team Co-ordinator 
//#                          <iana-port.remove-spamguard&povray.org>
//intecourier     495/tcp    intecourier
//intecourier     495/udp    intecourier
//#                          Steve Favor <sfavor&tigger.intecom.com>
//pim-rp-disc     496/tcp    PIM-RP-DISC
//pim-rp-disc     496/udp    PIM-RP-DISC
//#                          Dino Farinacci <dino&cisco.com>
//dantz           497/tcp    dantz
//dantz           497/udp    dantz
//#                          Richard Zulch <richard_zulch&dantz.com>
//siam            498/tcp    siam
//siam            498/udp    siam
//#                          Philippe Gilbert <pgilbert&cal.fr>
//iso-ill         499/tcp    ISO ILL Protocol
//iso-ill         499/udp    ISO ILL Protocol
//#                          Mark H. Needleman <markn&sirsi.com>
//isakmp          500/tcp    isakmp
//isakmp          500/udp    isakmp
//#                          Mark Schertler <mjs&tycho.ncsc.mil>
//stmf            501/tcp    STMF
//stmf            501/udp    STMF
//#                          Alan Ungar <aungar&farradyne.com>
//asa-appl-proto  502/tcp    asa-appl-proto
//asa-appl-proto  502/udp    asa-appl-proto
//#                          Dennis Dube <ddube&modicon.com>
//intrinsa        503/tcp    Intrinsa
//intrinsa        503/udp    Intrinsa
//#                          Robert Ford <robert&intrinsa.com>
//citadel         504/tcp    citadel
//citadel         504/udp    citadel
//#                          Art Cancro <ajc&uncensored.citadel.org>
//mailbox-lm      505/tcp    mailbox-lm
//mailbox-lm      505/udp    mailbox-lm
//#                          Beverly Moody <Beverly_Moody&stercomm.com>
//ohimsrv         506/tcp    ohimsrv
//ohimsrv         506/udp    ohimsrv
//#                          Scott Powell <spowell&openhorizon.com>
//crs             507/tcp    crs
//crs             507/udp    crs
//#                          Brad Wright <bradwr&microsoft.com>
//xvttp           508/tcp    xvttp
//xvttp           508/udp    xvttp
//#                          Keith J. Alphonso <alphonso&ncs-ssc.com>
//snare           509/tcp    snare
//snare           509/udp    snare
//#                          Dennis Batchelder <dennis&capres.com>
//fcp             510/tcp    FirstClass Protocol
//fcp             510/udp    FirstClass Protocol
//#                          Mike Marshburn <paul&softarc.com>
//passgo          511/tcp    PassGo
//passgo          511/udp    PassGo
//#                          John Rainford <jrainford&passgo.com>
//exec            512/tcp    remote process execution;
//#                          authentication performed using
//#                          passwords and UNIX login names
//comsat          512/udp
//biff            512/udp    used by mail system to notify users
//#                          of new mail received; currently
//#                          receives messages only from 
//#                          processes on the same machine
//login           513/tcp    remote login a la telnet;
//#                          automatic authentication performed
//#                          based on priviledged port numbers
//#                          and distributed data bases which
//#                          identify "authentication domains"
//who             513/udp    maintains data bases showing who's
//#                          logged in to machines on a local 
//#                          net and the load average of the
//#                          machine
//shell           514/tcp    cmd
//#                          like exec, but automatic authentication 
//#                          is performed as for login server
//syslog          514/udp
//printer         515/tcp    spooler
//printer         515/udp    spooler
//videotex        516/tcp    videotex
//videotex        516/udp    videotex
//#                          Daniel Mavrakis <system&venus.mctel.fr>
//talk            517/tcp    like tenex link, but across
//#                          machine - unfortunately, doesn't
//#                          use link protocol (this is actually
//#                          just a rendezvous port from which a
//#                          tcp connection is established)
//talk            517/udp    like tenex link, but across
//#                          machine - unfortunately, doesn't
//#                          use link protocol (this is actually
//#                          just a rendezvous port from which a
//#                          tcp connection is established)
//ntalk           518/tcp
//ntalk           518/udp
//utime           519/tcp    unixtime
//utime           519/udp    unixtime
//efs             520/tcp    extended file name server
//router          520/udp    local routing process (on site);
//#                          uses variant of Xerox NS routing
//#                          information protocol - RIP
//ripng           521/tcp    ripng
//ripng           521/udp    ripng
//#                          Robert E. Minnear <minnear&ipsilon.com>
//ulp             522/tcp    ULP    
//ulp             522/udp    ULP    
//#                          Max Morris <maxm&MICROSOFT.com>
//ibm-db2         523/tcp    IBM-DB2
//ibm-db2         523/udp    IBM-DB2
//#                          Juliana Hsu <jhsu&ca.ibm.com>
//ncp             524/tcp    NCP
//ncp             524/udp    NCP    
//#                          Don Provan <donp&sjf.novell.com>
//timed  	        525/tcp    timeserver
//timed           525/udp    timeserver
//tempo	        526/tcp    newdate
//tempo	        526/udp    newdate
//#                          Unknown
//stx             527/tcp    Stock IXChange
//stx             527/udp    Stock IXChange
//custix          528/tcp    Customer IXChange
//custix          528/udp    Customer IXChange
//#                          Ferdi Ladeira <ferdil&fraxion.biz> 
//irc-serv        529/tcp    IRC-SERV
//irc-serv        529/udp    IRC-SERV
//#                          Brian Tackett <cym&acrux.net>
//courier         530/tcp    rpc
//courier         530/udp    rpc
//conference      531/tcp    chat
//conference      531/udp    chat
//netnews         532/tcp    readnews
//netnews         532/udp    readnews
//netwall	        533/tcp    for emergency broadcasts
//netwall	        533/udp    for emergency broadcasts
//#                          Andreas Heidemann <a.heidemann&ais-gmbh.de>
//windream	534/tcp    windream Admin
//windream	534/udp    windream Admin
//#			    Uwe Honermann <u.honermann&windream.com>
//iiop            535/tcp    iiop
//iiop            535/udp    iiop
//#                          Jeff M.Michaud <michaud&zk3.dec.com>
//opalis-rdv      536/tcp    opalis-rdv
//opalis-rdv      536/udp    opalis-rdv
//#                          Laurent Domenech <ldomenech&opalis.com>
//nmsp            537/tcp    Networked Media Streaming Protocol
//nmsp            537/udp    Networked Media Streaming Protocol
//#                          Paul Santinelli Jr. <psantinelli&narrative.com>
//gdomap          538/tcp    gdomap
//gdomap          538/udp    gdomap
//#                          Richard Frith-Macdonald <richard&brainstorm.co.uk>
//apertus-ldp     539/tcp    Apertus Technologies Load Determination
//apertus-ldp     539/udp    Apertus Technologies Load Determination
//uucp	        540/tcp    uucpd		
//uucp	        540/udp    uucpd		
//uucp-rlogin     541/tcp    uucp-rlogin  
//uucp-rlogin     541/udp    uucp-rlogin
//#                          Stuart Lynne <sl&wimsey.com>
//commerce        542/tcp    commerce
//commerce        542/udp    commerce
//#                          Randy Epstein <repstein&hostleasing.net>
//klogin          543/tcp
//klogin          543/udp
//kshell 	        544/tcp    krcmd
//kshell 	        544/udp    krcmd
//appleqtcsrvr    545/tcp    appleqtcsrvr
//appleqtcsrvr    545/udp    appleqtcsrvr
//#                          Murali Ranganathan 
//#                          <Murali_Ranganathan&quickmail.apple.com>
//dhcpv6-client   546/tcp    DHCPv6 Client
//dhcpv6-client   546/udp    DHCPv6 Client
//dhcpv6-server   547/tcp    DHCPv6 Server
//dhcpv6-server   547/udp    DHCPv6 Server
//#                          Jim Bound <bound&zk3.dec.com>
//afpovertcp      548/tcp    AFP over TCP
//afpovertcp      548/udp    AFP over TCP
//#                          Leland Wallace <randall&apple.com>
//idfp            549/tcp    IDFP
//idfp            549/udp    IDFP
//#                          Ramana Kovi <ramana&kovi.com>
//new-rwho        550/tcp    new-who
//new-rwho        550/udp    new-who
//cybercash       551/tcp    cybercash
//cybercash       551/udp    cybercash
//#                          Donald E. Eastlake 3rd <dee&cybercash.com>
//devshr-nts      552/tcp    DeviceShare
//devshr-nts      552/udp    DeviceShare
//#                          Benjamin Rosenberg <brosenberg&advsyscon.com>
//pirp            553/tcp    pirp
//pirp            553/udp    pirp
//#                          D. J. Bernstein <djb&silverton.berkeley.edu>
//rtsp            554/tcp    Real Time Streaming Protocol (RTSP)
//rtsp            554/udp    Real Time Streaming Protocol (RTSP)
//#                          Rob Lanphier <robla&prognet.com>
//dsf             555/tcp
//dsf             555/udp
//remotefs        556/tcp    rfs server
//remotefs        556/udp    rfs server
//openvms-sysipc  557/tcp    openvms-sysipc
//openvms-sysipc  557/udp    openvms-sysipc
//#                          Alan Potter <potter&movies.enet.dec.com>
//sdnskmp         558/tcp    SDNSKMP
//sdnskmp         558/udp    SDNSKMP
//teedtap         559/tcp    TEEDTAP
//teedtap         559/udp    TEEDTAP
//#                          Charlie Limoges <Charlie.Limoges&GDC4S.com>
//rmonitor        560/tcp    rmonitord
//rmonitor        560/udp    rmonitord
//monitor         561/tcp
//monitor         561/udp
//chshell         562/tcp    chcmd
//chshell         562/udp    chcmd
//nntps           563/tcp    nntp protocol over TLS/SSL (was snntp)
//nntps           563/udp    nntp protocol over TLS/SSL (was snntp)
//#                          Kipp E.B. Hickman <kipp&netscape.com>
//9pfs            564/tcp    plan 9 file service
//9pfs            564/udp    plan 9 file service
//whoami          565/tcp    whoami
//whoami          565/udp    whoami
//streettalk      566/tcp    streettalk
//streettalk      566/udp    streettalk
//banyan-rpc      567/tcp    banyan-rpc
//banyan-rpc      567/udp    banyan-rpc
//#                          Tom Lemaire <toml&banyan.com>
//ms-shuttle      568/tcp    microsoft shuttle
//ms-shuttle      568/udp    microsoft shuttle
//#                          Rudolph Balaz <rudolphb&microsoft.com>
//ms-rome         569/tcp    microsoft rome
//ms-rome         569/udp    microsoft rome
//#                          Rudolph Balaz <rudolphb&microsoft.com>
//meter           570/tcp    demon
//meter           570/udp    demon
//meter	        571/tcp    udemon
//meter	        571/udp    udemon
//sonar           572/tcp    sonar
//sonar           572/udp    sonar
//#                          Keith Moore <moore&cs.utk.edu>
//banyan-vip      573/tcp    banyan-vip
//banyan-vip      573/udp    banyan-vip
//#                          Denis Leclerc <DLeclerc&banyan.com>
//ftp-agent       574/tcp    FTP Software Agent System
//ftp-agent       574/udp    FTP Software Agent System
//#                          Michael S. Greenberg <arnoff&ftp.com>
//vemmi           575/tcp    VEMMI
//vemmi           575/udp    VEMMI
//#                          Daniel Mavrakis <mavrakis&mctel.fr>
//ipcd            576/tcp    ipcd
//ipcd            576/udp    ipcd
//vnas            577/tcp    vnas
//vnas            577/udp    vnas
//ipdd            578/tcp    ipdd
//ipdd            578/udp    ipdd
//#                          Jay Farhat <jfarhat&ipass.com>
//decbsrv		579/tcp    decbsrv
//decbsrv		579/udp    decbsrv
//#			   Rudi Martin <movies::martin"@movies.enet.dec.com>
//sntp-heartbeat  580/tcp    SNTP HEARTBEAT
//sntp-heartbeat  580/udp	   SNTP HEARTBEAT
//#			   Louis Mamakos <louie&uu.net>
//bdp		581/tcp    Bundle Discovery Protocol
//bdp		581/udp	   Bundle Discovery Protocol
//#			   Gary Malkin <gmalkin&xylogics.com>
//scc-security    582/tcp    SCC Security
//scc-security    582/udp	   SCC Security
//#			   Prashant Dholakia <prashant&semaphorecom.com>
//philips-vc	583/tcp    Philips Video-Conferencing
//philips-vc	583/udp    Philips Video-Conferencing
//#			   Janna Chang <janna&pmc.philips.com>
//keyserver	584/tcp    Key Server
//keyserver	584/udp	   Key Server
//#			   Gary Howland <gary&systemics.com>
//#		585	   De-registered (25 April 2006)
//#               Use of 585 is not recommended, use 993 instead
//password-chg 	586/tcp    Password Change
//password-chg	586/udp	   Password Change
//submission	587/tcp    Submission
//submission	587/udp    Submission
//#			   [RFC4409]
//cal		588/tcp    CAL
//cal		588/udp    CAL
//#			   Myron Hattig <Myron_Hattig&ccm.jf.intel.com>
//eyelink		589/tcp    EyeLink
//eyelink		589/udp	   EyeLink
//#			   Dave Stampe <dstampe&psych.toronto.edu>
//tns-cml		590/tcp    TNS CML
//tns-cml		590/udp    TNS CML
//#			   Jerome Albin <albin&taec.enet.dec.com>
//http-alt	591/tcp    FileMaker, Inc. - HTTP Alternate (see Port 80)
//http-alt	591/udp    FileMaker, Inc. - HTTP Alternate (see Port 80)
//#			   Clay Maeckel <clay_maeckel&filemaker.com>
//eudora-set	592/tcp    Eudora Set
//eudora-set	592/udp	   Eudora Set
//#			   Randall Gellens <randy&qualcomm.com>
//http-rpc-epmap  593/tcp    HTTP RPC Ep Map
//http-rpc-epmap  593/udp    HTTP RPC Ep Map
//#			   Edward Reus <edwardr&microsoft.com>
//tpip		594/tcp    TPIP
//tpip		594/udp    TPIP
//#			   Brad Spear <spear&platinum.com>
//cab-protocol	595/tcp    CAB Protocol
//cab-protocol	595/udp    CAB Protocol
//#			   Winston Hetherington
//smsd            596/tcp    SMSD
//smsd            596/udp    SMSD
//#                          Wayne Barlow <web&unx.dec.com>
//ptcnameservice	597/tcp    PTC Name Service
//ptcnameservice	597/udp    PTC Name Service
//#                          Yuri Machkasov <yuri&ptc.com>
//sco-websrvrmg3	598/tcp    SCO Web Server Manager 3
//sco-websrvrmg3	598/udp    SCO Web Server Manager 3
//#                          Simon Baldwin <simonb&sco.com>
//acp             599/tcp    Aeolon Core Protocol
//acp             599/udp    Aeolon Core Protocol
//#                          Michael Alyn Miller <iana&aeolon.com>
//ipcserver       600/tcp    Sun IPC server
//ipcserver       600/udp    Sun IPC server
//#                          Bill Schiefelbein <schief&aspen.cray.com>
//syslog-conn     601/tcp    Reliable Syslog Service
//syslog-conn     601/udp    Reliable Syslog Service
//#                          RFC 3195
//xmlrpc-beep     602/tcp    XML-RPC over BEEP
//xmlrpc-beep     602/udp    XML-RPC over BEEP
//#                          RFC3529 <ftp://ftp.isi.edu/in-notes/rfc3529.txt> March 2003
//idxp            603/tcp    IDXP
//idxp            603/udp    IDXP
//#                          RFC4767
//tunnel          604/tcp    TUNNEL
//tunnel          604/udp    TUNNEL
//#                          RFC3620
//soap-beep       605/tcp    SOAP over BEEP
//soap-beep       605/udp    SOAP over BEEP
//#                          RFC4227 <ftp://ftp.isi.edu/in-notes/rfc4227.txt> April 2002
//urm             606/tcp    Cray Unified Resource Manager
//urm             606/udp    Cray Unified Resource Manager
//nqs             607/tcp    nqs
//nqs             607/udp    nqs
//#                          Bill Schiefelbein <schief&aspen.cray.com>
//sift-uft        608/tcp    Sender-Initiated/Unsolicited File Transfer 
//sift-uft        608/udp    Sender-Initiated/Unsolicited File Transfer
//#                          Rick Troth <troth&rice.edu>
//npmp-trap       609/tcp    npmp-trap
//npmp-trap       609/udp    npmp-trap
//npmp-local      610/tcp    npmp-local
//npmp-local      610/udp    npmp-local
//npmp-gui        611/tcp    npmp-gui  
//npmp-gui        611/udp    npmp-gui  
//#                          John Barnes <jbarnes&crl.com>
//hmmp-ind	612/tcp    HMMP Indication
//hmmp-ind	612/udp	   HMMP Indication
//hmmp-op		613/tcp    HMMP Operation
//hmmp-op		613/udp	   HMMP Operation
//#			   Andrew Sinclair <andrsin&microsoft.com>
//sshell		614/tcp    SSLshell
//sshell   	614/udp	   SSLshell
//#			   Simon J. Gerraty <sjg&quick.com.au>
//sco-inetmgr	615/tcp	   Internet Configuration Manager
//sco-inetmgr	615/udp    Internet Configuration Manager
//sco-sysmgr	616/tcp    SCO System Administration Server
//sco-sysmgr	616/udp    SCO System Administration Server
//sco-dtmgr	617/tcp    SCO Desktop Administration Server
//sco-dtmgr	617/udp    SCO Desktop Administration Server
//#			   Christopher Durham <chrisdu&sco.com>
//dei-icda	618/tcp    DEI-ICDA
//dei-icda	618/udp    DEI-ICDA
//#			   David Turner <digital&Quetico.tbaytel.net>
//compaq-evm	619/tcp    Compaq EVM
//compaq-evm	619/udp    Compaq EVM
//#			   Jem Treadwell <Jem.Treadwell&compaq.com>
//sco-websrvrmgr  620/tcp    SCO WebServer Manager
//sco-websrvrmgr  620/udp    SCO WebServer Manager
//#			   Christopher Durham <chrisdu&sco.com>
//escp-ip		621/tcp    ESCP
//escp-ip		621/udp    ESCP
//#			   Lai Zit Seng <lzs&pobox.com>
//collaborator	622/tcp    Collaborator
//collaborator	622/udp	   Collaborator
//#			   Johnson Davis <johnsond&opteamasoft.com>
//oob-ws-http	623/tcp    DMTF out-of-band web services management protocol
//#			   Jim Davis <jim.davis&wbemsolutions.com> June 2007
//asf-rmcp        623/udp    ASF Remote Management and Control Protocol
//#                          Carl First <Carl.L.First&intel.com>
//cryptoadmin	624/tcp    Crypto Admin
//cryptoadmin	624/udp    Crypto Admin
//#			   Tony Walker <tony&cryptocard.com>
//dec_dlm		625/tcp    DEC DLM
//dec_dlm		625/udp    DEC DLM
//#			   Rudi Martin <Rudi.Martin&edo.mts.dec.com>
//asia		626/tcp    ASIA
//asia		626/udp    ASIA
//#			   Michael Dasenbrock <dasenbro&apple.com>
//passgo-tivoli	627/tcp    PassGo Tivoli
//passgo-tivoli	627/udp    PassGo Tivoli
//#			   John Rainford <john.rainford&passgo.com> 
//qmqp		628/tcp    QMQP
//qmqp		628/udp    QMQP
//#			   Dan Bernstein <djb&cr.yp.to>
//3com-amp3	629/tcp    3Com AMP3
//3com-amp3	629/udp    3Com AMP3
//#			   Prakash Banthia <prakash_banthia&3com.com>
//rda		630/tcp    RDA
//rda		630/udp    RDA
//#			   John Hadjioannou <john&minster.co.uk>
//ipp		631/tcp    IPP (Internet Printing Protocol)
//ipp		631/udp    IPP (Internet Printing Protocol)
//#			   Carl-Uno Manros <manros&cp10.es.xerox.com>
//bmpp		632/tcp    bmpp
//bmpp		632/udp    bmpp
//#			   Troy Rollo <troy&kroll.corvu.com.au>	
//servstat	633/tcp    Service Status update (Sterling Software)
//servstat	633/udp    Service Status update (Sterling Software)
//#                          Greg Rose <Greg_Rose&sydney.sterling.com>
//ginad           634/tcp    ginad
//ginad           634/udp    ginad
//#                          Mark Crother <mark&eis.calstate.edu>
//rlzdbase        635/tcp    RLZ DBase
//rlzdbase        635/udp    RLZ DBase
//#                          Michael Ginn <ginn&tyxar.com>
//ldaps           636/tcp    ldap protocol over TLS/SSL (was sldap)
//ldaps           636/udp    ldap protocol over TLS/SSL (was sldap)
//#                          Pat Richard <patr&xcert.com>
//lanserver       637/tcp    lanserver
//lanserver       637/udp    lanserver
//#                          Chris Larsson <clarsson&VNET.IBM.COM>
//mcns-sec	638/tcp    mcns-sec
//mcns-sec	638/udp    mcns-sec
//#			   Kaz Ozawa <k.ozawa&cablelabs.com>
//msdp		639/tcp    MSDP
//msdp		639/udp    MSDP
//#			   Dino Farinacci <dino&cisco.com>
//entrust-sps	640/tcp    entrust-sps
//entrust-sps	640/udp    entrust-sps
//#			   Marek Buchler <Marek.Buchler&entrust.com>
//repcmd		641/tcp    repcmd
//repcmd		641/udp    repcmd
//#			   Scott Dale <scott&Replicase.com>
//esro-emsdp	642/tcp    ESRO-EMSDP V1.3
//esro-emsdp	642/udp    ESRO-EMSDP V1.3
//#			   Mohsen Banan <mohsen&neda.com> 
//sanity		643/tcp    SANity
//sanity		643/udp    SANity
//#			   Peter Viscarola <PeterGV&osr.com>
//dwr		644/tcp    dwr
//dwr		644/udp    dwr
//#			   Bill Fenner <fenner&parc.xerox.com>
//pssc		645/tcp    PSSC
//pssc		645/udp    PSSC
//#			   Egon Meier-Engelen <egon.meier-engelen&dlr.de>
//ldp		646/tcp    LDP
//ldp		646/udp    LDP
//#			   Bob Thomas <rhthomas&cisco.com>
//dhcp-failover   647/tcp    DHCP Failover
//dhcp-failover   647/udp    DHCP Failover
//#                          Bernard Volz <volz&cisco.com> 
//rrp             648/tcp    Registry Registrar Protocol (RRP)
//rrp             648/udp    Registry Registrar Protocol (RRP)
//#                          Scott Hollenbeck <shollenb&netsol.com>	
//cadview-3d      649/tcp    Cadview-3d - streaming 3d models over the internet
//cadview-3d      649/udp    Cadview-3d - streaming 3d models over the internet
//#                          David Cooper <david.cooper&oracle.com> 
//obex		650/tcp    OBEX
//obex		650/udp    OBEX
//#			   Jeff Garbers <FJG030&email.mot.com>
//ieee-mms	651/tcp    IEEE MMS
//ieee-mms	651/udp    IEEE MMS
//#			   Curtis Anderson <canderson&turbolinux.com>
//hello-port	652/tcp    HELLO_PORT
//hello-port	652/udp    HELLO_PORT	
//#			   Patrick Cipiere <Patrick.Cipiere&UDcast.com>
//repscmd		653/tcp    RepCmd
//repscmd		653/udp    RepCmd
//#			   Scott Dale <scott&tioga.com>
//aodv		654/tcp	   AODV
//aodv		654/udp	   AODV
//#			   Charles Perkins <cperkins&eng.sun.com>
//tinc		655/tcp    TINC
//tinc		655/udp    TINC
//#			   Ivo Timmermans <itimmermans&bigfoot.com>
//spmp		656/tcp    SPMP
//spmp		656/udp    SPMP
//#			   Jakob Kaivo <jkaivo&nodomainname.net>
//rmc		657/tcp    RMC
//rmc		657/udp    RMC
//#			   Michael Schmidt <mmaass&us.ibm.com>
//tenfold		658/tcp    TenFold
//tenfold		658/udp    TenFold
//#			   Louis Olszyk <lolszyk&10fold.com>
//#               659        Removed (2001-06-06)
//mac-srvr-admin  660/tcp    MacOS Server Admin
//mac-srvr-admin  660/udp    MacOS Server Admin
//#                          Forest Hill <forest&apple.com>
//hap             661/tcp    HAP
//hap             661/udp    HAP
//#                          Igor Plotnikov <igor&uroam.com>
//pftp            662/tcp    PFTP
//pftp            662/udp    PFTP
//#                          Ben Schluricke <support&pftp.de>
//purenoise       663/tcp    PureNoise
//purenoise       663/udp    PureNoise
//#                          Sam Osa <pristine&mailcity.com>
//oob-ws-https	664/tcp    DMTF out-of-band secure web services management protocol
//#			    Jim Davis <jim.davis&wbemsolutions.com> June 2007
//asf-secure-rmcp 664/udp    ASF Secure Remote Management and Control Protocol
//#                          Carl First <Carl.L.First&intel.com>
//sun-dr          665/tcp    Sun DR
//sun-dr          665/udp    Sun DR
//#                          Harinder Bhasin <Harinder.Bhasin&Sun.COM>
//mdqs            666/tcp	
//mdqs            666/udp	
//doom            666/tcp    doom Id Software
//doom            666/udp    doom Id Software
//#                          <ddt&idcube.idsoftware.com>
//disclose        667/tcp    campaign contribution disclosures - SDR Technologies
//disclose        667/udp    campaign contribution disclosures - SDR Technologies
//#                          Jim Dixon  <jim&lambda.com>
//mecomm          668/tcp    MeComm
//mecomm          668/udp    MeComm
//meregister      669/tcp    MeRegister
//meregister      669/udp    MeRegister
//#                          Armin Sawusch <armin&esd1.esd.de>
//vacdsm-sws      670/tcp    VACDSM-SWS
//vacdsm-sws      670/udp    VACDSM-SWS
//vacdsm-app      671/tcp    VACDSM-APP
//vacdsm-app      671/udp    VACDSM-APP
//vpps-qua        672/tcp    VPPS-QUA
//vpps-qua        672/udp    VPPS-QUA
//cimplex         673/tcp    CIMPLEX
//cimplex         673/udp    CIMPLEX
//#                          Ulysses G. Smith Jr. <ugsmith&cesi.com>
//acap            674/tcp    ACAP
//acap            674/udp	   ACAP
//#                          Chris Newman <chris.newman&sun.com>
//dctp		675/tcp    DCTP
//dctp		675/udp    DCTP
//#			   Andre Kramer <Andre.Kramer&ansa.co.uk>
//vpps-via	676/tcp    VPPS Via
//vpps-via	676/udp    VPPS Via
//#			   Ulysses G. Smith Jr. <ugsmith&cesi.com>
//vpp		677/tcp    Virtual Presence Protocol 
//vpp		677/udp    Virtual Presence Protocol 
//#			   Klaus Wolf <wolf&cobrow.com>
//ggf-ncp		678/tcp    GNU Generation Foundation NCP
//ggf-ncp		678/udp    GNU Generation Foundation NCP
//#			   Noah Paul <noahp&altavista.net>
//mrm             679/tcp    MRM
//mrm             679/udp    MRM
//#                          Liming Wei <lwei&cisco.com>
//entrust-aaas	680/tcp    entrust-aaas 
//entrust-aaas	680/udp    entrust-aaas 
//entrust-aams	681/tcp    entrust-aams
//entrust-aams	681/udp    entrust-aams
//#                          Adrian Mancini <adrian.mancini&entrust.com>
//xfr             682/tcp    XFR
//xfr             682/udp    XFR
//#                          Noah Paul <noahp&ultranet.com>
//corba-iiop      683/tcp    CORBA IIOP 
//corba-iiop      683/udp    CORBA IIOP 
//corba-iiop-ssl	684/tcp    CORBA IIOP SSL
//corba-iiop-ssl	684/udp    CORBA IIOP SSL
//#                          Andrew Watson <andrew&omg.org>
//mdc-portmapper	685/tcp    MDC Port Mapper
//mdc-portmapper	685/udp    MDC Port Mapper
//#                          Noah Paul <noahp&altavista.net>
//hcp-wismar      686/tcp    Hardware Control Protocol Wismar
//hcp-wismar      686/udp    Hardware Control Protocol Wismar
//#                          David Merchant <d.f.merchant&livjm.ac.uk>	
//asipregistry	687/tcp    asipregistry
//asipregistry	687/udp    asipregistry
//#                          Erik Sea <sea&apple.com>
//realm-rusd      688/tcp    ApplianceWare managment protocol
//realm-rusd      688/udp    ApplianceWare managment protocol
//#                          Stacy Kenworthy <skenworthy&applianceware.com>
//nmap            689/tcp    NMAP
//nmap            689/udp    NMAP
//#                          Peter Dennis Bartok <peter&novonyx.com>
//vatp            690/tcp    Velazquez Application Transfer Protocol
//vatp            690/udp    Velazquez Application Transfer Protocol
//#                          Velneo <velneo&velneo.com>
//msexch-routing	691/tcp    MS Exchange Routing
//msexch-routing	691/udp    MS Exchange Routing
//#                          David Lemson <dlemson&microsoft.com>
//hyperwave-isp	692/tcp    Hyperwave-ISP
//hyperwave-isp	692/udp    Hyperwave-ISP
//#                          Gerald Mesaric <gmesaric&hyperwave.com>
//connendp        693/tcp    almanid Connection Endpoint
//connendp        693/udp    almanid Connection Endpoint
//#                          Ronny Bremer <rbremer&almanid.com>
//ha-cluster      694/tcp    ha-cluster
//ha-cluster      694/udp    ha-cluster
//#                          Alan Robertson <alanr&unix.sh>
//ieee-mms-ssl    695/tcp    IEEE-MMS-SSL
//ieee-mms-ssl    695/udp    IEEE-MMS-SSL
//#                          Curtis Anderson <ecanderson&turbolinux.com> 
//rushd           696/tcp    RUSHD
//rushd           696/udp    RUSHD
//#                          Greg Ercolano <erco&netcom.com>
//uuidgen         697/tcp    UUIDGEN
//uuidgen         697/udp    UUIDGEN
//#                          James Falkner <james.falkner&sun.com>
//olsr            698/tcp    OLSR
//olsr            698/udp    OLSR
//#                          Thomas Clausen <thomas.clausen&inria.fr>   
//accessnetwork   699/tcp    Access Network
//accessnetwork   699/udp    Access Network
//#                          Yingchun Xu <Yingchun_Xu&3com.com>
//epp             700/tcp    Extensible Provisioning Protocol
//epp             700/udp    Extensible Provisioning Protocol
//#                          [RFC4934]
//lmp             701/tcp    Link Management Protocol (LMP)
//lmp             701/udp    Link Management Protocol (LMP)
//#                          [RFC4204]
//iris-beep       702/tcp    IRIS over BEEP
702,//iris-beep       702/udp    IRIS over BEEP
//#                          [RFC3983] 
//#               703        Unassigned
704,//elcsd	        704/tcp    errlog copy/server daemon
//elcsd	        704/udp    errlog copy/server daemon
//agentx	        705/tcp    AgentX
//agentx          705/udp    AgentX
//#                          Bob Natale <bob.natale&appliedsnmp.com>
//silc            706/tcp    SILC
//silc            706/udp    SILC
//#                          Pekka Riikonen <priikone&poseidon.pspt.fi>	
//borland-dsj     707/tcp    Borland DSJ
707,//borland-dsj     707/udp	   Borland DSJ
//#                          Gerg Cole <gcole&corp.borland.com>
//#               708        Unassigned
709,//entrust-kmsh    709/tcp    Entrust Key Management Service Handler
//entrust-kmsh    709/udp    Entrust Key Management Service Handler
//entrust-ash     710/tcp    Entrust Administration Service Handler
//entrust-ash     710/udp    Entrust Administration Service Handler
//#                          Peter Whittaker <pww&entrust.com>
//cisco-tdp       711/tcp    Cisco TDP
//cisco-tdp       711/udp    Cisco TDP
//#                          Bruce Davie <bsd&cisco.com>
//tbrpf           712/tcp    TBRPF
//tbrpf           712/udp    TBRPF
//#                          RFC3684
//iris-xpc	713/tcp    IRIS over XPC 
//iris-xpc	713/udp    IRIS over XPC 
//iris-xpcs	714/tcp    IRIS over XPCS
//iris-xpcs	714/udp    IRIS over XPCS
//#			   [RFC4992]
//iris-lwz	715/tcp    IRIS-LWZ
//iris-lwz	715/udp    IRIS-LWZ
//#			   [RFC4993]
716,//pana            716/udp    PANA Messages
//#                          [RFC5191]
//#               717-728    Unassigned
729,//netviewdm1      729/tcp    IBM NetView DM/6000 Server/Client
//netviewdm1      729/udp    IBM NetView DM/6000 Server/Client
//netviewdm2      730/tcp    IBM NetView DM/6000 send/tcp
//netviewdm2      730/udp    IBM NetView DM/6000 send/tcp
//netviewdm3      731/tcp    IBM NetView DM/6000 receive/tcp
731,//netviewdm3      731/udp    IBM NetView DM/6000 receive/tcp
//#                          Philippe Binet  (phbinet&vnet.IBM.COM)
//#               732-740    Unassigned           
741,//netgw           741/tcp    netGW
//netgw           741/udp    netGW
//#                          Oliver Korfmacher (okorf&netcs.com)
//netrcs          742/tcp    Network based Rev. Cont. Sys.
742,//netrcs          742/udp    Network based Rev. Cont. Sys.
//#                          Gordon C. Galligher <gorpong&ping.chi.il.us>
//#               743        Unassigned
744,//flexlm          744/tcp    Flexible License Manager
744,//flexlm          744/udp    Flexible License Manager
//#                          Matt Christiano
//#                          <globes@matt&oliveb.atc.olivetti.com> 
//#               745-746    Unassigned
747,//fujitsu-dev     747/tcp    Fujitsu Device Control
//fujitsu-dev     747/udp    Fujitsu Device Control
//ris-cm          748/tcp    Russell Info Sci Calendar Manager
//ris-cm          748/udp    Russell Info Sci Calendar Manager
//kerberos-adm    749/tcp    kerberos administration
//kerberos-adm    749/udp    kerberos administration
//rfile 	        750/tcp
//loadav          750/udp
//kerberos-iv     750/udp    kerberos version iv
//#                          Martin Hamilton <martin&mrrl.lut.as.uk>
//pump	        751/tcp
//pump	        751/udp
//qrh             752/tcp
//qrh             752/udp
//rrh    	        753/tcp
//rrh             753/udp
//tell	        754/tcp	   send
754,//tell	        754/udp	   send
//#                          Josyula R. Rao <jrrao&watson.ibm.com>
//#               755-756    Unassigned
758,//nlogin	        758/tcp
//nlogin	        758/udp
//con             759/tcp
//con             759/udp
//ns              760/tcp
//ns              760/udp
//rxe             761/tcp
//rxe             761/udp
//quotad	        762/tcp
//quotad	        762/udp
//cycleserv       763/tcp
//cycleserv       763/udp
//omserv	        764/tcp
//omserv	        764/udp
//webster	        765/tcp
765,//webster	        765/udp
//#                          Josyula R. Rao <jrrao&watson.ibm.com>
//#               766        Unassigned
767,//phonebook       767/tcp	   phone
767,//phonebook       767/udp	   phone
//#                          Josyula R. Rao <jrrao&watson.ibm.com>
//#               768        Unassigned
769,//vid             769/tcp
//vid             769/udp
//cadlock         770/tcp
//cadlock         770/udp
//rtip 	        771/tcp
//rtip 	        771/udp
//cycleserv2      772/tcp
//cycleserv2      772/udp
//submit	        773/tcp
//notify	        773/udp
//rpasswd	        774/tcp
//acmaint_dbd     774/udp
//entomb	        775/tcp
//acmaint_transd	775/udp
//wpages          776/tcp
//wpages          776/udp
//#                          Josyula R. Rao <jrrao&watson.ibm.com>
//multiling-http	777/tcp    Multiling HTTP
777,//multiling-http	777/udp    Multiling HTTP
//#                          Alejandro Bonet <babel&ctv.es>
//#               778-779    Unassigned
778,//wpgs            780/tcp
778,//wpgs            780/udp
//#                          Josyula R. Rao <jrrao&watson.ibm.com>
//#               781-785    Unassigned
//#               786        Unassigned (Removed 2002-05-08)
//#               787        Unassigned (Removed 2002-10-08)
//#               788-799    Unassigned
800,//mdbs_daemon	800/tcp	
//mdbs_daemon	800/udp	
//device		801/tcp
801,//device		801/udp
//#		802-809    Unassigned
810,//fcp-udp		810/tcp    FCP
810,//fcp-udp		810/udp    FCP Datagram
//#			   Paul Whittemore <paul&softarc.com>
//#		811-827    Unassigned
828,//itm-mcell-s	828/tcp    itm-mcell-s
//itm-mcell-s	828/udp    itm-mcell-s
//#			   Portnoy Boxman <portnoy_boxman&bmc.com>
//pkix-3-ca-ra	829/tcp    PKIX-3 CA/RA
//pkix-3-ca-ra    829/udp    PKIX-3 CA/RA
//#			   Carlisle Adams <Cadams&entrust.com>
//netconf-ssh     830/tcp    NETCONF over SSH
//netconf-ssh     830/udp    NETCONF over SSH
//#                          [RFC4742]
//netconf-beep    831/tcp    NETCONF over BEEP 
//netconf-beep    831/udp    NETCONF over BEEP
//#                          [RFC4744]
//netconfsoaphttp 832/tcp    NETCONF for SOAP over HTTPS
//netconfsoaphttp 832/udp    NETCONF for SOAP over HTTPS
//#                          [RFC4743]
//netconfsoapbeep 833/tcp    NETCONF for SOAP over BEEP
833,//netconfsoapbeep 833/udp    NETCONF for SOAP over BEEP
//#                          [RFC4743]
//#               834-846    Unassigned
847,//dhcp-failover2  847/tcp    dhcp-failover 2
//dhcp-failover2  847/udp    dhcp-failover 2
//#                          Bernard Volz <volz&cisco.com> 
//gdoi            848/tcp    GDOI
//gdoi            848/udp    GDOI
849,//#                          [RFC3547]
//#               849-859    Unassigned
860,//iscsi           860/tcp    iSCSI
//iscsi           860/udp    iSCSI
//#                          RFC3720
//owamp-control   861/tcp    OWAMP-Control
//owamp-control   861/udp    OWAMP-Control
//#                          [RFC4656]
//twamp-control   862/tcp    Two-way Active Measurement Protocol (TWAMP) Control
862,//twamp-control   862/udp    Two-way Active Measurement Protocol (TWAMP) Control
//#                          [RFC5357]
//#               863-872    Unassigned
873,//rsync           873/tcp    rsync
873,//rsync           873/udp    rsync
//#                          Andrew Tridgell <tridge&samba.anu.edu.au>
//#               874-885    Unassigned
886,//iclcnet-locate  886/tcp    ICL coNETion locate server
//iclcnet-locate  886/udp    ICL coNETion locate server
//#                          Bob Lyon <bl&oasis.icl.co.uk>
//iclcnet_svinfo  887/tcp    ICL coNETion server info
//iclcnet_svinfo  887/udp    ICL coNETion server info
//#                          Bob Lyon <bl&oasis.icl.co.uk>
//accessbuilder   888/tcp    AccessBuilder
//accessbuilder   888/udp    AccessBuilder
//#                          Steve Sweeney <Steven_Sweeney&3mail.3com.com>
//# The following entry records an unassigned but widespread use
888,//cddbp           888/tcp    CD Database Protocol
//#                          Steve Scherf <steve&moonsoft.com>
//#
//#		889-899    Unassigned
900,//omginitialrefs  900/tcp    OMG Initial Refs
//omginitialrefs  900/udp    OMG Initial Refs
//#			   Christian Callsen <Christian.Callsen&eng.sun.com>
//smpnameres      901/tcp    SMPNAMERES
//smpnameres      901/udp    SMPNAMERES
//#                          Leif Ekblad <leif&rdos.net>
//ideafarm-door   902/tcp    self documenting Telnet Door
//ideafarm-door   902/udp    self documenting Door: send 0x00 for info
//ideafarm-panic  903/tcp    self documenting Telnet Panic Door
903,//ideafarm-panic  903/udp    self documenting Panic Door: send 0x00 for info
//#                          Wo'o Ideafarm <b85f3c23.9ad6f42c&ideafarm.com> 
//#               904-909    Unassigned
910,//kink            910/tcp    Kerberized Internet Negotiation of Keys (KINK) 
//kink            910/udp    Kerberized Internet Negotiation of Keys (KINK)
//#                          [RFC4430]  
//xact-backup     911/tcp    xact-backup
//xact-backup     911/udp    xact-backup
//#                          Bill Carroll <billc&xactlabs.com>
//apex-mesh       912/tcp    APEX relay-relay service
//apex-mesh       912/udp    APEX relay-relay service
//apex-edge       913/tcp    APEX endpoint-relay service
913,//apex-edge       913/udp    APEX endpoint-relay service    
//#                          [RFC3340]
//#               914-988    Unassigned
989,//ftps-data	989/tcp    ftp protocol, data, over TLS/SSL
//ftps-data	989/udp    ftp protocol, data, over TLS/SSL
//ftps		990/tcp    ftp protocol, control, over TLS/SSL
//ftps		990/udp    ftp protocol, control, over TLS/SSL
//#			   Christopher Allen <ChristopherA&consensus.com>
//nas		991/tcp    Netnews Administration System
//nas		991/udp    Netnews Administration System
//#			   Vera Heinau <heinau&fu-berlin.de>
//#			   Heiko Schlichting <heiko&fu-berlin.de>
//telnets		992/tcp    telnet protocol over TLS/SSL
//telnets		992/udp    telnet protocol over TLS/SSL
//imaps		993/tcp    imap4 protocol over TLS/SSL
//imaps		993/udp    imap4 protocol over TLS/SSL
//ircs		994/tcp    irc protocol over TLS/SSL
//ircs		994/udp    irc protocol over TLS/SSL
//#			   Christopher Allen <ChristopherA&consensus.com>
//pop3s           995/tcp    pop3 protocol over TLS/SSL (was spop3)
//pop3s           995/udp    pop3 protocol over TLS/SSL (was spop3)
//#                          Gordon Mangione <gordm&microsoft.com>
//vsinet          996/tcp    vsinet
//vsinet          996/udp    vsinet
//#                          Rob Juergens <robj&vsi.com>
//maitrd		997/tcp
//maitrd		997/udp
//busboy		998/tcp
//puparp		998/udp
//garcon		999/tcp
//applix		999/udp	   Applix ac
//puprouter	999/tcp
//puprouter	999/udp
//cadlock2	1000/tcp
1000,//cadlock2	1000/udp
//#               1001-1009  Unassigned
//#		1008/udp   Possibly used by Sun Solaris????
1010,//surf		1010/tcp   surf
//surf		1010/udp   surf
//#			   Joseph Geer <jgeer&peapod.com>	 
//#		1011-1020  Reserved
//exp1            1021/tcp   RFC3692-style Experiment 1 (*)    [RFC4727]
//exp1            1021/udp   RFC3692-style Experiment 1 (*)    [RFC4727]
//exp2            1022/tcp   RFC3692-style Experiment 2 (*)    [RFC4727]
//exp2            1022/udp   RFC3692-style Experiment 2 (*)    [RFC4727]
//                1023/tcp   Reserved
//	        1023/udp   Reserved
//#                          IANA <iana&iana.org>
//
//(*) It is only appropriate to use these values in explicitly-
//    configured experiments; they MUST NOT be shipped as defaults in
//    implementations.  See RFC 3692 for details.
//
//
//
//
//
//
//REGISTERED PORT NUMBERS
//
//The Registered Ports are listed by the IANA and on most systems can be
//used by ordinary user processes or programs executed by ordinary
//users.
//
//Ports are used in the TCP [RFC793] to name the ends of logical
//connections which carry long term conversations.  For the purpose of
//providing services to unknown callers, a service contact port is
//defined.  This list specifies the port used by the server process as
//its contact port.
//
//The IANA registers uses of these ports as a convenience to the
//community.
//
//To the extent possible, these same port assignments are used with the
//UDP [RFC768].
//
//The Registered Ports are in the range 1024-49151.
//
//Port Assignments:
//
//Keyword         Decimal    Description                     References
//-------         -------    -----------                     ----------
//                1024/tcp   Reserved		
//                1024/udp   Reserved             
//#                          IANA <iana&iana.org>
//blackjack       1025/tcp   network blackjack
//blackjack       1025/udp   network blackjack
//#                          Unknown contact
//cap             1026/tcp   Calendar Access Protocol
1026,//cap             1026/udp   Calendar Access Protocol
//#                          Doug Royer <Doug&Royer.com> June 2002
//#               1027/tcp   Unassigned (Removed on 2005-09-16)
//#               1028       Deprecated February 2004
1029,//solid-mux       1029/tcp   Solid Mux Server
//solid-mux       1029/udp   Solid Mux Server
//#                          Anders Borg <anders.borg&solid.se> November 2004
//iad1            1030/tcp   BBN IAD
//iad1            1030/udp   BBN IAD
//iad2            1031/tcp   BBN IAD
//iad2            1031/udp   BBN IAD
//iad3            1032/tcp   BBN IAD
//iad3            1032/udp   BBN IAD
//#                          Andy Malis <malis_a&timeplex.com>
//netinfo-local   1033/tcp   local netinfo port
//netinfo-local   1033/udp   local netinfo port
//#                          Marc Majka <majka&apple.com> August 2002
//activesync      1034/tcp   ActiveSync Notifications
//activesync      1034/udp   ActiveSync Notifications
//#                          Sandra Vargas <Sandrama&microsoft.com> March 2003
//mxxrlogin       1035/tcp   MX-XR RPC
//mxxrlogin       1035/udp   MX-XR RPC
//#                          Arnold E. Mauer <amauer&vrms.com> April 2003
//nsstp           1036/tcp   Nebula Secure Segment Transfer Protocol
//nsstp           1036/udp   Nebula Secure Segment Transfer Protocol
//#                          Steve Ravida <steve.ravida&nebulaholdings.com>
//ams             1037/tcp   AMS
//ams             1037/udp   AMS
//#                          Ronald R. Ohmer <rohmer&aisconsulting.net> October 2003 / February 2004
//mtqp            1038/tcp   Message Tracking Query Protocol
//mtqp            1038/udp   Message Tracking Query Protocol
//#                          [RFC3887]
//sbl             1039/tcp   Streamlined Blackhole
//sbl             1039/udp   Streamlined Blackhole
//#                          Jonathan A. Zdziaraski <jonathan&nuclearelephant.com> November 2004
//netarx          1040/tcp   Netarx Netcare
//netarx          1040/udp   Netarx Netcare
//#                          Previous Contact: Fredrick Paul Eisele <phreed&netarx.com>
//#                          Current Contact: Sandy Kronenberg <sandy&netarx.com> 03 April 2008
//danf-ak2        1041/tcp   AK2 Product
//danf-ak2        1041/udp   AK2 Product
//#                          Karl Palsson <karl_p&danfoss.com> November 2004
//afrog           1042/tcp   Subnet Roaming
//afrog           1042/udp   Subnet Roaming
//#                          Michael Chapman <mchapman&fortresstech.com> November 2004
//boinc-client    1043/tcp   BOINC Client Control
//boinc-client    1043/udp   BOINC Client Control
//#                          David Anderson <davea&ssl.berkeley.edu> November 2004
//dcutility       1044/tcp   Dev Consortium Utility
//dcutility       1044/udp   Dev Consortium Utility
//#                          Chris Ryland <cpr&emsoftware.com> November 2004
//fpitp           1045/tcp   Fingerprint Image Transfer Protocol
//fpitp           1045/udp   Fingerprint Image Transfer Protocol
//#                          Steven Fields <sfields&identix.com> February 2002
//wfremotertm     1046/tcp   WebFilter Remote Monitor
//wfremotertm     1046/udp   WebFilter Remote Monitor
//#                          Tim Morgan <timm&surfcontrol.com> November 2004
//neod1           1047/tcp   Sun's NEO Object Request Broker
//neod1           1047/udp   Sun's NEO Object Request Broker
//neod2           1048/tcp   Sun's NEO Object Request Broker
//neod2           1048/udp   Sun's NEO Object Request Broker
//#                          Rohit Garg <rohit.garg&eng.sun.com>
//td-postman      1049/tcp   Tobit David Postman VPMN
//td-postman      1049/udp   Tobit David Postman VPMN
//#                          Franz-Josef Leuders <development&tobit.com>
//cma             1050/tcp   CORBA Management Agent
//cma             1050/udp   CORBA Management Agent
//#                          Ramy Zaarour <ramy&lumos.com>  
//optima-vnet     1051/tcp   Optima VNET
//optima-vnet     1051/udp   Optima VNET
//#                          Ralf Doewich <ralf.doewich&optimatele.com>
//ddt             1052/tcp   Dynamic DNS Tools
//ddt             1052/udp   Dynamic DNS Tools
//#                          Remi Lefebvre <remi&debian.org>
//remote-as       1053/tcp   Remote Assistant (RA)
//remote-as       1053/udp   Remote Assistant (RA)
//#                          Roman Kriis <roman&previo.ee>   
//brvread         1054/tcp   BRVREAD
//brvread         1054/udp   BRVREAD
//#                          A. Boninn <aboninn&hotmail.com>
//ansyslmd        1055/tcp   ANSYS - License Manager 
//ansyslmd        1055/udp   ANSYS - License Manager
//#                          Suzanne Lorrin <suzanne.lorrin&ansys.com>
//vfo             1056/tcp   VFO
//vfo             1056/udp   VFO 
//#                          Anthony Gonzalez <agonzal1&telcordia.com>
//startron        1057/tcp   STARTRON
//startron        1057/udp   STARTRON
//#                          Markus Sabadello <sabadello&startron.org> 
//nim             1058/tcp   nim
//nim             1058/udp   nim
//nimreg          1059/tcp   nimreg
//nimreg          1059/udp   nimreg
//#                          Robert Gordon <rbg&austin.ibm.com>
//polestar        1060/tcp   POLESTAR
//polestar        1060/udp   POLESTAR
//#                          Masakuni Okada <masakuni&jp.ibm.com>
//kiosk           1061/tcp   KIOSK
//kiosk           1061/udp   KIOSK
//#                          Ken Ksiazek <kksiazek&maytag.com>
//veracity        1062/tcp   Veracity
//veracity        1062/udp   Veracity
//#                          Ross Williams <ross&rocksoft.com>
//kyoceranetdev   1063/tcp   KyoceraNetDev
//kyoceranetdev   1063/udp   KyoceraNetDev
//#                          Shigenaka Kanemitsu 
//#                          <Shigenaka_Kanemitsu&ypd.kyocera.co.jp>
//jstel           1064/tcp   JSTEL
//jstel           1064/udp   JSTEL
//#                          Duane Kiser <dkiser&jsexpress.com> 
//syscomlan       1065/tcp   SYSCOMLAN
//syscomlan       1065/udp   SYSCOMLAN
//#                          Previous contact: Urs Ryf <urs.ryf&selectron.ch>
//#                          Current contact: Alexandre Lechenne <alexandre.lechenne&selectron.ch> 10 December 2008
//fpo-fns         1066/tcp   FPO-FNS
//fpo-fns         1066/udp   FPO-FNS
//#                          Jens Klose <jklose&intercope.com>
//instl_boots     1067/tcp   Installation Bootstrap Proto. Serv. 
//instl_boots     1067/udp   Installation Bootstrap Proto. Serv. 
//instl_bootc     1068/tcp   Installation Bootstrap Proto. Cli.  
//instl_bootc     1068/udp   Installation Bootstrap Proto. Cli.  
//#                          David Arko <darko&hpfcrn.fc.hp.com>
//cognex-insight  1069/tcp   COGNEX-SSLMGR
//cognex-insight  1069/udp   COGNEX-SSLMGR
//#                          Steve Olson <solson&cognex.com>
//gmrupdateserv   1070/tcp   GMRUpdateSERV
//gmrupdateserv   1070/udp   GMRUpdateSERV
//#                          Steve Kellogg <stevekellogg&mezzogmr.com>
//bsquare-voip    1071/tcp   BSQUARE-VOIP
//bsquare-voip    1071/udp   BSQUARE-VOIP
//#                          Yen Lee <YenL&bsquare.com>
//cardax          1072/tcp   CARDAX
//cardax          1072/udp   CARDAX
//#                          Charles Oram <charleso&cardax.com>
//bridgecontrol   1073/tcp   Bridge Control
//bridgecontrol   1073/udp   Bridge Control
//#                          Andy Heron <btexact.ports&bt.com>
//warmspotMgmt    1074/tcp   Warmspot Management Protocol
//warmspotMgmt    1074/udp   Warmspot Management Protocol
//#                          Robert C. Henningsgard <rhenn_iana&laptwo.com>
//rdrmshc         1075/tcp   RDRMSHC
//rdrmshc         1075/udp   RDRMSHC
//#                          Ericko Shimada <eriko&kel.fujitsu.co.jp> 
//dab-sti-c       1076/tcp   DAB STI-C
//dab-sti-c       1076/udp   DAB STI-C
//#                          World DAB <worlddab_irc&worlddab.org>
//imgames         1077/tcp   IMGames
//imgames         1077/udp   IMGames
//#                          Jean A. Ames <engr-admin&flipside.com>
//avocent-proxy   1078/tcp   Avocent Proxy Protocol
//avocent-proxy   1078/udp   Avocent Proxy Protocol
//#                          Steven W. Clark <steven.clark&avocent.com> 
//asprovatalk     1079/tcp   ASPROVATalk
//asprovatalk     1079/udp   ASPROVATalk
//#                          Chiew Farn Chung <cfchung&asprova.com>
//socks           1080/tcp   Socks    
//socks           1080/udp   Socks    
//#                          Ying-Da Lee <ylee&syl.dl.nec.com
//pvuniwien       1081/tcp   PVUNIWIEN
//pvuniwien       1081/udp   PVUNIWIEN
//#                          Peter Lipp >Peter.Lipp&iaik.at>
//amt-esd-prot    1082/tcp   AMT-ESD-PROT
//amt-esd-prot    1082/udp   AMT-ESD-PROT 
//#                          AMTEC S.p.A <sp.amtec&interbusiness.it>
//ansoft-lm-1     1083/tcp   Anasoft License Manager
//ansoft-lm-1     1083/udp   Anasoft License Manager
//ansoft-lm-2     1084/tcp   Anasoft License Manager
//ansoft-lm-2     1084/udp   Anasoft License Manager
//webobjects	1085/tcp   Web Objects
//webobjects	1085/udp   Web Objects
//#			   Andy Belk <abelk&apple.com>
//cplscrambler-lg 1086/tcp   CPL Scrambler Logging
//cplscrambler-lg 1086/udp   CPL Scrambler Logging
//cplscrambler-in 1087/tcp   CPL Scrambler Internal
//cplscrambler-in 1087/udp   CPL Scrambler Internal 
//cplscrambler-al 1088/tcp   CPL Scrambler Alarm Log
//cplscrambler-al 1088/udp   CPL Scrambler Alarm Log
//#                          Richard Corn <rac&racc.com> 
//ff-annunc       1089/tcp   FF Annunciation 
//ff-annunc       1089/udp   FF Annunciation 
//ff-fms          1090/tcp   FF Fieldbus Message Specification 
//ff-fms          1090/udp   FF Fieldbus Message Specification
//ff-sm           1091/tcp   FF System Management
//ff-sm           1091/udp   FF System Management
//#                          Fieldbus Foundation <dave.glanzer&fieldbus.org>
//obrpd           1092/tcp   Open Business Reporting Protocol
//obrpd           1092/udp   Open Business Reporting Protocol
//#                          William Randolph Royere III 
//#                          <william&royere.net>
//proofd          1093/tcp   PROOFD
//proofd          1093/udp   PROOFD
//rootd           1094/tcp   ROOTD
//rootd           1094/udp   ROOTD
//#                          Fons Rademakers <Fons.Rademakers&cern.ch>
//nicelink        1095/tcp   NICELink
//nicelink        1095/udp   NICELink
//#                          Jordi Lisbona <jlisbona&tango04.net>   
//cnrprotocol     1096/tcp   Common Name Resolution Protocol
//cnrprotocol     1096/udp   Common Name Resolution Protocol
//#                          Michael Mealling <michaelm&netsol.com> 
//sunclustermgr	1097/tcp   Sun Cluster Manager
//sunclustermgr	1097/udp   Sun Cluster Manager
//#                          Ashit Patel <Ashit.Patel&eng.Sun.COM>
//rmiactivation	1098/tcp   RMI Activation
//rmiactivation	1098/udp   RMI Activation
//rmiregistry     1099/tcp   RMI Registry
//rmiregistry     1099/udp   RMI Registry
//#                          Mark Hodapp <mark.hodapp&sun.com>
//mctp            1100/tcp   MCTP 
//mctp            1100/udp   MCTP
//#                          Vitaly Revsin <vitaly&webmanage.com>
//pt2-discover    1101/tcp   PT2-DISCOVER
//pt2-discover    1101/udp   PT2-DISCOVER
//#                          Ralph Kammerlander 
//#                          <ralph.kammerlander&khe.siemens.de> 
//adobeserver-1   1102/tcp   ADOBE SERVER 1
//adobeserver-1   1102/udp   ADOBE SERVER 1
//adobeserver-2   1103/tcp   ADOBE SERVER 2
//adobeserver-2   1103/udp   ADOBE SERVER 2
//#                          Frank Soetebeer <frsoeteb&adobe.com>
//xrl             1104/tcp   XRL
//xrl             1104/udp   XRL
//#                          Patrick Robinson <probinson&plosive.com>
//ftranhc         1105/tcp   FTRANHC
//ftranhc         1105/udp   FTRANHC
//#                          Eriko Shimada <eriko&kel.fujitsu.co.jp> 
//isoipsigport-1  1106/tcp   ISOIPSIGPORT-1
//isoipsigport-1  1106/udp   ISOIPSIGPORT-1 
//isoipsigport-2  1107/tcp   ISOIPSIGPORT-2 
//isoipsigport-2  1107/udp   ISOIPSIGPORT-2 
//#                          Peter Egli <peter.egli&inalp.com> 
//ratio-adp       1108/tcp   ratio-adp
//ratio-adp       1108/udp   ratio-adp
//#                          Oliver Thulke <oth&ratio.de>
//#               1109       Reserved - IANA
//webadmstart	1110/tcp   Start web admin server
//nfsd-keepalive  1110/udp   Client status info
//#                          Beth Crespo <beth.crespo&hp.com>
//lmsocialserver  1111/tcp   LM Social Server
//lmsocialserver  1111/udp   LM Social Server
//#                          Ron Lussier <coyote&likeminds.com>
//icp             1112/tcp   Intelligent Communication Protocol
//icp             1112/udp   Intelligent Communication Protocol
//#                          Mark H. David <mhd&gensym.com>   
//ltp-deepspace   1113/tcp   Licklider Transmission Protocol
//ltp-deepspace   1113/udp   Licklider Transmission Protocol
//#                          [RFC5326]
//mini-sql        1114/tcp   Mini SQL
//mini-sql        1114/udp   Mini SQL
//#                          David Hughes <bambi&Hughes.com.au>
//ardus-trns      1115/tcp   ARDUS Transfer
//ardus-trns      1115/udp   ARDUS Transfer
//ardus-cntl      1116/tcp   ARDUS Control
//ardus-cntl      1116/udp   ARDUS Control
//ardus-mtrns     1117/tcp   ARDUS Multicast Transfer
//ardus-mtrns     1117/udp   ARDUS Multicast Transfer
//#                          Shinya Abe <abeabe&pfu.co.jp>
//sacred          1118/tcp   SACRED
//sacred          1118/udp   SACRED
//#                          RFC3767
//bnetgame        1119/tcp   Battle.net Chat/Game Protocol
//bnetgame        1119/udp   Battle.net Chat/Game Protocol
//bnetfile        1120/tcp   Battle.net File Transfer Protocol 
//bnetfile        1120/udp   Battle.net File Transfer Protocol 
//#                          Domain Tech <Domainnametech&blizzard.com> April 2005
//rmpp            1121/tcp   Datalode RMPP
//rmpp            1121/udp   Datalode RMPP
//#                          Dave Ruedger <daver&datalode.com> November 2003
//availant-mgr    1122/tcp   availant-mgr
//availant-mgr    1122/udp   availant-mgr
//#                          Steven Pelletier <stevep&Availant.com> 
//murray          1123/tcp   Murray
//murray          1123/udp   Murray
//#                          Stu Mark <fordii&j51.com>
//hpvmmcontrol    1124/tcp   HP VMM Control
//hpvmmcontrol    1124/udp   HP VMM Control
//hpvmmagent      1125/tcp   HP VMM Agent
//hpvmmagent      1125/udp   HP VMM Agent
//hpvmmdata       1126/tcp   HP VMM Agent
//hpvmmdata       1126/udp   HP VMM Agent
//#                          John Morton <j.morton&hp.com> November 2004
//kwdb-commn      1127/tcp   KWDB Remote Communication
//kwdb-commn      1127/udp   KWDB Remote Communication
//#                          Lal Samuel Varghese <lalsam&hp.com> August 2005
//saphostctrl	1128/tcp   SAPHostControl over SOAP/HTTP
//saphostctrl	1128/udp   SAPHostControl over SOAP/HTTP
//saphostctrls	1129/tcp   SAPHostControl over SOAP/HTTPS
//saphostctrls	1129/udp   SAPHostControl over SOAP/HTTPS
//#			   Muscarella Fabrizio <fabrizio.muscarella&sap.com> April 2006
//casp		1130/tcp   CAC App Service Protocol
//casp		1130/udp   CAC App Service Protocol
//caspssl		1131/tcp   CAC App Service Protocol Encripted
//caspssl		1131/udp   CAC App Service Protocol Encripted
//#			   Enrique Corujo <enrique&caclearing.com> February 2006
//kvm-via-ip	1132/tcp   KVM-via-IP Management Service
//kvm-via-ip	1132/udp   KVM-via-IP Management Service
//#			   Ian Miller <IANA-reg&adder.com> March 2006
//dfn		1133/tcp   Data Flow Network
//dfn		1133/udp   Data Flow Network
//#			   Dmitry Obuvalin <pulse.cc&mail.ru> February 2006
//aplx		1134/tcp   MicroAPL APLX
//aplx		1134/udp   MicroAPL APLX
//#			   Richard Nabavi <nabavi&microapl.co.uk> February 2006
//omnivision	1135/tcp   OmniVision Communication Service
//omnivision	1135/udp   OmniVision Communication Service
//#			   Serge Vacquier <vacquier&systar.fr> February 2006
//hhb-gateway	1136/tcp   HHB Gateway Control
//hhb-gateway	1136/udp   HHB Gateway Control
//#			   Richard Harwell <richardcharwell&eaton.com> February 2006
//trim		1137/tcp   TRIM Workgroup Service
//trim		1137/udp   TRIM Workgroup Service
//#			   Siva Poobalasingam <siva&towersoft.com.au> March 2006
//encrypted_admin	1138/tcp   encrypted admin requests
//encrypted_admin	1138/udp   encrypted admin requests
//#			   Michael Elizarov <Michael.Elizarov&microsoft.com> January 2007
//evm             1139/tcp   Enterprise Virtual Manager
//evm             1139/udp   Enterprise Virtual Manager
//#			   Thomas Hennessy <thennessy&manageiq.com> 04 October 2007
//autonoc		1140/tcp   AutoNOC Network Operations Protocol
//autonoc		1140/udp   AutoNOC Network Operations Protocol
//#                          Kyle Lussier <klussier&autonoc.com> December 2005
//mxomss		1141/tcp   User Message Service
//mxomss		1141/udp   User Message Service
//#			   Chaoyi Lang <chao-yi_lang&maxtor.com> January 2006
//edtools		1142/tcp   User Discovery Service
//edtools		1142/udp   User Discovery Service
//#			   Dolson, Lee <dolson&f-net.co.kr> January 2006
//imyx		1143/tcp   Infomatryx Exchange 
//imyx		1143/udp   Infomatryx Exchange 
//#			   David Walling <sylvanhollow&yahoo.com> March 2006
//fuscript	1144/tcp   Fusion Script
//fuscript	1144/udp   Fusion Script
//#			   Peter Loveday <peter&eyeonline.com> January 2006
//x9-icue		1145/tcp   X9 iCue Show Control
//x9-icue		1145/udp   X9 iCue Show Control
//#			   Brandon Potter <iana&brandonpotter.com> January 2006
//audit-transfer  1146/tcp   audit transfer 
//audit-transfer  1146/udp   audit transfer 
//#                          Mark Wahl <mark.wahl&informed-control.com> November 2005
//capioverlan     1147/tcp   CAPIoverLAN
//capioverlan     1147/udp   CAPIoverLAN
//#                          Diego Friedel <d.friedel&avm.de> November 2005
//elfiq-repl      1148/tcp   Elfiq Replication Service
//elfiq-repl      1148/udp   Elfiq Replication Service
//#                          Frederick Parent <fparent&elfiq.com> November 2005
//bvtsonar        1149/tcp   BVT Sonar Service
//bvtsonar        1149/udp   BVT Sonar Service
//#                          Justin Huff <justin.huff&blueviewtech.com> November 2005
//blaze           1150/tcp   Blaze File Server
//blaze           1150/udp   Blaze File Server
//#                          Curt Schimmel <curt&small-tree.com> November 2005
//unizensus       1151/tcp   Unizensus Login Server
//unizensus       1151/udp   Unizensus Login Server
//#                          Dirk Materlik <materlik&blubbsoft.de> November 2005
//winpoplanmess   1152/tcp   Winpopup LAN Messenger
//winpoplanmess   1152/udp   Winpopup LAN Messenger
//#                          Vitali Fomine <info&winpopup-lan-messenger.com> November 2005
//c1222-acse      1153/tcp   ANSI C12.22 Port
//c1222-acse      1153/udp   ANSI C12.22 Port
//#                          Avygdor Moise <avy&fdos.ca> November 2005
//resacommunity   1154/tcp   Community Service
//resacommunity   1154/udp   Community Service
//#                          St�phane MONS <stephane.mons&free.fr> September 2005
//nfa             1155/tcp   Network File Access                
//nfa             1155/udp   Network File Access                
//#                          James Powell <james&mailhost.unidata.com>
//iascontrol-oms  1156/tcp   iasControl OMS
//iascontrol-oms  1156/udp   iasControl OMS
//#                          Todd Guay <todd.guay&oracle.com> November 2004
//iascontrol      1157/tcp   Oracle iASControl
//iascontrol      1157/udp   Oracle iASControl
//#                          Todd Guay <todd.guay&oracle.com> November 2004
//dbcontrol-oms   1158/tcp   dbControl OMS
//dbcontrol-oms   1158/udp   dbControl OMS
//#                          Todd Guay <todd.guay&oracle.com> November 2004
//oracle-oms      1159/tcp   Oracle OMS
//oracle-oms      1159/udp   Oracle OMS
//#                          Todd Guay <todd.guay&oracle.com> November 2004
//olsv            1160/tcp   DB Lite Mult-User Server
//olsv            1160/udp   DB Lite Mult-User Server
//#                          Philip Stephenson <Philip.stephenson&oracle.com> August 2005
//health-polling  1161/tcp   Health Polling
//health-polling  1161/udp   Health Polling
//health-trap     1162/tcp   Health Trap
//health-trap     1162/udp   Health Trap
//sddp            1163/tcp   SmartDialer Data Protocol
//sddp            1163/udp   SmartDialer Data Protocol
//#                          Lee Griffiths <lg&dataconnection.com> November 2004
//qsm-proxy       1164/tcp   QSM Proxy Service
//qsm-proxy       1164/udp   QSM Proxy Service
//#                          Norm Lunde <norm&commvault.com> November 2004
//qsm-gui         1165/tcp   QSM GUI Service
//qsm-gui         1165/udp   QSM GUI Service
//#                          Norm Lunde <norm&commvault.com> November 2004
//qsm-remote      1166/tcp   QSM RemoteExec
//qsm-remote      1166/udp   QSM RemoteExec
//#                          Norm Lunde <norm&commvault.com> November 2004
//cisco-ipsla     1167/tcp   Cisco IP SLAs Control Protocol
//cisco-ipsla     1167/udp   Cisco IP SLAs Control Protocol
//cisco-ipsla     1167/sctp  Cisco IP SLAs Control Protocol
//#			   Emmanuel Tychon <etychon&cisco.com> March 2006
//vchat           1168/tcp   VChat Conference Service
//vchat           1168/udp   VChat Conference Service
//#                          Andreas Wetzel <mickey&enforcer.cc> September 2002
//tripwire        1169/tcp   TRIPWIRE
//tripwire        1169/udp   TRIPWIRE
//#                          Ed Metcalf <emetcalf&tripwiresecurity.com>
//#                          Albert Holt <alberth&triosoftware.com>
//atc-lm          1170/tcp   AT+C License Manager
//atc-lm          1170/udp   AT+C License Manager
//#                          Peter Sch�fer <p.schaefer&nospam.atc-systeme.de> February 2004
//atc-appserver   1171/tcp   AT+C FmiApplicationServer
//atc-appserver   1171/udp   AT+C FmiApplicationServer
//#                          Peter Sch�fer <p.schaefer&nospam.atc-systeme.de> February 2004
//dnap            1172/tcp   DNA Protocol
//dnap            1172/udp   DNA Protocol
//#                          David McLaughlin <davidmclaughlin&accessdata.com> November 2004
//d-cinema-rrp    1173/tcp   D-Cinema Request-Response
//d-cinema-rrp    1173/udp   D-Cinema Request-Response
//#                          Robert Baldwin <baldwin&plusfive.com> November 2004
//fnet-remote-ui  1174/tcp   FlashNet Remote Admin
//fnet-remote-ui  1174/udp   FlashNet Remote Admin
//#                          Terry Smyth <terry&sgluk.com> November 2004
//dossier         1175/tcp   Dossier Server
//dossier         1175/udp   Dossier Server
//#                          Rob Minerick <rob&vortimac.com> November 2004
//indigo-server   1176/tcp   Indigo Home Server
//indigo-server   1176/udp   Indigo Home Server
//#                          Matt Bendiksen <matt&perceptiveautomation.com> November 2004
//dkmessenger     1177/tcp   DKMessenger Protocol
//dkmessenger     1177/udp   DKMessenger Protocol
//#                          Douglas Kadlecek <doug&dkware.com> November 2004
//sgi-storman     1178/tcp   SGI Storage Manager
//sgi-storman     1178/udp   SGI Storage Manager
//#                          Greg Banks <gnb&sgi.com> November 2004
//b2n             1179/tcp   Backup To Neighbor
//b2n             1179/udp   Backup To Neighbor
//#                          Thomas Fok <thomas&melody-soft.com> November 2004
//mc-client       1180/tcp   Millicent Client Proxy
//mc-client       1180/udp   Millicent Client Proxy
//#                          Steve Glassman <steveg&pa.dec.com>
//3comnetman      1181/tcp   3Com Net Management
//3comnetman      1181/udp   3Com Net Management
//#                          Peter White <peter_white&3com.com> November 2004
//accelenet       1182/tcp   AcceleNet Control
//accelenet       1182/udp   AcceleNet Control
//#                          Peter Lepeska <plepeska&ictompress.com> November 2004
//llsurfup-http   1183/tcp   LL Surfup HTTP
//llsurfup-http   1183/udp   LL Surfup HTTP
//llsurfup-https  1184/tcp   LL Surfup HTTPS
//llsurfup-https  1184/udp   LL Surfup HTTPS
//#                          Katy Lynn McCullough <KatyM&LapLink.com>
//catchpole       1185/tcp   Catchpole port
//catchpole       1185/udp   Catchpole port
//#                          Christian Catchpole <christian&catchpole.net> March 2002
//mysql-cluster   1186/tcp   MySQL Cluster Manager
//mysql-cluster   1186/udp   MySQL Cluster Manager
//#                          Arjen Lentz <arjen&mysql.com> November 2004
//alias           1187/tcp   Alias Service
//alias           1187/udp   Alias Service
//#                          Paul Tokarchuk <ptokarch&alias.com> November 2004
//hp-webadmin     1188/tcp   HP Web Admin
//hp-webadmin     1188/udp   HP Web Admin
//#                          Lance Kind <lance_kind&hp.com>
//unet            1189/tcp   Unet Connection
//unet            1189/udp   Unet Connection
//#                          Anthony Stahler <imunfair&yahoo.com> November 2004
//commlinx-avl    1190/tcp   CommLinx GPS / AVL System
//commlinx-avl    1190/udp   CommLinx GPS / AVL System
//#                          Peter Johnson <peter&commlinx.com.au> November 2004
//gpfs            1191/tcp   General Parallel File System
//gpfs            1191/udp   General Parallel File System
//#                          Dave Craft <gpfs&ibm.com> November 2004
//caids-sensor    1192/tcp   caids sensors channel
//caids-sensor    1192/udp   caids sensors channel
//#                          Gregory Hostettler <ghostettler&caracal.ch> November 2004
//fiveacross      1193/tcp   Five Across Server
//fiveacross      1193/udp   Five Across Server
//#                          Glenn Reid <port-reg&fiveacross.com> November 2004
//openvpn         1194/tcp   OpenVPN
//openvpn         1194/udp   OpenVPN
//#                          James Yonan <jim&yonan.net> November 2004
//rsf-1           1195/tcp   RSF-1 clustering
//rsf-1           1195/udp   RSF-1 clustering
//#                          Dave Hines <d.hines&high-availability.com> November 2004
//netmagic        1196/tcp   Network Magic
//netmagic        1196/udp   Network Magic
//#                          Nick Holt <nickh&purenetworks.com> August 2005
//carrius-rshell  1197/tcp   Carrius Remote Access
//carrius-rshell  1197/udp   Carrius Remote Access
//#                          Gerry Dubois <gdubois&carriustech.com> August 2005
//cajo-discovery  1198/tcp   cajo reference discovery
//cajo-discovery  1198/udp   cajo reference discovery
//#                          John Catherino <cajo&dev.java.net> August 2005
//dmidi           1199/tcp   DMIDI
//dmidi           1199/udp   DMIDI
//#                          Phil Kerr <phil&plus24.com> February 2002
//scol            1200/tcp   SCOL
//scol            1200/udp   SCOL
//#                          Cryo-Networks <p.favre&cryo-networks.fr>
//nucleus-sand    1201/tcp   Nucleus Sand Database Server 
//nucleus-sand    1201/udp   Nucleus Sand Database Server 
//#                          James Marsh <James_T_Marsh&hotmail.com>
//caiccipc        1202/tcp   caiccipc
//caiccipc        1202/udp   caiccipc
//#                          Vince Re <Vincent.Re&cai.com>
//ssslic-mgr      1203/tcp   License Validation
//ssslic-mgr      1203/udp   License Validation
//ssslog-mgr      1204/tcp   Log Request Listener
//ssslog-mgr      1204/udp   Log Request Listener
//#                          Eric Bruno <ebruno&solution-soft.com>
//accord-mgc      1205/tcp   Accord-MGC
//accord-mgc      1205/udp   Accord-MGC
//#                          Roni Even <roni_e&accord.co.il>
//anthony-data    1206/tcp   Anthony Data
//anthony-data    1206/udp   Anthony Data
//#                          Paul Dollemore <pauld&anthonydata.com>
//metasage        1207/tcp   MetaSage
//metasage        1207/udp   MetaSage
//#                          Peter Anvelt <panvelt&xnai.com> 
//seagull-ais     1208/tcp   SEAGULL AIS
//seagull-ais     1208/udp   SEAGULL AIS
//#                          Lee Breisacher <lbreisacher&seagullsw.com> 
//ipcd3           1209/tcp   IPCD3
//ipcd3           1209/udp   IPCD3
//#                          Mark Ciskey <mlciskey&plato.com>  
//eoss            1210/tcp   EOSS
//eoss            1210/udp   EOSS
//#                          Robert Armes <rarmes&axarte.com>
//groove-dpp      1211/tcp   Groove DPP
//groove-dpp      1211/udp   Groove DPP
//#                          Ken Moore <kmoore&groove.net>
//lupa            1212/tcp   lupa
//lupa            1212/udp   lupa
//#                          Barney Wolff <barney&databus.com>
//mpc-lifenet     1213/tcp   MPC LIFENET
//mpc-lifenet     1213/udp   MPC LIFENET
//#                          Ward Silver <hwardsil&wolfenet.com>
//kazaa           1214/tcp   KAZAA
//kazaa           1214/udp   KAZAA
//#                          Ahti Heinla <ahti&ahti.bluemoon.ee>  
//scanstat-1      1215/tcp   scanSTAT 1.0
//scanstat-1      1215/udp   scanSTAT 1.0
//#                          William Scheding <wls&wls.org>
//etebac5         1216/tcp   ETEBAC 5
//etebac5         1216/udp   ETEBAC 5
//#                          Jean-Louis Barbut <etebac5&gsit.fr>
//hpss-ndapi      1217/tcp   HPSS NonDCE Gateway
//hpss-ndapi      1217/udp   HPSS NonDCE Gateway
//#                          Michael Gleicher <mgleicher&comcast.net>
//aeroflight-ads  1218/tcp   AeroFlight-ADs
//aeroflight-ads  1218/udp   AeroFlight-ADs
//aeroflight-ret  1219/tcp   AeroFlight-Ret
//aeroflight-ret  1219/udp   AeroFlight-Ret
//#                          Eric Johnson <eric&gruver.net>
//qt-serveradmin  1220/tcp   QT SERVER ADMIN
//qt-serveradmin  1220/udp   QT SERVER ADMIN
//#                          Chris LeCroy <lecroy&apple.com>
//sweetware-apps  1221/tcp   SweetWARE Apps
//sweetware-apps  1221/udp   SweetWARE Apps
//#                          David Dunetz <david&sweetware.com> 
//nerv            1222/tcp   SNI R&D network                  
//nerv            1222/udp   SNI R&D network                  
//#                          Martin Freiss <freiss.pad&sni.de>
//tgp             1223/tcp   TrulyGlobal Protocol
//tgp             1223/udp   TrulyGlobal Protocol
//#                          Previous contact: Gur Kimchi <gur&mail.trulyglobal.com>  
//#                          Current contact: Gur Kimchi <gkimchi&microsoft.com> 20 May 2008
//vpnz            1224/tcp   VPNz
//vpnz            1224/udp   VPNz
//#                          Tom Strack <TSTRACK&Advnw.com>      
//slinkysearch    1225/tcp   SLINKYSEARCH
//slinkysearch    1225/udp   SLINKYSEARCH
//#                          Desmond Chan <deschan&prismedia.com>
//stgxfws         1226/tcp   STGXFWS
//stgxfws         1226/udp   STGXFWS
//#                          Tetsuya Shioda <tetsuya&saint.nm.fujitsu.co.jp>   
//dns2go          1227/tcp   DNS2Go
//dns2go          1227/udp   DNS2Go
//#                          Mike Courterier <mikec&deerfield.com> 
//florence        1228/tcp   FLORENCE
//florence        1228/udp   FLORENCE
//#                          Brian Trammell <btrammell&iventurelab.com>
//zented		1229/tcp   ZENworks Tiered Electronic Distribution
//zented		1229/udp   ZENworks Tiered Electronic Distribution
//#                          Ty Ellis <tellis&novell.com> 
//periscope       1230/tcp   Periscope
//periscope       1230/udp   Periscope
//#                          Kevin Madden <Kevin&emailxtras.com>
//menandmice-lpm  1231/tcp   menandmice-lpm
//menandmice-lpm  1231/udp   menandmice-lpm
//#                          Sigfus Magnusson <sigfusm&menandmice.com>
//#####  Microsoft (unoffically) using 1232     #####
//univ-appserver  1233/tcp   Universal App Server
//univ-appserver  1233/udp   Universal App Server
//#                          Tim Sent <tim.sent&systemsarchitects.com>
//search-agent    1234/tcp   Infoseek Search Agent
//search-agent    1234/udp   Infoseek Search Agent
//#                          Jackie Wu <jackiew&infoseek.com>
//mosaicsyssvc1   1235/tcp   mosaicsyssvc1
//mosaicsyssvc1   1235/udp   mosaicsyssvc1
//#                          Brian Matthews <bmatthews&mosaicsystems.com>	
//bvcontrol       1236/tcp   bvcontrol
//bvcontrol       1236/udp   bvcontrol
//#                          Daniel J Walsh <dwalsh&bindview.com>
//tsdos390        1237/tcp   tsdos390
//tsdos390        1237/udp   tsdos390
//#                          Ben Pracht <ben.pracht&tivoli.com> 
//hacl-qs	        1238/tcp   hacl-qs
//hacl-qs	        1238/udp   hacl-qs
//#                          Farid Faez <farid_faez&hp.com>
//nmsd            1239/tcp   NMSD
//nmsd            1239/udp   NMSD
//#                          Yuri Machkasov <yuri&ptc.com>
//instantia       1240/tcp   Instantia
//instantia       1240/udp   Instantia
//#                          Ruth Slater <ruth.slater&ideagen.co.uk> 
//nessus	        1241/tcp   nessus
//nessus	        1241/udp   nessus
//#                          Jordan Hrycaj <jordan&mjh.teddy-net.com>
//nmasoverip      1242/tcp   NMAS over IP
//nmasoverip      1242/udp   NMAS over IP
//#                          Hal Henderson <hhenders&novell.com>		
//serialgateway   1243/tcp   SerialGateway
//serialgateway   1243/udp   SerialGateway
//#                          Stephen LaValley <lavalley&lucent.com>
//isbconference1  1244/tcp   isbconference1
//isbconference1  1244/udp   isbconference1
//isbconference2  1245/tcp   isbconference2
//isbconference2  1245/udp   isbconference2
//#                          Arnold Dittmann <dittmann&isbcad.de>
//payrouter       1246/tcp   payrouter
//payrouter       1246/udp   payrouter
//#                          David Wilson <dwilson&integral-ie.com>
//visionpyramid   1247/tcp   VisionPyramid
//visionpyramid   1247/udp   VisionPyramid
//#                          Gavin Hutchinson <gavinh&visionlogistics.com>
//hermes		1248/tcp   hermes
//hermes		1248/udp   hermes
//#                          Not known
//mesavistaco	1249/tcp   Mesa Vista Co
//mesavistaco	1249/udp   Mesa Vista Co
//#                          Rick LaBanca <rel&mesasys.com>
//swldy-sias	1250/tcp   swldy-sias
//swldy-sias	1250/udp   swldy-sias
//#                          Peter E Williams <peter.williams&smallworld-us.com>
//servergraph     1251/tcp   servergraph
//servergraph	1251/udp   servergraph
//#                          Lindsay Morris <lmorris&servergraph.com>
//bspne-pcc	1252/tcp   bspne-pcc
//bspne-pcc       1252/udp   bspne-pcc
//q55-pcc         1253/tcp   q55-pcc
//q55-pcc		1253/udp   q55-pcc
//#                          Prem Tirilok <Prem.Tirilok&tellabs.com>	
//de-noc		1254/tcp   de-noc
//de-noc		1254/udp   de-noc
//de-cache-query  1255/tcp   de-cache-query
//de-cache-query  1255/udp   de-cache-query
//de-server	1256/tcp   de-server
//de-server	1256/udp   de-server
//#			   Jeff Burdette <support&digitalenvoy.net>
//shockwave2      1257/tcp   Shockwave 2
//shockwave2	1257/udp   Shockwave 2
//#			   Dave Simmons <dsimmons&macromedia.com>	
//opennl		1258/tcp   Open Network Library
//opennl		1258/udp   Open Network Library
//opennl-voice    1259/tcp   Open Network Library Voice
//opennl-voice	1259/udp   Open Network Library Voice
//#                          Phil Frisbie <phil&hawksoft.com> 
//ibm-ssd		1260/tcp   ibm-ssd
//ibm-ssd		1260/udp   ibm-ssd
//#			   Barry Whyte <barry_whyte&uk.ibm.com>
//mpshrsv         1261/tcp   mpshrsv
//mpshrsv		1261/udp   mpshrsv
//#                          Makoto Ikeyama <ikeyama&ael.fujitsu.co.jp>
//qnts-orb	1262/tcp   QNTS-ORB
//qnts-orb        1262/udp   QNTS-ORB
//#                          Raghurama Bhat <raghu&quintus.com> 
//dka		1263/tcp   dka
//dka		1263/udp   dka
//#                          Chris Griffin <cgriffin&dka.com>
//prat		1264/tcp   PRAT
//prat            1264/udp   PRAT
//#                          Keith Wood <keith.wood&epid.eurotherm.co.uk> 
//dssiapi         1265/tcp   DSSIAPI
//dssiapi         1265/udp   DSSIAPI
//#                          Jim Turner <Jim.Turner&asg.com>
//dellpwrappks    1266/tcp   DELLPWRAPPKS
//dellpwrappks    1266/udp   DELLPWRAPPKS
//#                          David Troeger <David_Troeger&dell.com> 
//epc             1267/tcp   eTrust Policy Compliance
//epc             1267/udp   eTrust Policy Compliance
//#                          Aaron Stein <aaron.stein&ca.com>
//propel-msgsys   1268/tcp   PROPEL-MSGSYS
//propel-msgsys   1268/udp   PROPEL-MSGSYS
//#                          Bert Van der Linden <bert&propel.com>
//watilapp        1269/tcp   WATiLaPP
//watilapp        1269/udp   WATiLaPP
//#                          Frederic Weymann <contact&fizzban.net>
//opsmgr          1270/tcp   Microsoft Operations Manager
//opsmgr          1270/udp   Microsoft Operations Manager
//#                          Ashvin Sanghvi <AshvinS&microsoft.com>
//excw            1271/tcp   eXcW
//excw            1271/udp   eXcW
//#                          Norm Freedman <normfree&san.rr.com>
//cspmlockmgr     1272/tcp   CSPMLockMgr
//cspmlockmgr     1272/udp   CSPMLockMgr
//#                          Ibtsam Mahfouz <imahfouz&cisco.com>
//emc-gateway     1273/tcp   EMC-Gateway
//emc-gateway     1273/udp   EMC-Gateway
//#                          Rene Fontaine <fontaine_rene&emc.com>
//t1distproc      1274/tcp   t1distproc
//t1distproc      1274/udp   t1distproc
//#                          Julian Biddle <julian_biddle&TechnologyOneCorp.com>
//ivcollector     1275/tcp   ivcollector
//ivcollector     1275/udp   ivcollector
//ivmanager       1276/tcp   ivmanager
//ivmanager       1276/udp   ivmanager
//#                          Xavier Roques <xroques&infovista.fr>
//miva-mqs        1277/tcp   mqs
//miva-mqs        1277/udp   mqs
//#                          Miva Corporation <jwoods&miva.com.au>
//dellwebadmin-1  1278/tcp   Dell Web Admin 1
//dellwebadmin-1  1278/udp   Dell Web Admin 1
//dellwebadmin-2  1279/tcp   Dell Web Admin 2
//dellwebadmin-2  1279/udp   Dell Web Admin 2   
//#                          Bridget Navoda <Bridget_Navoda&dell.com> 
//pictrography    1280/tcp   Pictrography
//pictrography    1280/udp   Pictrography
//#                          Takashi Hoshino <hoshino&miya.fujifilm.co.jp>   
//healthd         1281/tcp   healthd
//healthd         1281/udp   healthd
//#                          James E. Housley <jim&thehousleys.net> 
//emperion        1282/tcp   Emperion
//emperion        1282/udp   Emperion
//#                          Claus Thor Barth <iana&barth.dk>
//productinfo     1283/tcp   ProductInfo
//productinfo     1283/udp   ProductInfo
//iee-qfx         1284/tcp   IEE-QFX
//iee-qfx         1284/udp   IEE-QFX
//#                          Kevin D. Quitt <KQuitt&IEEInc.com>
//neoiface        1285/tcp   neoiface
//neoiface        1285/udp   neoiface
//#                          Jason McManus <jasonm&neoinformatics.com>
//netuitive       1286/tcp   netuitive
//netuitive       1286/udp   netuitive 
//#                          JF Huard <jfhuard&netuitive.com>
//routematch      1287/tcp   RouteMatch Com 
//routematch      1287/udp   RouteMatch Com 
//#                          Jeff Jones <Jeff.Jones&routematch.com> November 2005
//navbuddy        1288/tcp   NavBuddy
//navbuddy        1288/udp   NavBuddy
//#                          Eric Hackman <ehackman&millapps.com>
//jwalkserver     1289/tcp   JWalkServer
//jwalkserver     1289/udp   JWalkServer
//winjaserver     1290/tcp   WinJaServer 
//winjaserver     1290/udp   WinJaServer  
//seagulllms      1291/tcp   SEAGULLLMS
//seagulllms      1291/udp   SEAGULLLMS
//#                          Lee Breisacher <lbreisacher&seagullsw.com>
//dsdn            1292/tcp   dsdn
//dsdn            1292/udp   dsdn
//#                          Stanislaw Skowronek <thesis&elementary.pl>
//pkt-krb-ipsec   1293/tcp   PKT-KRB-IPSec
//pkt-krb-ipsec   1293/udp   PKT-KRB-IPSec
//#                          Nancy Davoust <n.davoust&cablelabs.com>
//cmmdriver       1294/tcp   CMMdriver
//cmmdriver       1294/udp   CMMdriver
//#                          Lutz Karras <karras&zeiss.de>
//ehtp            1295/tcp   End-by-Hop Transmission Protocol
//ehtp            1295/udp   End-by-Hop Transmission Protocol
//#                          Alexander Bogdanov <alexandr_bgd&softhome.net>  
//dproxy          1296/tcp   dproxy
//dproxy          1296/udp   dproxy
//sdproxy         1297/tcp   sdproxy
//sdproxy         1297/udp   sdproxy
//#                          Raimond Diederik <rdiederik&descartes.com> 
//lpcp            1298/tcp   lpcp
//lpcp            1298/udp   lpcp
//#                          Christian Stredicke <stredicke&snom.de>
//hp-sci          1299/tcp   hp-sci
//hp-sci          1299/udp   hp-sci
//#                          Kim Scott <kims&cup.hp.com>       
//h323hostcallsc	1300/tcp   H323 Host Call Secure
//h323hostcallsc	1300/udp   H323 Host Call Secure
//#			   Jim Toga <jtoga&ideal.jf.intel.com>
//ci3-software-1  1301/tcp   CI3-Software-1
//ci3-software-1  1301/udp   CI3-Software-1
//ci3-software-2  1302/tcp   CI3-Software-2
//ci3-software-2  1302/udp   CI3-Software-2
//#                          Kelli Watson <kwatson&ci3software.com>
//sftsrv          1303/tcp   sftsrv
//sftsrv          1303/udp   sftsrv
//#                          Robert Frazier <BobF&mrp3.com>
//boomerang       1304/tcp   Boomerang
//boomerang       1304/udp   Boomerang
//#                          Bruce Lueckenhoff <brucelu&cisco.com>
//pe-mike	        1305/tcp   pe-mike
//pe-mike         1305/udp   pe-mike
//#                          Stephen Hemminger <shemminger&passedge.com>
//re-conn-proto   1306/tcp   RE-Conn-Proto
//re-conn-proto   1306/udp   RE-Conn-Proto
//#                          Sandeep Singhal <sandeep&reefedge.com>
//pacmand         1307/tcp   Pacmand
//pacmand         1307/udp   Pacmand
//#                          Edward T. O'Shea <oshea&bellsouth.net> 
//odsi            1308/tcp   Optical Domain Service Interconnect (ODSI)
//odsi            1308/udp   Optical Domain Service Interconnect (ODSI)
//#                          K. Arvind <arvind&tenornetworks.com> 
//jtag-server     1309/tcp   JTAG server
//jtag-server     1309/udp   JTAG server
//#                          Andrew Draper <adraper&altera.com>
//husky		1310/tcp   Husky
//husky		1310/udp   Husky
//#			   Mark Zang <mark&zang.com>
//rxmon		1311/tcp   RxMon
//rxmon		1311/udp   RxMon
//#			   Javier Jiminez <javier_l_jimenez&dell.com>
//sti-envision	1312/tcp   STI Envision
//sti-envision	1312/udp   STI Envision
//#			   Don Stedman <dones&stisystems.com>
//bmc_patroldb    1313/tcp   BMC_PATROLDB
//bmc_patroldb    1313/udp   BMC_PATROLDB
//#                          Portnoy Boxman <portnoy_boxman&bmc.com>
//pdps		1314/tcp   Photoscript Distributed Printing System
//pdps            1314/udp   Photoscript Distributed Printing System
//#			   Les Klein <sgy&cix.compulink.co.uk>
//els		1315/tcp   E.L.S., Event Listener Service
//els		1315/udp   E.L.S., Event Listener Service
//#			   Jim Cleppe <clep13&hotmail.com>
//exbit-escp      1316/tcp   Exbit-ESCP
//exbit-escp      1316/udp   Exbit-ESCP
//#                          Morten Christensen <mjc&exbit.dk>
//vrts-ipcserver  1317/tcp   vrts-ipcserver
//vrts-ipcserver  1317/udp   vrts-ipcserver
//#                          Bruce Hestand <Bruce.Hestand&veritas.com>
//krb5gatekeeper  1318/tcp   krb5gatekeeper
//krb5gatekeeper  1318/udp   krb5gatekeeper
//#                          Patrick Moore <pcmoore&sandia.gov> 
//amx-icsp        1319/tcp   AMX-ICSP
//amx-icsp        1319/udp   AMX-ICSP
//#                          Jeff Burch <jeff.burch&amx.com>     
//amx-axbnet	1320/tcp   AMX-AXBNET
//amx-axbnet	1320/udp   AMX-AXBNET
//#			   Jeff Burch <jeff.burch&amx.com> 
//pip		1321/tcp   PIP
//pip		1321/udp   PIP
//#			   Gordon Mohr <gojomo&usa.net>
//novation        1322/tcp   Novation
//novation        1322/udp   Novation
//#                          Alan Dano <wiseobject&yahoo.com>
//brcd            1323/tcp   brcd
//brcd            1323/udp   brcd
//#                          Todd Picquelle <todd&picquelle.com>
//delta-mcp       1324/tcp   delta-mcp
//delta-mcp       1324/udp   delta-mcp
//#                          Quinton Tormanen <quinton&deltacompsys.com> 
//dx-instrument   1325/tcp   DX-Instrument
//dx-instrument   1325/udp   DX-Instrument
//#                          Walt Modic <Walt.Modic&dionex.com>
//wimsic          1326/tcp   WIMSIC
//wimsic          1326/udp   WIMSIC
//#                          James Brown <ender&admdev.com>
//ultrex          1327/tcp   Ultrex
//ultrex          1327/udp   Ultrex
//#                          Tim Walsh <tim&ultrex.com>
//ewall           1328/tcp   EWALL
//ewall           1328/udp   EWALL
//#                          Jeff Busma <busma&echogent.com>
//netdb-export    1329/tcp   netdb-export
//netdb-export    1329/udp   netdb-export
//#                          Konstantinos Kostis <netdb&kostis.net>
//streetperfect   1330/tcp   StreetPerfect
//streetperfect   1330/udp   StreetPerfect
//#                          Michael R. Young <michael.young&tor.sunpub.com> 
//intersan        1331/tcp   intersan
//intersan        1331/udp   intersan
//#                          Barry H. Feild <barry&intersan.net> 
//pcia-rxp-b      1332/tcp   PCIA RXP-B
//pcia-rxp-b      1332/udp   PCIA RXP-B
//#                          James Dabbs <jdabbs&tga.com>
//passwrd-policy  1333/tcp   Password Policy
//passwrd-policy  1333/udp   Password Policy
//#                          Tonio Pirotta <tonio&tpis.com.au> 
//writesrv        1334/tcp   writesrv
//writesrv        1334/udp   writesrv
//#                          Marvin Toungate <toungate&austin.ibm.com>   
//digital-notary	1335/tcp   Digital Notary Protocol
//digital-notary	1335/udp   Digital Notary Protocol
//#			   Wes Doonan
//ischat	        1336/tcp   Instant Service Chat
//ischat          1336/udp   Instant Service Chat
//#                          Mike Clise <mikec&instantservice.com>
//menandmice-dns  1337/tcp   menandmice DNS
//menandmice-dns  1337/udp   menandmice DNS
//#                          Sigfus Magnusson <sigfusm&menandmice.com>
//wmc-log-svc     1338/tcp   WMC-log-svr
//wmc-log-svc     1338/udp   WMC-log-svr
//#                          Scott Anderson <sanderso&workingmachines.com> 
//kjtsiteserver   1339/tcp   kjtsiteserver
//kjtsiteserver   1339/udp   kjtsiteserver
//#                          Jason Aubain <jaubain&kjt.com>
//naap		1340/tcp   NAAP
//naap            1340/udp   NAAP
//#                          Henry Haverinen <henry.haverinen&nokia.com>	
//qubes           1341/tcp   QuBES
//qubes		1341/udp   QuBES
//#                          Eric Grange <egrange&creative-it.net> 
//esbroker	1342/tcp   ESBroker
//esbroker	1342/udp   ESBroker
//#                          Alexander Medvinsky <smedvinsky&gi.com>
//re101		1343/tcp   re101
//re101           1343/udp   re101
//#                          Doriano Blengino <tecnico_remove_&_remove_xonelectronics.it>
//icap		1344/tcp   ICAP
//icap            1344/udp   ICAP
//#                          Jeremy Elson <jelson&isi.edu>
//vpjp            1345/tcp   VPJP
//vpjp            1345/udp   VPJP
//#                          Michael Collins <UBMCollins&aol.com>
//alta-ana-lm     1346/tcp   Alta Analytics License Manager 
//alta-ana-lm     1346/udp   Alta Analytics License Manager 
//bbn-mmc		1347/tcp   multi media conferencing
//bbn-mmc		1347/udp   multi media conferencing
//bbn-mmx		1348/tcp   multi media conferencing
//bbn-mmx		1348/udp   multi media conferencing
//sbook           1349/tcp   Registration Network Protocol       
//sbook           1349/udp   Registration Network Protocol       
//editbench       1350/tcp   Registration Network Protocol       
//editbench       1350/udp   Registration Network Protocol       
//#                          Simson L. Garfinkel <simsong&next.cambridge.ma.us>
//equationbuilder 1351/tcp   Digital Tool Works (MIT)            
//equationbuilder 1351/udp   Digital Tool Works (MIT)            
//#                          Terrence J. Talbot <lexcube!tjt&bu.edu>
//lotusnote       1352/tcp   Lotus Note                          
//lotusnote       1352/udp   Lotus Note                          
//#                          Greg Pflaum <iris.com!Greg_Pflaum&uunet.uu.net> (July 1992)
//relief          1353/tcp   Relief Consulting                   
//relief          1353/udp   Relief Consulting                   
//#                          John Feiler <relief!jjfeiler&uu2.psi.com>
//XSIP-network    1354/tcp   Five Across XSIP Network              
//XSIP-network    1354/udp   Five Across XSIP Network              
//#                          Glenn Reid <port-reg&fiveacross.com>
//intuitive-edge  1355/tcp   Intuitive Edge 
//intuitive-edge  1355/udp   Intuitive Edge 
//#                          Montgomery Zukowski
//#                          <monty&nextnorth.acs.ohio-state.edu> 
//cuillamartin    1356/tcp   CuillaMartin Company 
//cuillamartin    1356/udp   CuillaMartin Company 
//pegboard        1357/tcp   Electronic PegBoard  
//pegboard        1357/udp   Electronic PegBoard  
//#                          Chris Cuilla
//#                          <balr!vpnet!cuilla!chris&clout.chi.il.us> 
//connlcli        1358/tcp   CONNLCLI                             
//connlcli        1358/udp   CONNLCLI                             
//ftsrv           1359/tcp   FTSRV                                
//ftsrv           1359/udp   FTSRV                                
//#                          Ines Homem de Melo <sidinf&brfapesp.bitnet>
//mimer           1360/tcp   MIMER                               
//mimer           1360/udp   MIMER                               
//#                          Per Schroeder  <Per.Schroder&mimer.se>
//linx            1361/tcp   LinX                        
//linx            1361/udp   LinX                        
//#                          Steffen Schilke <---none--->
//timeflies       1362/tcp   TimeFlies                           
//timeflies       1362/udp   TimeFlies                           
//#                          Doug Kent <mouthers@slugg&nwnexus.wa.com>
//ndm-requester   1363/tcp   Network DataMover Requester
//ndm-requester   1363/udp   Network DataMover Requester
//ndm-server      1364/tcp   Network DataMover Server   
//ndm-server      1364/udp   Network DataMover Server   
//#                          Toshio Watanabe
//#                          <watanabe&godzilla.rsc.spdd.ricoh.co.j> 
//adapt-sna       1365/tcp   Network Software Associates
//adapt-sna       1365/udp   Network Software Associates
//#                          Jeffery Chiao <714-768-401>
//netware-csp     1366/tcp   Novell NetWare Comm Service Platform
//netware-csp     1366/udp   Novell NetWare Comm Service Platform
//#                          Laurie Lindsey <llindsey&novell.com>
//dcs             1367/tcp   DCS                             
//dcs             1367/udp   DCS                             
//#                          Stefan Siebert <ssiebert&dcs.de>
//screencast      1368/tcp   ScreenCast                          
//screencast      1368/udp   ScreenCast                          
//#                          Bill Tschumy <other!bill&uunet.UU.NET>
//gv-us           1369/tcp   GlobalView to Unix Shell             
//gv-us           1369/udp   GlobalView to Unix Shell             
//us-gv           1370/tcp   Unix Shell to GlobalView             
//us-gv           1370/udp   Unix Shell to GlobalView             
//#                          Makoto Mita <mita&ssdev.ksp.fujixerox.co.jp>
//fc-cli          1371/tcp   Fujitsu Config Protocol             
//fc-cli          1371/udp   Fujitsu Config Protocol             
//fc-ser          1372/tcp   Fujitsu Config Protocol             
//fc-ser          1372/udp   Fujitsu Config Protocol             
//#                          Ryuichi Horie <horie&spad.sysrap.cs.fujitsu.co.jp>
//chromagrafx     1373/tcp   Chromagrafx                         
//chromagrafx     1373/udp   Chromagrafx                         
//#                          Mike Barthelemy <msb&chromagrafx.com>
//molly           1374/tcp   EPI Software Systems        
//molly           1374/udp   EPI Software Systems        
//#                          Jim Vlcek <jvlcek&veeco.com>
//bytex           1375/tcp   Bytex                             
//bytex           1375/udp   Bytex                             
//#                          Mary Ann Burt <bytex!ws054!maryann&uunet.UU.NET>
//ibm-pps         1376/tcp   IBM Person to Person Software     
//ibm-pps         1376/udp   IBM Person to Person Software     
//#                          Simon Phipps <sphipps&vnet.ibm.com>
//cichlid         1377/tcp   Cichlid License Manager       
//cichlid         1377/udp   Cichlid License Manager       
//#                          Andy Burgess <aab&cichlid.com>
//elan            1378/tcp   Elan License Manager   
//elan            1378/udp   Elan License Manager   
//#                          Ken Greer <kg&elan.com>
//dbreporter      1379/tcp   Integrity Solutions                 
//dbreporter      1379/udp   Integrity Solutions                 
//#                          Tim Dawson <tdawson%mspboss&uunet.UU.NET>
//telesis-licman  1380/tcp   Telesis Network License Manager     
//telesis-licman  1380/udp   Telesis Network License Manager     
//#                          Karl Schendel, Jr. <wiz&telesis.com>
//apple-licman    1381/tcp   Apple Network License Manager 
//apple-licman    1381/udp   Apple Network License Manager 
//#                          Earl Wallace <earlw&apple.com>
//udt_os          1382/tcp   udt_os
//udt_os          1382/udp   udt_os
//gwha            1383/tcp   GW Hannaway Network License Manager
//gwha            1383/udp   GW Hannaway Network License Manager
//#                          J. Gabriel Foster <fop&gwha.com>
//os-licman       1384/tcp   Objective Solutions License Manager 
//os-licman       1384/udp   Objective Solutions License Manager 
//#                          Donald Cornwell <don.cornwell&objective.com>
//atex_elmd       1385/tcp   Atex Publishing License Manager
//atex_elmd       1385/udp   Atex Publishing License Manager
//#                          Brett Sorenson <bcs&atex.com>
//checksum        1386/tcp   CheckSum License Manager            
//checksum        1386/udp   CheckSum License Manager            
//#                          Andreas Glocker <glocker&sirius.com>
//cadsi-lm        1387/tcp   Computer Aided Design Software Inc LM 
//cadsi-lm        1387/udp   Computer Aided Design Software Inc LM 
//#                          Sulistio Muljadi <e-mail?>
//objective-dbc   1388/tcp   Objective Solutions DataBase Cache
//objective-dbc   1388/udp   Objective Solutions DataBase Cache
//#                          Donald Cornwell <e-mail?>
//iclpv-dm        1389/tcp   Document Manager                    
//iclpv-dm        1389/udp   Document Manager                    
//iclpv-sc        1390/tcp   Storage Controller                  
//iclpv-sc        1390/udp   Storage Controller                  
//iclpv-sas       1391/tcp   Storage Access Server               
//iclpv-sas       1391/udp   Storage Access Server               
//iclpv-pm        1392/tcp   Print Manager                       
//iclpv-pm        1392/udp   Print Manager                       
//iclpv-nls       1393/tcp   Network Log Server                  
//iclpv-nls       1393/udp   Network Log Server                  
//iclpv-nlc       1394/tcp   Network Log Client                  
//iclpv-nlc       1394/udp   Network Log Client                  
//iclpv-wsm       1395/tcp   PC Workstation Manager software     
//iclpv-wsm       1395/udp   PC Workstation Manager software     
//#                          A.P. Hobson <A.P.Hobson&bra0112.wins.icl.co.uk>
//dvl-activemail  1396/tcp   DVL Active Mail                     
//dvl-activemail  1396/udp   DVL Active Mail                     
//audio-activmail 1397/tcp   Audio Active Mail                   
//audio-activmail 1397/udp   Audio Active Mail                   
//video-activmail 1398/tcp   Video Active Mail                   
//video-activmail 1398/udp   Video Active Mail                   
//#                          Avshalom Houri <Avshalom&ubique.com>
//cadkey-licman   1399/tcp   Cadkey License Manager         
//cadkey-licman   1399/udp   Cadkey License Manager         
//cadkey-tablet   1400/tcp   Cadkey Tablet Daemon           
//cadkey-tablet   1400/udp   Cadkey Tablet Daemon           
//#                          Joe McCollough <joe&cadkey.com>
//goldleaf-licman 1401/tcp   Goldleaf License Manager
//goldleaf-licman 1401/udp   Goldleaf License Manager
//#                          John Fox <---none--->
//prm-sm-np       1402/tcp   Prospero Resource Manager
//prm-sm-np       1402/udp   Prospero Resource Manager
//prm-nm-np       1403/tcp   Prospero Resource Manager
//prm-nm-np       1403/udp   Prospero Resource Manager
//#                          B. Clifford Neuman <bcn&isi.edu>
//igi-lm          1404/tcp   Infinite Graphics License Manager
//igi-lm          1404/udp   Infinite Graphics License Manager
//ibm-res         1405/tcp   IBM Remote Execution Starter
//ibm-res         1405/udp   IBM Remote Execution Starter
//netlabs-lm      1406/tcp   NetLabs License Manager
//netlabs-lm      1406/udp   NetLabs License Manager
//dbsa-lm         1407/tcp   DBSA License Manager        
//dbsa-lm         1407/udp   DBSA License Manager        
//#                          Scott Shattuck <ss&dbsa.com>
//sophia-lm       1408/tcp   Sophia License Manager              
//sophia-lm       1408/udp   Sophia License Manager              
//#                          Eric Brown <sst!emerald!eric&uunet.UU.net>
//here-lm         1409/tcp   Here License Manager             
//here-lm         1409/udp   Here License Manager             
//#                          David Ison  <here&dialup.oar.net>
//hiq             1410/tcp   HiQ License Manager               
//hiq             1410/udp   HiQ License Manager               
//#                          Rick Pugh <rick&bilmillennium.com>
//af              1411/tcp   AudioFile                  
//af              1411/udp   AudioFile                  
//#                          Jim Gettys <jg&crl.dec.com>
//innosys         1412/tcp   InnoSys               
//innosys         1412/udp   InnoSys               
//innosys-acl     1413/tcp   Innosys-ACL           
//innosys-acl     1413/udp   Innosys-ACL           
//#                          Eric Welch <--none--->
//ibm-mqseries    1414/tcp   IBM MQSeries                        
//ibm-mqseries    1414/udp   IBM MQSeries                        
//#                          Roger Meli <rmmeli%winvmd&vnet.ibm.com>
//dbstar          1415/tcp   DBStar                          
//dbstar          1415/udp   DBStar                          
//#                          Jeffrey Millman <jcm&dbstar.com>
//novell-lu6.2    1416/tcp   Novell LU6.2         
//novell-lu6.2    1416/udp   Novell LU6.2         
//#                          Peter Liu <--none--->
//timbuktu-srv1   1417/tcp   Timbuktu Service 1 Port            
//timbuktu-srv1   1417/udp   Timbuktu Service 1 Port            
//timbuktu-srv2   1418/tcp   Timbuktu Service 2 Port            
//timbuktu-srv2   1418/udp   Timbuktu Service 2 Port            
//timbuktu-srv3   1419/tcp   Timbuktu Service 3 Port            
//timbuktu-srv3   1419/udp   Timbuktu Service 3 Port            
//timbuktu-srv4   1420/tcp   Timbuktu Service 4 Port            
//timbuktu-srv4   1420/udp   Timbuktu Service 4 Port            
//#                          Marc Epard <marc&netopia.com>
//gandalf-lm      1421/tcp   Gandalf License Manager
//gandalf-lm      1421/udp   Gandalf License Manager
//#                          gilmer&gandalf.ca
//autodesk-lm     1422/tcp   Autodesk License Manager   
//autodesk-lm     1422/udp   Autodesk License Manager   
//#                          David Ko <dko&autodesk.com>
//essbase         1423/tcp   Essbase Arbor Software     
//essbase         1423/udp   Essbase Arbor Software     
//hybrid          1424/tcp   Hybrid Encryption Protocol  
//hybrid          1424/udp   Hybrid Encryption Protocol  
//#                          Howard Hart <hch&hybrid.com>
//zion-lm         1425/tcp   Zion Software License Manager 
//zion-lm         1425/udp   Zion Software License Manager 
//#                          David Ferrero <david&zion.com>
//sais            1426/tcp   Satellite-data Acquisition System 1
//sais            1426/udp   Satellite-data Acquisition System 1
//#                          Bill Taylor <sais&ssec.wisc.edu>
//mloadd          1427/tcp   mloadd monitoring tool     
//mloadd          1427/udp   mloadd monitoring tool     
//#                          Bob Braden <braden&isi.edu>
//informatik-lm   1428/tcp   Informatik License Manager
//informatik-lm   1428/udp   Informatik License Manager
//#                          Harald Schlangmann
//#                          <schlangm&informatik.uni-muenchen.de> 
//nms             1429/tcp   Hypercom NMS                      
//nms             1429/udp   Hypercom NMS                      
//tpdu            1430/tcp   Hypercom TPDU                     
//tpdu            1430/udp   Hypercom TPDU                     
//#                          Noor Chowdhury <noor&hypercom.com>
//rgtp            1431/tcp   Reverse Gossip Transport
//rgtp            1431/udp   Reverse Gossip Transport
//#                          Ian Jackson  <iwj&cam-orl.co.uk>
//blueberry-lm    1432/tcp   Blueberry Software License Manager  
//blueberry-lm    1432/udp   Blueberry Software License Manager  
//#                          Steve Beigel <ublueb!steve&uunet.uu.net>
//ms-sql-s        1433/tcp   Microsoft-SQL-Server 
//ms-sql-s        1433/udp   Microsoft-SQL-Server 
//ms-sql-m        1434/tcp   Microsoft-SQL-Monitor
//ms-sql-m        1434/udp   Microsoft-SQL-Monitor                
//#                          Peter Hussey <peterhus&microsoft.com>
//ibm-cics        1435/tcp   IBM CICS
//ibm-cics        1435/udp   IBM CICS
//#                          Geoff Meacock <gbibmswl&ibmmail.COM>
//saism           1436/tcp   Satellite-data Acquisition System 2
//saism           1436/udp   Satellite-data Acquisition System 2
//#                          Bill Taylor <sais&ssec.wisc.edu>
//tabula          1437/tcp   Tabula
//tabula          1437/udp   Tabula
//#                          Marcelo Einhorn
//#                          <KGUNE%HUJIVM1.bitnet&taunivm.tau.ac.il> 
//eicon-server    1438/tcp   Eicon Security Agent/Server         
//eicon-server    1438/udp   Eicon Security Agent/Server         
//eicon-x25       1439/tcp   Eicon X25/SNA Gateway               
//eicon-x25       1439/udp   Eicon X25/SNA Gateway               
//eicon-slp       1440/tcp   Eicon Service Location Protocol     
//eicon-slp       1440/udp   Eicon Service Location Protocol     
//#                          Pat Calhoun <CALHOUN&admin.eicon.qc.ca>
//cadis-1         1441/tcp   Cadis License Management       
//cadis-1         1441/udp   Cadis License Management       
//cadis-2         1442/tcp   Cadis License Management       
//cadis-2         1442/udp   Cadis License Management       
//#                          Todd Wichers <twichers&csn.org>
//ies-lm          1443/tcp   Integrated Engineering Software     
//ies-lm          1443/udp   Integrated Engineering Software     
//#                          David Tong <David_Tong&integrated.mb.ca>
//marcam-lm       1444/tcp   Marcam  License Management    
//marcam-lm       1444/udp   Marcam  License Management    
//#                          Therese Hunt <hunt&marcam.com>
//proxima-lm      1445/tcp   Proxima License Manager       
//proxima-lm      1445/udp   Proxima License Manager       
//ora-lm          1446/tcp   Optical Research Associates License Manager
//ora-lm          1446/udp   Optical Research Associates License Manager
//apri-lm         1447/tcp   Applied Parallel Research LM
//apri-lm         1447/udp   Applied Parallel Research LM
//#                          Jim Dillon <jed&apri.com>
//oc-lm           1448/tcp   OpenConnect License Manager
//oc-lm           1448/udp   OpenConnect License Manager
//#                          Sue Barnhill <snb&oc.com>
//peport          1449/tcp   PEport                               
//peport          1449/udp   PEport                               
//#                          Qentin Neill <quentin&ColumbiaSC.NCR.COM>
//dwf             1450/tcp   Tandem Distributed Workbench Facility 
//dwf             1450/udp   Tandem Distributed Workbench Facility 
//#                          Mike Bert <BERG_MIKE&tandem.com>
//infoman         1451/tcp   IBM Information Management
//infoman         1451/udp   IBM Information Management
//#                          Karen Burns <---none--->
//gtegsc-lm       1452/tcp   GTE Government Systems License Man   
//gtegsc-lm       1452/udp   GTE Government Systems License Man   
//#                          Mike Gregory <Gregory_Mike&msmail.iipo.gtegsc.com>
//genie-lm        1453/tcp   Genie License Manager                
//genie-lm        1453/udp   Genie License Manager                
//#                          Paul Applegate <p.applegate2&genie.geis.com>
//interhdl_elmd   1454/tcp   interHDL License Manager      
//interhdl_elmd   1454/udp   interHDL License Manager      
//#                          Eli Sternheim eli&interhdl.com
//esl-lm          1455/tcp   ESL License Manager           
//esl-lm          1455/udp   ESL License Manager           
//#                          Abel Chou <abel&willy.esl.com>
//dca             1456/tcp   DCA           
//dca             1456/udp   DCA           
//#                          Jeff Garbers <jgarbers&netcom.com>
//valisys-lm      1457/tcp   Valisys License Manager
//valisys-lm      1457/udp   Valisys License Manager
//#                          Leslie Lincoln <leslie_lincoln&valisys.com>
//nrcabq-lm       1458/tcp   Nichols Research Corp.
//nrcabq-lm       1458/udp   Nichols Research Corp.
//#                          Howard Cole <hcole&tumbleweed.nrcabq.com>
//proshare1       1459/tcp   Proshare Notebook Application
//proshare1       1459/udp   Proshare Notebook Application
//proshare2       1460/tcp   Proshare Notebook Application
//proshare2       1460/udp   Proshare Notebook Application
//#                          Robin Kar <Robin_Kar&ccm.hf.intel.com>
//ibm_wrless_lan  1461/tcp   IBM Wireless LAN 
//ibm_wrless_lan  1461/udp   IBM Wireless LAN 
//#                          <flanne&vnet.IBM.COM>
//world-lm        1462/tcp   World License Manager
//world-lm        1462/udp   World License Manager
//#                          Michael S Amirault <ambi&world.std.com>
//nucleus         1463/tcp   Nucleus
//nucleus         1463/udp   Nucleus
//#                          Venky Nagar <venky&fafner.Stanford.EDU>
//msl_lmd         1464/tcp    MSL License Manager
//msl_lmd         1464/udp    MSL License Manager
//#                           Matt Timmermans
//pipes           1465/tcp    Pipes Platform 
//pipes           1465/udp    Pipes Platform  mfarlin&peerlogic.com
//#                           Mark Farlin <mfarlin&peerlogic.com>
//oceansoft-lm    1466/tcp    Ocean Software License Manager
//oceansoft-lm    1466/udp    Ocean Software License Manager
//#                           Randy Leonard <randy&oceansoft.com>
//csdmbase        1467/tcp    CSDMBASE  
//csdmbase        1467/udp    CSDMBASE  
//csdm            1468/tcp    CSDM      
//csdm            1468/udp    CSDM      
//#               Robert Stabl <stabl&informatik.uni-muenchen.de>
//aal-lm          1469/tcp    Active Analysis Limited License Manager
//aal-lm          1469/udp    Active Analysis Limited License Manager
//#                           David Snocken  +44 (71)437-7009
//uaiact          1470/tcp    Universal Analytics  
//uaiact          1470/udp    Universal Analytics  
//#                           Mark R. Ludwig <Mark-Ludwig&uai.com>
//csdmbase        1471/tcp    csdmbase   
//csdmbase        1471/udp    csdmbase   
//csdm            1472/tcp    csdm       
//csdm            1472/udp    csdm       
//#               Robert Stabl <stabl&informatik.uni-muenchen.de>
//openmath        1473/tcp    OpenMath   
//openmath        1473/udp    OpenMath   
//#                           Garth Mayville <mayville&maplesoft.on.ca>
//telefinder      1474/tcp    Telefinder 
//telefinder      1474/udp    Telefinder 
//#                           Jim White <Jim_White&spiderisland.com>
//taligent-lm     1475/tcp    Taligent License Manager  
//taligent-lm     1475/udp    Taligent License Manager  
//#               Mark Sapsford <Mark_Sapsford@@taligent.com>
//clvm-cfg        1476/tcp    clvm-cfg  
//clvm-cfg        1476/udp    clvm-cfg  
//#                           Eric Soderberg <seric&cup.hp.com>
//ms-sna-server   1477/tcp    ms-sna-server  
//ms-sna-server   1477/udp    ms-sna-server  
//ms-sna-base     1478/tcp    ms-sna-base    
//ms-sna-base     1478/udp    ms-sna-base    
//#                           Gordon Mangione <gordm&microsoft.com>
//dberegister     1479/tcp    dberegister  
//dberegister     1479/udp    dberegister  
//#                           Brian Griswold <brian&dancingbear.com>
//pacerforum      1480/tcp    PacerForum  
//pacerforum      1480/udp    PacerForum  
//#                           Peter Caswell <pfc&pacvax.pacersoft.com>
//airs            1481/tcp    AIRS        
//airs            1481/udp    AIRS        
//#                           Bruce Wilson, 905-771-6161
//miteksys-lm     1482/tcp    Miteksys License Manager
//miteksys-lm     1482/udp    Miteksys License Manager
//#                           Shane McRoberts <mcroberts&miteksys.com>
//afs             1483/tcp    AFS License Manager   
//afs             1483/udp    AFS License Manager   
//#                           Michael R. Pizolato <michael&afs.com>
//confluent       1484/tcp    Confluent License Manager 
//confluent       1484/udp    Confluent License Manager 
//#                           James Greenfiel <jim&pa.confluent.com>
//lansource       1485/tcp    LANSource 
//lansource       1485/udp    LANSource 
//#                           Christopher Wells <Christopher_Wells&3com.com>
//nms_topo_serv   1486/tcp    nms_topo_serv  
//nms_topo_serv   1486/udp    nms_topo_serv  
//#                           Sylvia Siu <Sylvia_Siu&Novell.CO>
//localinfosrvr   1487/tcp    LocalInfoSrvr  
//localinfosrvr   1487/udp    LocalInfoSrvr  
//#               Brian Matthews <brian_matthews&ibist.ibis.com>
//docstor         1488/tcp    DocStor  
//docstor         1488/udp    DocStor  
//#                           Brian Spears <bspears&salix.com>
//dmdocbroker     1489/tcp    dmdocbroker  
//dmdocbroker     1489/udp    dmdocbroker  
//#                           Razmik Abnous <abnous&documentum.com>
//insitu-conf     1490/tcp    insitu-conf  
//insitu-conf     1490/udp    insitu-conf  
//#                           Paul Blacknell <paul&insitu.com>
//anynetgateway   1491/tcp    anynetgateway  
//anynetgateway   1491/udp    anynetgateway  
//#                           Dan Poirier <poirier&VNET.IBM.COM>
//stone-design-1  1492/tcp    stone-design-1  
//stone-design-1  1492/udp    stone-design-1  
//#                           Andrew Stone <andrew&stone.com>
//netmap_lm       1493/tcp    netmap_lm  
//netmap_lm       1493/udp    netmap_lm  
//#                           Phillip Magson <philm&extro.ucc.su.OZ.AU>
//ica             1494/tcp    ica   
//ica             1494/udp    ica   
//#                           John Richardson, Citrix Systems
//cvc             1495/tcp    cvc  
//cvc             1495/udp    cvc  
//#                           Bill Davidson <billd&equalizer.cray.com>
//liberty-lm      1496/tcp    liberty-lm
//liberty-lm      1496/udp    liberty-lm
//#                           Jim Rogers <trane!jimbo&pacbell.com>
//rfx-lm          1497/tcp    rfx-lm
//rfx-lm          1497/udp    rfx-lm
//#                           Bill Bishop <bil&rfx.rfx.com>
//sybase-sqlany   1498/tcp    Sybase SQL Any
//sybase-sqlany   1498/udp    Sybase SQL Any
//#                           Dave Neudoerffer <Dave.Neudoerffer&ianywhere.com>
//fhc             1499/tcp    Federico Heinz Consultora
//fhc             1499/udp    Federico Heinz Consultora
//#                           Federico Heinz <federico&heinz.com>
//vlsi-lm         1500/tcp    VLSI License Manager
//vlsi-lm         1500/udp    VLSI License Manager
//#                           Shue-Lin Kuo <shuelin&mdk.sanjose.vlsi.com>
//saiscm          1501/tcp    Satellite-data Acquisition System 3 
//saiscm          1501/udp    Satellite-data Acquisition System 3 
//#                           Bill Taylor <sais&ssec.wisc.edu>
//shivadiscovery  1502/tcp    Shiva
//shivadiscovery  1502/udp    Shiva
//#                           Jonathan Wenocur <jhw&Shiva.COM>
//imtc-mcs        1503/tcp    Databeam
//imtc-mcs        1503/udp    Databeam
//#                           Jim Johnston <jjohnston&databeam.com>
//evb-elm         1504/tcp    EVB Software Engineering License Manager
//evb-elm         1504/udp    EVB Software Engineering License Manager
//#                           B.G. Mahesh < mahesh&sett.com>
//funkproxy       1505/tcp    Funk Software, Inc.
//funkproxy       1505/udp    Funk Software, Inc.
//#                           Robert D. Vincent <bert&willowpond.com>
//utcd            1506/tcp    Universal Time daemon (utcd)
//utcd            1506/udp    Universal Time daemon (utcd)
//#                           Walter Poxon <wdp&ironwood.cray.com>
//symplex         1507/tcp    symplex
//symplex         1507/udp    symplex
//#                           Mike Turley <turley&symplex.com>
//diagmond        1508/tcp    diagmond
//diagmond        1508/udp    diagmond
//#                           Pete Moscatelli <moscat&hprdstl0.rose.hp.com>
//robcad-lm       1509/tcp    Robcad, Ltd. License Manager
//robcad-lm       1509/udp    Robcad, Ltd. License Manager
//#                           Hindin Joseph <hindin%robcad&uunet.uu.net>
//mvx-lm          1510/tcp    Midland Valley Exploration Ltd. Lic. Man.
//mvx-lm          1510/udp    Midland Valley Exploration Ltd. Lic. Man.
//#                           Neil Salter <neil&indigo2.mvel.demon.co.uk>Laszlo
//3l-l1           1511/tcp    3l-l1
//3l-l1           1511/udp    3l-l1
//#                           Ian A. Young <iay&threel.co.uk>
//wins            1512/tcp    Microsoft's Windows Internet Name Service
//wins            1512/udp    Microsoft's Windows Internet Name Service
//#                           Pradeep Bahl <pradeepb&microsoft.com>
//fujitsu-dtc     1513/tcp    Fujitsu Systems Business of America, Inc
//fujitsu-dtc     1513/udp    Fujitsu Systems Business of America, Inc
//fujitsu-dtcns   1514/tcp    Fujitsu Systems Business of America, Inc
//fujitsu-dtcns   1514/udp    Fujitsu Systems Business of America, Inc
//#                           Charles A. Higgins <75730.2257&compuserve.com>
//ifor-protocol   1515/tcp    ifor-protocol
//ifor-protocol   1515/udp    ifor-protocol
//#                           Dr. R.P. Alston <robin&gradient.com>
//vpad            1516/tcp    Virtual Places Audio data
//vpad            1516/udp    Virtual Places Audio data
//vpac            1517/tcp    Virtual Places Audio control
//vpac            1517/udp    Virtual Places Audio control
//vpvd            1518/tcp    Virtual Places Video data
//vpvd            1518/udp    Virtual Places Video data
//vpvc            1519/tcp    Virtual Places Video control
//vpvc            1519/udp    Virtual Places Video control
//#                           Avshalom Houri <Avshalom&ubique.com>
//atm-zip-office  1520/tcp    atm zip office
//atm-zip-office  1520/udp    atm zip office
//#                           Wilson Kwan <wilsonk%toronto&zip.atm.com>
//ncube-lm        1521/tcp    nCube License Manager
//ncube-lm        1521/udp    nCube License Manager
//#                           Maxine Yuen <maxine&hq.ncube.com>
//ricardo-lm      1522/tcp    Ricardo North America License Manager
//ricardo-lm      1522/udp    Ricardo North America License Manager
//#                           Mike Flemming <mf&xnet.com>
//cichild-lm      1523/tcp    cichild
//cichild-lm      1523/udp    cichild
//#                           Andy Burgess <aab&cichlid.com>
//ingreslock	1524/tcp    ingres
//ingreslock	1524/udp    ingres
//orasrv          1525/tcp    oracle
//orasrv          1525/udp    oracle
//prospero-np     1525/tcp    Prospero Directory Service non-priv
//prospero-np     1525/udp    Prospero Directory Service non-priv
//pdap-np         1526/tcp    Prospero Data Access Prot non-priv 
//pdap-np         1526/udp    Prospero Data Access Prot non-priv 
//#                           B. Clifford Neuman <bcn&isi.edu>
//tlisrv          1527/tcp    oracle
1527,//tlisrv          1527/udp    oracle
//#                           Unknown Contact
//#		1528        Unassigned (Returned 2007-10-04)
1529,//coauthor        1529/tcp    oracle
//coauthor        1529/udp    oracle
//rap-service     1530/tcp    rap-service
//rap-service     1530/udp    rap-service
//rap-listen      1531/tcp    rap-listen
//rap-listen      1531/udp    rap-listen
//#                           Phil Servita <meister&ftp.com>
//miroconnect     1532/tcp    miroconnect
//miroconnect     1532/udp    miroconnect
//#                           Michael Fischer +49 531 21 13 0
//virtual-places  1533/tcp    Virtual Places Software
//virtual-places  1533/udp    Virtual Places Software
//#                           Avshalom Houri <Avshalom&ubique.com> 
//micromuse-lm    1534/tcp    micromuse-lm    
//micromuse-lm    1534/udp    micromuse-lm    
//#                           Adam Kerrison <adam&micromuse.co.uk>
//ampr-info       1535/tcp    ampr-info    
//ampr-info       1535/udp    ampr-info    
//ampr-inter      1536/tcp    ampr-inter
//ampr-inter      1536/udp    ampr-inter
//#                           Rob Janssen <rob&sys3.pe1chl.ampr.org>
//sdsc-lm         1537/tcp    isi-lm
//sdsc-lm         1537/udp    isi-lm
//#                           Len Wanger <lrw&sdsc.edu>
//3ds-lm          1538/tcp    3ds-lm
//3ds-lm          1538/udp    3ds-lm
//#                           Keith Trummel <ktrummel&autodesk.com>
//intellistor-lm  1539/tcp    Intellistor License Manager
//intellistor-lm  1539/udp    Intellistor License Manager
//#                           Ron Vaughn <rv&intellistor.com>
//rds             1540/tcp    rds
//rds             1540/udp    rds
//rds2            1541/tcp    rds2
//rds2            1541/udp    rds2
//#                           Sudhakar Rajamannar <mobius1&cerfnet.com>
//gridgen-elmd    1542/tcp    gridgen-elmd
//gridgen-elmd    1542/udp    gridgen-elmd
//#                           John R. Chawner +1 817 354-1004
//simba-cs        1543/tcp    simba-cs
//simba-cs        1543/udp    simba-cs
//#                           Betsy Alexander +1 604-681-4549
//aspeclmd        1544/tcp    aspeclmd
//aspeclmd        1544/udp    aspeclmd
//#                           V. Balaji <balaji&aspec.com>
//vistium-share   1545/tcp    vistium-share
//vistium-share   1545/udp    vistium-share
//#                           Allison Carleton 
//#                           <acarleto&naper1.napervilleil.ncr.com>
//abbaccuray      1546/tcp    abbaccuray
//abbaccuray      1546/udp    abbaccuray
//#                           John Wendt 614-261-2000
//laplink         1547/tcp    laplink
//laplink         1547/udp    laplink
//#                           Michael Crawford <MichaelC&dev.travsoft.com>
//axon-lm         1548/tcp    Axon License Manager
//axon-lm         1548/udp    Axon License Manager
//#   Mark Pearce <<Mark_A.._Pearce/AXON_Networks_Inc..&notes.axon.com>
//shivahose       1549/tcp    Shiva Hose
//shivasound      1549/udp    Shiva Sound
//#                           Kin Chan <kchan&shiva.com>
//3m-image-lm     1550/tcp    Image Storage license manager 3M Company
//3m-image-lm     1550/udp    Image Storage license manager 3M Company
//#                           J. C. Canessa <jccanessa&mmm.com>
//hecmtl-db       1551/tcp    HECMTL-DB
//hecmtl-db       1551/udp    HECMTL-DB
//#                           Maxime Belanger <R173&hec.ca>
//pciarray        1552/tcp    pciarray
//pciarray        1552/udp    pciarray
//#                           Ron Folk <rfolkes&avl.com>
//sna-cs          1553/tcp    sna-cs
//sna-cs          1553/udp    sna-cs
//#                           Tony Sowter <ts&datcon.co.uk>
//caci-lm         1554/tcp    CACI Products Company License Manager
//caci-lm         1554/udp    CACI Products Company License Manager
//#                           Erik Blume <erikb&caciasl.com>
//livelan         1555/tcp    livelan
//livelan         1555/udp    livelan
//#                           khedayat&roadrunner.pictel.com <Kaynam Hedayat>
//veritas_pbx     1556/tcp    VERITAS Private Branch Exchange
//veritas_pbx     1556/udp    VERITAS Private Branch Exchange                        
//#                           Stefan Winkel <stefan&veritas.com> April 2004
//arbortext-lm    1557/tcp    ArborText License Manager
//arbortext-lm    1557/udp    ArborText License Manager
//#                           David J. Wilson <djw&arbortext.com>
//xingmpeg        1558/tcp    xingmpeg
//xingmpeg        1558/udp    xingmpeg
//#                           Howard Gordon <hgordon&system.xingtech.com>
//web2host        1559/tcp    web2host
//web2host        1559/udp    web2host
//#                           Stephen Johnson <sjohnson&mindspring.com>
//asci-val        1560/tcp    ASCI-RemoteSHADOW
//asci-val        1560/udp    ASCI-RemoteSHADOW
//#                           Benjamin Rosenberg <brosenberg&advsyscon.com>
//facilityview    1561/tcp    facilityview
//facilityview    1561/udp    facilityview
//#                           Ed Green <egreen&pmeasuring.com>
//pconnectmgr     1562/tcp    pconnectmgr
//pconnectmgr     1562/udp    pconnectmgr
//#                           Bob Kaiser <BKaiser&palindrome.com>
//cadabra-lm      1563/tcp    Cadabra License Manager
//cadabra-lm      1563/udp    Cadabra License Manager
//#                           Arthur Castonguay <arthurc&doe.carleton.ca>
//pay-per-view    1564/tcp    Pay-Per-View
//pay-per-view    1564/udp    Pay-Per-View
//#                           Brian Tung <brian&isi.edu>
//winddlb         1565/tcp    WinDD
//winddlb         1565/udp    WinDD
//#                           Kelly Sims <kellys&garnet.wv.tek.com>
//corelvideo      1566/tcp    CORELVIDEO
//corelvideo      1566/udp    CORELVIDEO
//#                           Ming Poon <mingp&corel.ca>
//jlicelmd        1567/tcp    jlicelmd
//jlicelmd        1567/udp    jlicelmd
//#                           Christian Schormann <100410.3063&compuserve.com>
//tsspmap         1568/tcp    tsspmap
//tsspmap         1568/udp    tsspmap
//#                           Paul W. Nelson <nelson&thursby.com>
//ets             1569/tcp    ets
//ets             1569/udp    ets
//#                           Carstein Seeberg <case&boole.no> 
//orbixd          1570/tcp    orbixd
//orbixd          1570/udp    orbixd
//#                           Bridget Walsh <bwalsh&iona.ie>
//rdb-dbs-disp    1571/tcp    Oracle Remote Data Base
//rdb-dbs-disp    1571/udp    Oracle Remote Data Base
//#                           <mackin&us.oracle.com>
//chip-lm         1572/tcp    Chipcom License Manager
//chip-lm         1572/udp    Chipcom License Manager
//#                           Jerry Natowitz <Jerry Natowitz>
//itscomm-ns      1573/tcp    itscomm-ns
//itscomm-ns      1573/udp    itscomm-ns
//#                           Rich Thompson <richt&watson.ibm.com>
//mvel-lm         1574/tcp    mvel-lm
//mvel-lm         1574/udp    mvel-lm
//#                           David Bisset <dbisset&mvel.demon.co.uk>
//oraclenames     1575/tcp    oraclenames
//oraclenames     1575/udp    oraclenames
//#                           P.V.Shivkumar <PSHIVKUM&us.oracle.com>
//moldflow-lm     1576/tcp    Moldflow License Manager
//moldflow-lm     1576/udp    Moldflow License Manager
//#			    Lech Laskowski <lech_laskowski&moldflow.com>
//hypercube-lm    1577/tcp    hypercube-lm
//hypercube-lm    1577/udp    hypercube-lm
//#                           Christopher McLendon <cem&hyper.com>
//jacobus-lm      1578/tcp    Jacobus License Manager
//jacobus-lm      1578/udp    Jacobus License Manager
//#                           Tony Cleveland <tony.cleveland&jacobus.com>
//ioc-sea-lm      1579/tcp    ioc-sea-lm
//ioc-sea-lm      1579/udp    ioc-sea-lm
//#                           Paul Nelson <paul&ioc-sea.com>
//tn-tl-r1        1580/tcp    tn-tl-r1
//tn-tl-r2        1580/udp    tn-tl-r2
//#                           Ed Kress <eskress&thinknet.com>
//mil-2045-47001  1581/tcp    MIL-2045-47001
//mil-2045-47001  1581/udp    MIL-2045-47001
//#                           Eric Whitehill <Eric.Whitehill&itt.com>
//msims           1582/tcp    MSIMS
//msims           1582/udp    MSIMS
//#                           Glenn Olander <gjo&msi.com>
//simbaexpress    1583/tcp    simbaexpress
//simbaexpress    1583/udp    simbaexpress
//#                           Betsy Alexander +1 604-681-4549
//tn-tl-fd2       1584/tcp    tn-tl-fd2
//tn-tl-fd2       1584/udp    tn-tl-fd2
//#                           Ed Kress <eskress&thinknet.com>
//intv            1585/tcp    intv
//intv            1585/udp    intv
//#                           Dermot Tynand <dtynan&claddagh.ie>
//ibm-abtact      1586/tcp    ibm-abtact
//ibm-abtact      1586/udp    ibm-abtact
//#                           Sandeep K. Singhal <singhal&CS.Stanford.EDU>
//pra_elmd        1587/tcp    pra_elmd
//pra_elmd        1587/udp    pra_elmd
//#                           Dennis Mastin <dennis&tasmania.platte.com>
//triquest-lm     1588/tcp    triquest-lm 
//triquest-lm     1588/udp    triquest-lm 
//#                           Nand Kumar <nkumar&triquest-da.com>
//vqp             1589/tcp    VQP
//vqp             1589/udp    VQP
//#                           Keith McCloghrie <kzm&cisco.com>
//gemini-lm       1590/tcp    gemini-lm
//gemini-lm       1590/udp    gemini-lm
//#                           Tony Sawyer <tonys&gemtech.com>
//ncpm-pm         1591/tcp    ncpm-pm
//ncpm-pm         1591/udp    ncpm-pm
//#                           Ted Power <tedp&hpinpcb.cup.hp.com>
//commonspace     1592/tcp    commonspace
//commonspace     1592/udp    commonspace
//#                           Rob Chandhok <chandhok&within.com>
//mainsoft-lm     1593/tcp    mainsoft-lm
//mainsoft-lm     1593/udp    mainsoft-lm
//#                           Anand Gangadharan <anand&goa.mainsoft.com>
//sixtrak         1594/tcp    sixtrak
//sixtrak         1594/udp    sixtrak
//#                           Bob Rennie <rjrennie&wizvax.net>
//radio           1595/tcp    radio
//radio           1595/udp    radio
//radio-sm        1596/tcp    radio-sm
//radio-bc        1596/udp    radio-bc
//#                           Ken Chapman <kchapman&isis.com>
//orbplus-iiop    1597/tcp    orbplus-iiop
//orbplus-iiop    1597/udp    orbplus-iiop
//#                           Robert A. Kukura <kukura&apollo.hp.com>
//picknfs         1598/tcp    picknfs
//picknfs         1598/udp    picknfs
//#                           John Lombardo <johnl&picksys.com>
//simbaservices   1599/tcp    simbaservices
//simbaservices   1599/udp    simbaservices
//#                           Betsy Alexander +1 604-681-4549
//issd		1600/tcp   issd
//issd		1600/udp   issd
//aas             1601/tcp   aas
//aas             1601/udp   aas
//#                          Bob Beard <bobb&lachman.com>
//inspect         1602/tcp   inspect
//inspect         1602/udp   inspect
//#                          Frank O'Neill <frank&morse.ilo.dec.com>
//picodbc         1603/tcp   pickodbc
//picodbc         1603/udp   pickodbc
//#                          John Lombardo <johnl&picksys.com>
//icabrowser      1604/tcp   icabrowser
//icabrowser      1604/udp   icabrowser
//#                          Brad Pedersen <bradp&citrix.com>       
//slp             1605/tcp   Salutation Manager (Salutation Protocol)
//slp             1605/udp   Salutation Manager (Salutation Protocol)
//slm-api         1606/tcp   Salutation Manager (SLM-API)
//slm-api         1606/udp   Salutation Manager (SLM-API)
//#                          Tohru Mori <tmori&VNET.IBM.COM>       
//stt             1607/tcp   stt
//stt             1607/udp   stt
//#                          Ryan Bolz <ryanbo&microsoft.com>
//smart-lm        1608/tcp   Smart Corp. License Manager
//smart-lm        1608/udp   Smart Corp. License Manager
//#                          Connie Qiu <connie&scdb.com>
//isysg-lm        1609/tcp   isysg-lm
//isysg-lm        1609/udp   isysg-lm
//#                          Adam Curtin <adam.curtin&isysg.com>
//taurus-wh       1610/tcp   taurus-wh
//taurus-wh       1610/udp   taurus-wh
//#                          Jeff Moffatt <jeff&taurus.com>
//ill             1611/tcp   Inter Library Loan
//ill             1611/udp   Inter Library Loan
//#                          Niall Murphy <niallm&orca.ucd.ie>
//netbill-trans   1612/tcp   NetBill Transaction Server
//netbill-trans   1612/udp   NetBill Transaction Server
//netbill-keyrep  1613/tcp   NetBill Key Repository
//netbill-keyrep  1613/udp   NetBill Key Repository
//netbill-cred    1614/tcp   NetBill Credential Server
//netbill-cred    1614/udp   NetBill Credential Server
//netbill-auth    1615/tcp   NetBill Authorization Server
//netbill-auth    1615/udp   NetBill Authorization Server
//netbill-prod    1616/tcp   NetBill Product Server
//netbill-prod    1616/udp   NetBill Product Server
//#                          Marvin Sirbu <sirbu+&andrew.cmu.edu>
//nimrod-agent    1617/tcp   Nimrod Inter-Agent Communication
//nimrod-agent    1617/udp   Nimrod Inter-Agent Communication
//#                          Charles Lynn <clynn&bbn.com>
//skytelnet       1618/tcp   skytelnet
//skytelnet       1618/udp   skytelnet
//#                          Byron Jones <byronj&bellsouth.net>
//xs-openstorage  1619/tcp  xs-openstorage
//xs-openstorage  1619/udp  xs-openstorage
//#                         XuiS Software Ltd. <100322.2376&compuserve.com>
//faxportwinport  1620/tcp  faxportwinport
//faxportwinport  1620/udp  faxportwinport
//#                         Chris Wells <chris_wells&lansource.com>
//softdataphone   1621/tcp  softdataphone
//softdataphone   1621/udp  softdataphone
//#                         Dror Gill <drorgi&VNET.IBM.COM>
//ontime          1622/tcp  ontime
//ontime          1622/udp  ontime
//#                         Keith Rhodes 810-559-5955
//jaleosnd        1623/tcp  jaleosnd
//jaleosnd        1623/udp  jaleosnd
//#                         Christian Schormann <100410.3063&compuserve.com>
//udp-sr-port     1624/tcp  udp-sr-port
//udp-sr-port     1624/udp  udp-sr-port
//#                         Herb Jensen <HWJensen&nfsrv.avionics.itt.com>
//svs-omagent     1625/tcp  svs-omagent
//svs-omagent     1625/udp  svs-omagent
//#                         Alberto Berlen <aberlen&VNET.IBM.COM>
//shockwave	1626/tcp  Shockwave
//shockwave	1626/udp  Shockwave
//#			  Sarah Allen <sallen&macromedia.com>
//t128-gateway	1627/tcp  T.128 Gateway
//t128-gateway	1627/udp  T.128 Gateway
//#			  Phil May <pm&datcon.co.uk>
//lontalk-norm	1628/tcp  LonTalk normal
//lontalk-norm	1628/udp  LonTalk normal
//lontalk-urgnt	1629/tcp  LonTalk urgent
//lontalk-urgnt	1629/udp  LonTalk urgent
//#                         Previous contact: Dan Wing <dwing&cisco.com>
//#                         Current contact: Bob Dolin <bdolin&echelon.com> 10 April 2008
//oraclenet8cman	1630/tcp  Oracle Net8 Cman
//oraclenet8cman	1630/udp  Oracle Net8 Cman
//#			  Tong-Ming Lee <tmlee&us.oracle.com>
//visitview	1631/tcp  Visit view 	
//visitview	1631/udp  Visit view 	
//#			  Tom Whittaker <tomw&ssec.wisc.edu>
//pammratc	1632/tcp  PAMMRATC
//pammratc	1632/udp  PAMMRATC
//pammrpc		1633/tcp  PAMMRPC
//pammrpc		1633/udp  PAMMRPC
//#			  John Britton <johnb&peakaudio.com>
//loaprobe	1634/tcp  Log On America Probe
//loaprobe	1634/udp  Log On America Probe
//#			  James Tavares, Log On America <krontor&loa.com> 
//edb-server1     1635/tcp  EDB Server 1
//edb-server1     1635/udp  EDB Server 1
//#                         Carlos Portela <cportela&simple-sw.com>
//isdc		1636/tcp  ISP shared public data control 
//isdc 		1636/udp  ISP shared public data control
//islc 		1637/tcp  ISP shared local data control
//islc 		1637/udp  ISP shared local data control
//ismc 		1638/tcp  ISP shared management control
//ismc 		1638/udp  ISP shared management control
//#                         Nick Austin <ogmion&ogmium.com>
//cert-initiator  1639/tcp  cert-initiator
//cert-initiator  1639/udp  cert-initiator
//cert-responder  1640/tcp  cert-responder
//cert-responder  1640/udp  cert-responder
//#                         Tom Markson <markson&osmosys.incog.com>
//invision        1641/tcp  InVision
//invision        1641/udp  InVision
//#                         Christopher Davey <niallocl&quay.ie>
//isis-am         1642/tcp  isis-am
//isis-am         1642/udp  isis-am
//isis-ambc       1643/tcp  isis-ambc
//isis-ambc       1643/udp  isis-ambc
//#                         Ken Chapman <kchapman&isis.com>
//saiseh          1644/tcp  Satellite-data Acquisition System 4
//#                         Bill Taylor <sais&ssec.wisc.edu>
//sightline       1645/tcp  SightLine   
//sightline       1645/udp  SightLine  
//#                         admin <iana&sightlinesystems.com> 
//sa-msg-port     1646/tcp  sa-msg-port
//sa-msg-port     1646/udp  sa-msg-port
//#                         Eric Whitehill <Eric.Whitehill&itt.com>
//rsap            1647/tcp  rsap
//rsap            1647/udp  rsap
//#                         Holger Reif 
//#                         <Holger.Reif&prakinf.tu-ilmenau.de> 
//concurrent-lm   1648/tcp  concurrent-lm
//concurrent-lm   1648/udp  concurrent-lm
//#                         Maggie Brinsford <mjb&concurrent.co.uk>
//kermit          1649/tcp  kermit
//kermit          1649/udp  kermit 
//#                         Frank da Cruz <fdc&watsun.cc.columbia.edu>
//nkd		1650/tcp  nkdn
//nkd		1650/udp  nkd
//shiva_confsrvr  1651/tcp  shiva_confsrvr
//shiva_confsrvr  1651/udp  shiva_confsrvr
//#                         Mike Horowitz <mah&Shiva.COM>
//xnmp            1652/tcp  xnmp
//xnmp            1652/udp  xnmp
//#                         Ali Saleh <scomm&cerf.net>
//alphatech-lm    1653/tcp  alphatech-lm
//alphatech-lm    1653/udp  alphatech-lm
//#                         Joseph Hauk <joseph.hauk&alphatech.com>
//stargatealerts  1654/tcp  stargatealerts
//stargatealerts  1654/udp  stargatealerts
//#                         Tim Coppernoll
//#                         <Tim_Coppernoll&ccm.jf.intel.com>
//dec-mbadmin     1655/tcp  dec-mbadmin
//dec-mbadmin     1655/udp  dec-mbadmin
//dec-mbadmin-h   1656/tcp  dec-mbadmin-h
//dec-mbadmin-h   1656/udp  dec-mbadmin-h
//#                         Nick Shipman <Nick.Shipman&mrmog.reo.dec.com>
//fujitsu-mmpdc   1657/tcp  fujitsu-mmpdc
//fujitsu-mmpdc   1657/udp  fujitsu-mmpdc
//#                         Katsumi Oomuro <NAE01421&niftyserve.or.jp>
//sixnetudr       1658/tcp  sixnetudr
//sixnetudr       1658/udp  sixnetudr
//#                         Bob Rennie <rjrennie&wizvax.net>
//sg-lm           1659/tcp  Silicon Grail License Manager
//sg-lm           1659/udp  Silicon Grail License Manager
//#                         William R Bishop <wrb&world.std.com>
//skip-mc-gikreq  1660/tcp  skip-mc-gikreq
//skip-mc-gikreq  1660/udp  skip-mc-gikreq
//#                         Tom Markson <markson&osmosys.incog.com>
//netview-aix-1   1661/tcp  netview-aix-1
//netview-aix-1   1661/udp  netview-aix-1
//netview-aix-2   1662/tcp  netview-aix-2
//netview-aix-2   1662/udp  netview-aix-2
//netview-aix-3   1663/tcp  netview-aix-3
//netview-aix-3   1663/udp  netview-aix-3
//netview-aix-4   1664/tcp  netview-aix-4
//netview-aix-4   1664/udp  netview-aix-4
//netview-aix-5   1665/tcp  netview-aix-5
//netview-aix-5   1665/udp  netview-aix-5
//netview-aix-6   1666/tcp  netview-aix-6
//netview-aix-6   1666/udp  netview-aix-6
//netview-aix-7   1667/tcp  netview-aix-7
//netview-aix-7   1667/udp  netview-aix-7
//netview-aix-8   1668/tcp  netview-aix-8
//netview-aix-8   1668/udp  netview-aix-8
//netview-aix-9   1669/tcp  netview-aix-9
//netview-aix-9   1669/udp  netview-aix-9
//netview-aix-10  1670/tcp  netview-aix-10
//netview-aix-10  1670/udp  netview-aix-10
//netview-aix-11  1671/tcp  netview-aix-11
//netview-aix-11  1671/udp  netview-aix-11
//netview-aix-12  1672/tcp  netview-aix-12
//netview-aix-12  1672/udp  netview-aix-12
//#                         Martha Crisson 
//#                         <CRISSON&ralvm12.vnet.ibm.com>
//proshare-mc-1   1673/tcp  Intel Proshare Multicast
//proshare-mc-1   1673/udp  Intel Proshare Multicast
//proshare-mc-2   1674/tcp  Intel Proshare Multicast
//proshare-mc-2   1674/udp  Intel Proshare Multicast
//#                         Mark Lewis <Mark_Lewis&ccm.jf.intel.com>
//pdp             1675/tcp  Pacific Data Products
//pdp             1675/udp  Pacific Data Products
//#                         Gary Morton <mortong&pacdata.com>
//netcomm1        1676/tcp  netcomm1
//netcomm2        1676/udp  netcomm2
//#                         Bulent Kasman <BKasman&symantec.com>
//groupwise       1677/tcp  groupwise
//groupwise       1677/udp  groupwise
//#                         Brent Bradshaw <bbradshaw&novell.com>
//prolink         1678/tcp  prolink
//prolink         1678/udp  prolink
//#                         Brian Abramson <brianab&soul.tv.tek.com>
//darcorp-lm      1679/tcp  darcorp-lm
//darcorp-lm      1679/udp  darcorp-lm
//#                         <DARcorp&aol.com>
//microcom-sbp    1680/tcp  microcom-sbp	
//microcom-sbp    1680/udp  microcom-sbp	
//#                         Boris B. Maiden <Boris_Maiden&smtp.microcom.com> 
//sd-elmd         1681/tcp  sd-elmd
//sd-elmd         1681/udp  sd-elmd
//#                         Bryan Otey <bwo&softdesk.com>
//lanyon-lantern  1682/tcp  lanyon-lantern
//lanyon-lantern  1682/udp  lanyon-lantern
//#                         Robin Lewis <robin.lewis&lanyon.com>
//ncpm-hip        1683/tcp  ncpm-hip
//ncpm-hip        1683/udp  ncpm-hip
//#                         Ken Hearn <hearn&hpindacx.cup.hp.com>
//snaresecure     1684/tcp  SnareSecure
//snaresecure     1684/udp  SnareSecure
//#                         Marty Batchelder <marty&capres.com>
//n2nremote       1685/tcp  n2nremote
//n2nremote       1685/udp  n2nremote
//#                         Kin Chan <kchan&net2net.com>
//cvmon           1686/tcp  cvmon
//cvmon           1686/udp  cvmon
//#                         Carol Ann Krug <carolann&hpmfas3.cup.hp.com>
//nsjtp-ctrl      1687/tcp    nsjtp-ctrl
//nsjtp-ctrl      1687/udp    nsjtp-ctrl
//nsjtp-data      1688/tcp    nsjtp-data
//nsjtp-data      1688/udp    nsjtp-data
//#                           Orazio Granato <og&wsbgrd01.italy.hp.com>
//firefox         1689/tcp    firefox
//firefox         1689/udp    firefox
//#                           Mark S. Edwards <marke&firefox.co.uk>
//ng-umds         1690/tcp    ng-umds
//ng-umds         1690/udp    ng-umds
//#                           Louis E. Simard <76400.3371&compuserve.com>
//empire-empuma   1691/tcp    empire-empuma
//empire-empuma   1691/udp    empire-empuma
//#                           Bobby Krupczak <rdk&empiretech.com>
//sstsys-lm       1692/tcp    sstsys-lm
//sstsys-lm       1692/udp    sstsys-lm
//#                           Yih-Wu Wang <sstsys&ix.netcom.com>
//rrirtr          1693/tcp    rrirtr
//rrirtr          1693/udp    rrirtr
//rrimwm          1694/tcp    rrimwm
//rrimwm          1694/udp    rrimwm
//rrilwm          1695/tcp    rrilwm
//rrilwm          1695/udp    rrilwm
//rrifmm          1696/tcp    rrifmm
//rrifmm          1696/udp    rrifmm
//rrisat          1697/tcp    rrisat
//rrisat          1697/udp    rrisat
//#                           Allen Briggs <briggs&access.rrinc.com>
//rsvp-encap-1    1698/tcp    RSVP-ENCAPSULATION-1
//rsvp-encap-1    1698/udp    RSVP-ENCAPSULATION-1
//rsvp-encap-2    1699/tcp    RSVP-ENCAPSULATION-2
//rsvp-encap-2    1699/udp    RSVP-ENCAPSULATION-2
//#                           Bob Braden <braden&isi.edu>
//mps-raft        1700/tcp    mps-raft
//mps-raft        1700/udp    mps-raft
//#                           Jason Leupen <Jleupen&aol.com>
//l2f             1701/tcp    l2f
//l2f             1701/udp    l2f
//l2tp		1701/tcp    l2tp
//l2tp		1701/udp    l2tp
//#                           Andy Valencia <vandys&vandys-lap.cisco.com>
//deskshare       1702/tcp    deskshare
//deskshare       1702/udp    deskshare
//#                           Sarah Thompson <sarah&telergy.com
//hb-engine       1703/tcp    hb-engine
//hb-engine       1703/udp    hb-engine
//#                           Charles C.L. Chou >cchou&zoom.com>
//bcs-broker      1704/tcp    bcs-broker
//bcs-broker      1704/udp    bcs-broker
//#                           Andy Warner <andyw&knoware.nl>
//slingshot       1705/tcp    slingshot
//slingshot       1705/udp    slingshot
//#                           Paul Groarke <paulg&quay.ie>
//jetform         1706/tcp    jetform
//jetform         1706/udp    jetform
//#                           gdeinsta <gdeinsta&jetform.com>
//vdmplay         1707/tcp    vdmplay
//vdmplay         1707/udp    vdmplay
//#                           David Thielen <support&windward.net>
//gat-lmd         1708/tcp    gat-lmd
//gat-lmd         1708/udp    gat-lmd
//#                           Igor Zaoutine <igor&global-tech.com>
//centra          1709/tcp    centra
//centra          1709/udp    centra
//#                           Drew Wolff <dwolff&centra.net>
//impera          1710/tcp    impera
//impera          1710/udp    impera
//#                           Stepehen Campbell <campbell&uniprise.com>
//pptconference   1711/tcp    pptconference
//pptconference   1711/udp    pptconference
//#                           John Tafoya <johnt&microsoft.com>
//registrar       1712/tcp    resource monitoring service
//registrar       1712/udp    resource monitoring service
//#                           Ron Lawson <ronaldl&hpindacx.cup.hp.com>
//conferencetalk  1713/tcp    ConferenceTalk
//conferencetalk  1713/udp    ConferenceTalk
//#                           George Kajos <gkajos&mail1.videoserver.com>
//sesi-lm         1714/tcp    sesi-lm
//sesi-lm         1714/udp    sesi-lm
//houdini-lm      1715/tcp    houdini-lm
//houdini-lm      1715/udp    houdini-lm
//#                           Paul Breslin <phb&SIDEFX.COM>
//xmsg            1716/tcp    xmsg
//xmsg            1716/udp    xmsg
//#                           Mark E. Fogle <mefogle&xantel.com>
//fj-hdnet        1717/tcp    fj-hdnet
//fj-hdnet        1717/udp    fj-hdnet
//#                           Manabu Makino <m-makino&ael.fujitsu.co.jp>
//h323gatedisc    1718/tcp    h323gatedisc
//h323gatedisc    1718/udp    h323gatedisc
//h323gatestat    1719/tcp    h323gatestat 
//h323gatestat    1719/udp    h323gatestat 
//h323hostcall    1720/tcp    h323hostcall
//h323hostcall    1720/udp    h323hostcall
//#                           Jim Toga <jtoga&ibeam.jf.intel.com>
//caicci          1721/tcp    caicci
//caicci          1721/udp    caicci
//#                           Sylvia Scheuren <schsy02&cai.com>
//hks-lm          1722/tcp    HKS License Manager
//hks-lm          1722/udp    HKS License Manager
//#                           Michael Wood <wood&althea.hks.com>
//pptp            1723/tcp    pptp
//pptp            1723/udp    pptp
//#                           Ken Crocker <kcrocker&microsoft.com>
//csbphonemaster  1724/tcp    csbphonemaster
//csbphonemaster  1724/udp    csbphonemaster
//#                           Hans-Peter Heffels <hostmaster&csb-system.com>
//iden-ralp       1725/tcp    iden-ralp
//iden-ralp       1725/udp    iden-ralp
//#                           Chris Stanaway <stanaway&comm.mot.com>
//iberiagames     1726/tcp    IBERIAGAMES
//iberiagames     1726/udp    IBERIAGAMES
//#                           Jose Luis <73374.313&compuserve.com>
//winddx          1727/tcp    winddx
//winddx          1727/udp    winddx
//#                           Bill Andrews <billa&vnd.tek.com>
//telindus        1728/tcp    TELINDUS
//telindus        1728/udp    TELINDUS
//#                           Paul Pyck <papy&telindus.be
//citynl          1729/tcp    CityNL License Management
//citynl          1729/udp    CityNL License Management
//#                           CityDisc >citydisc&euronet.nl>
//roketz          1730/tcp    roketz
//roketz          1730/udp    roketz
//#                           Ahti Heinla <ahti&ahti.bluemoon.ee>
//msiccp          1731/tcp    MSICCP
//msiccp          1731/udp    MSICCP
//#                           Max Morris <maxm&MICROSOFT.com>
//proxim          1732/tcp    proxim
//proxim          1732/udp    proxim
//#                           Srinivas N. Mogalapalli <srinivas&proxim.com>
//siipat          1733/tcp    SIMS - SIIPAT Protocol for Alarm Transmission
//siipat          1733/udp    SIMS - SIIPAT Protocol for Alarm Transmission
//#                           Steve Ryckman <iana&simsware.com>
//cambertx-lm     1734/tcp    Camber Corporation License Management
//cambertx-lm     1734/udp    Camber Corporation License Management
//#                           Jeannie Burleson <jeannie&cambertx.com>
//privatechat     1735/tcp    PrivateChat
//privatechat     1735/udp    PrivateChat
//#                           Louis E. Simard <76400.3371&CompuServe.COM>
//street-stream   1736/tcp    street-stream
//street-stream   1736/udp    street-stream
//#                           Glenn Levitt <streetd1&ix.netcom.com>
//ultimad         1737/tcp    ultimad
//ultimad         1737/udp    ultimad
//#                           (Michael Lanzetta <hagbard&ultimatech.com>
//gamegen1        1738/tcp    GameGen1
//gamegen1        1738/udp    GameGen1
//#                           Glen Pearson <GlenP&multigen.com>
//webaccess       1739/tcp    webaccess
//webaccess       1739/udp    webaccess
//#                           Christian Saether <ChristianS&asymetrix.com>
//encore          1740/tcp    encore
//encore          1740/udp    encore
//#                           Stuart Button <button&promis.com>
//cisco-net-mgmt  1741/tcp    cisco-net-mgmt
//cisco-net-mgmt  1741/udp    cisco-net-mgmt
//#                           John McCormack <jmac&cisco.com>
//3Com-nsd        1742/tcp    3Com-nsd
//3Com-nsd        1742/udp    3Com-nsd
//#                           Nitza Steinberg <nitza&isd.3com.com>
//cinegrfx-lm     1743/tcp    Cinema Graphics License Manager
//cinegrfx-lm     1743/udp    Cinema Graphics License Manager
//#                           Rodney Iwashina <rodney&cyclone.rfx.com>
//ncpm-ft         1744/tcp    ncpm-ft
//ncpm-ft         1744/udp    ncpm-ft
//#                           Ken Hearn <hearn&hpindacx.cup.hp.com>
//remote-winsock  1745/tcp    remote-winsock
//remote-winsock  1745/udp    remote-winsock
//#                           Avi Nathan <avin&microsoft.com>
//ftrapid-1       1746/tcp    ftrapid-1
//ftrapid-1       1746/udp    ftrapid-1
//ftrapid-2       1747/tcp    ftrapid-2
//ftrapid-2       1747/udp    ftrapid-2
//#                           Richard J. Williams <RJW1&trpo4.tr.unisys.com>
//oracle-em1      1748/tcp    oracle-em1
//oracle-em1      1748/udp    oracle-em1
//#                           Bob Purvy <bpurvy&us.oracle.com>
//aspen-services  1749/tcp    aspen-services
//aspen-services  1749/udp    aspen-services
//#                           Mark B. Hurst <mhurst&aspenres.com>
//sslp            1750/tcp    Simple Socket Library's PortMaster
//sslp            1750/udp    Simple Socket Library's PortMaster
//#                           Dr. Charles E. Campbell Jr.
//#                           <cec&gryphon.gsfc.nasa.gov> 
//swiftnet        1751/tcp    SwiftNet
//swiftnet        1751/udp    SwiftNet
//#                           Terry Lim <tkl&pentek.com>
//lofr-lm         1752/tcp    Leap of Faith Research License Manager 
1752,//lofr-lm         1752/udp    Leap of Faith Research License Manager 
//#                           
//#               1753        Unassigned (Removed 2004-05-18)
1754,//oracle-em2      1754/tcp    oracle-em2
//oracle-em2      1754/udp    oracle-em2
//#                           Bob Purvy <bpurvy&us.oracle.com>
//ms-streaming    1755/tcp    ms-streaming
//ms-streaming    1755/udp    ms-streaming
//#                           Bret O'Rourke <bretor&microsoft.com>
//capfast-lmd     1756/tcp    capfast-lmd
//capfast-lmd     1756/udp    capfast-lmd
//#                           Chuck Neal <chuck&phase3.com>
//cnhrp           1757/tcp    cnhrp
//cnhrp           1757/udp    cnhrp
//#                           William Stoye <wstoye&atml.co.uk>
//tftp-mcast      1758/tcp    tftp-mcast
//tftp-mcast      1758/udp    tftp-mcast
//#                           Tom Emberson <tom&lanworks.com>
//spss-lm         1759/tcp    SPSS License Manager
//spss-lm         1759/udp    SPSS License Manager
//#                           Tex Hull <tex&spss.com>
//www-ldap-gw     1760/tcp    www-ldap-gw
//www-ldap-gw     1760/udp    www-ldap-gw
//#                           Nick Emery <Nick.Emery&altavista.digital.com>
//cft-0           1761/tcp    cft-0
//cft-0           1761/udp    cft-0
//cft-1           1762/tcp    cft-1
//cft-1           1762/udp    cft-1
//cft-2           1763/tcp    cft-2
//cft-2           1763/udp    cft-2
//cft-3           1764/tcp    cft-3
//cft-3           1764/udp    cft-3
//cft-4           1765/tcp    cft-4
//cft-4           1765/udp    cft-4
//cft-5           1766/tcp    cft-5
//cft-5           1766/udp    cft-5
//cft-6           1767/tcp    cft-6
//cft-6           1767/udp    cft-6
//cft-7           1768/tcp    cft-7
//cft-7           1768/udp    cft-7
//#                           Martine Marchand 16 1 46 59 24 84
//bmc-net-adm     1769/tcp    bmc-net-adm
//bmc-net-adm     1769/udp    bmc-net-adm
//#                           Portnoy Boxman <portnoy_boxman&bmc.com>
//bmc-net-svc     1770/tcp    bmc-net-svc
//bmc-net-svc     1770/udp    bmc-net-svc
//#                           Portnoy Boxman <portnoy_boxman&bmc.com>
//vaultbase       1771/tcp    vaultbase
//vaultbase       1771/udp    vaultbase
//#                           Jose A. Sesin <sesin&vaultbase.com>
//essweb-gw       1772/tcp    EssWeb Gateway
//essweb-gw       1772/udp    EssWeb Gateway
//#                           Bob Nattenberg <bnattenberg&arborsoft.com>
//kmscontrol      1773/tcp    KMSControl
//kmscontrol      1773/udp    KMSControl
//#                           Roy Chastain <roy&kmsys.com>
//global-dtserv   1774/tcp    global-dtserv
//global-dtserv   1774/udp    global-dtserv
//#                           Nicholas Davies <N.Davies&globalcomm.co.uk>
//#               1775/tcp
//femis           1776/tcp    Federal Emergency Management Information System
//femis           1776/udp    Federal Emergency Management Information System
//#                           Larry Gerhardstein <lh_gerhardstein&pnl.gov>
//powerguardian   1777/tcp    powerguardian
//powerguardian   1777/udp    powerguardian
//#                           Previous Contact: Charles Bennett <chuck&benatong.com>
//#                           Current Contact: Charles Bennett <bennettc&ohio.edu> 29 August 2008
//prodigy-intrnet	1778/tcp    prodigy-internet
//prodigy-intrnet	1778/udp    prodigy-internet
//#                           Bob Dedrick <bob&staff.prodigy.com>
//pharmasoft      1779/tcp    pharmasoft
//pharmasoft      1779/udp    pharmasoft
//#                           Ola Strandberg <Ola.Strandberg&pharmasoft.se>
//dpkeyserv       1780/tcp    dpkeyserv
//dpkeyserv       1780/udp    dpkeyserv
//#                           Yasunari Gon Yamasita <yamasita&omronsoft.co.jp>
//answersoft-lm   1781/tcp    answersoft-lm
//answersoft-lm   1781/udp    answersoft-lm 
//#                           James A. Brewster <jimbrew&answersoft.com>
//hp-hcip         1782/tcp    hp-hcip
//hp-hcip         1782/udp    hp-hcip
//#                           Allen Baker <abaker&boi.hp.com>
//#               1783        Decomissioned Port 04/14/00, ms    
//#                           <naonao&kikaku.mmp.fujitsu.co.jp> 
//finle-lm        1784/tcp    Finle License Manager
//finle-lm        1784/udp    Finle License Manager
//#                           Dongling Wang <dongling&finle.com>
//windlm          1785/tcp    Wind River Systems License Manager
//windlm          1785/udp    Wind River Systems License Manager
//#                           Will Dere <will&wrs.com>
//funk-logger     1786/tcp    funk-logger
//funk-logger     1786/udp    funk-logger
//funk-license    1787/tcp    funk-license
//funk-license    1787/udp    funk-license
//#                           Cimarron Boozer <cboozer&funk.com>
//#                           Eric Wilde <eric&funk.com>
//psmond          1788/tcp    psmond
//psmond          1788/udp    psmond
//#                           Will Golson <golson&fc.hp.com>
//hello           1789/tcp    hello
//hello           1789/udp    hello
//#                           D. J. Bernstein <djb&koobera.math.uic.edu>       
//nmsp            1790/tcp    Narrative Media Streaming Protocol
//nmsp            1790/udp    Narrative Media Streaming Protocol
//#                           Paul Santinelli, Jr. <psantinelli&narrative.com>
//ea1             1791/tcp    EA1
//ea1             1791/udp    EA1
//#                           Kirk MacLean <kmaclean&ea.com>
//ibm-dt-2        1792/tcp    ibm-dt-2
//ibm-dt-2        1792/udp    ibm-dt-2
//#                           Sam Borman <sam_borman&uk.ibm.com>
//rsc-robot       1793/tcp    rsc-robot
//rsc-robot       1793/udp    rsc-robot
//#                           Andrew Jay Schneider <ajs&relsoft.com>
//cera-bcm        1794/tcp    cera-bcm
//cera-bcm        1794/udp    cera-bcm
//#                           Leo Moesgaard <leo_moesgaard&dk.ibm.com>
//dpi-proxy       1795/tcp    dpi-proxy
//dpi-proxy       1795/udp    dpi-proxy
//#                           Charles Gordon <cgordon&digprod.com>
//vocaltec-admin  1796/tcp    Vocaltec Server Administration
//vocaltec-admin  1796/udp    Vocaltec Server Administration
//#                           Scott Petrack <Scott_Petrack&vocaltec.com>
//uma             1797/tcp    UMA 
//uma             1797/udp    UMA
//#                           Martin Kirk <m.kirk&opengroup.org>
//etp             1798/tcp    Event Transfer Protocol
//etp             1798/udp    Event Transfer Protocol
//#                           Mike Wray <mjw&hplb.hpl.hp.com>
//netrisk		1799/tcp    NETRISK
//netrisk		1799/udp    NETRISK
//#			    Kevin Green <Kevin_Green&tds.com>
//ansys-lm	1800/tcp    ANSYS-License manager
//ansys-lm	1800/udp    ANSYS-License manager
//#			    Suzanne Lorrin <sml&ansyspo.ansys.com>
//msmq		1801/tcp    Microsoft Message Que
//msmq		1801/udp    Microsoft Message Que
//#			    Amnon Horowitz <amnonh&MICROSOFT.com>
//concomp1	1802/tcp    ConComp1
//concomp1	1802/udp    ConComp1
//#			    Ed Vincent <@edv&concomp.com>
//hp-hcip-gwy	1803/tcp    HP-HCIP-GWY
//hp-hcip-gwy	1803/udp    HP-HCIP-GWY
//#			    Allen Baker <abaker&boi.hp.com>
//enl		1804/tcp    ENL
//enl		1804/udp    ENL
//#			    Brian Olson <briolson&pacbell.net>
//enl-name	1805/tcp    ENL-Name
//enl-name	1805/udp    ENL-Name
//#			    Brian Olson <briolson&pacbell.net>
//musiconline	1806/tcp    Musiconline
//musiconline	1806/udp    Musiconline
//#			    Craig Weeks <cweeks&syspace.co.uk>
//fhsp		1807/tcp    Fujitsu Hot Standby Protocol
//fhsp		1807/udp    Fujitsu Hot Standby Protocol
//#			    Eiki Iwata (eiki&nd.net.fujitsu.co.jp>
//oracle-vp2	1808/tcp    Oracle-VP2
//oracle-vp2	1808/udp    Oracle-VP2
//#                           Craig Fowler <cfowler&us.oracle.com>
//oracle-vp1      1809/tcp    Oracle-VP1
//oracle-vp1	1809/udp    Oracle-VP1
//#                           Craig Fowler <cfowler&us.oracle.com>
//jerand-lm       1810/tcp    Jerand License Manager
//jerand-lm	1810/udp    Jerand License Manager
//#                           Robert Monat <jerand&jerand.com>
//scientia-sdb    1811/tcp    Scientia-SDB
//scientia-sdb	1811/udp    Scientia-SDB
//#                           SYSTEMS MANAGER <systems-manager&scientia.com>
//radius          1812/tcp    RADIUS
//radius          1812/udp    RADIUS
//#                           [RFC2865]
//radius-acct     1813/tcp    RADIUS Accounting
//radius-acct     1813/udp    RADIUS Accounting
//#                           [RFC2866]
//tdp-suite       1814/tcp    TDP Suite
//tdp-suite       1814/udp    TDP Suite
//#                           Rob Lockhart <rob.lockhart&mot.com>
//mmpft		1815/tcp    MMPFT
//mmpft		1815/udp    MMPFT
//#			    Ralf Muckenhirn <FAX: 49-7622-398200>
//#                           <Phone: 49-7622-3980>
//harp		1816/tcp    HARP
//harp		1816/udp    HARP
//#			    Bjorn Chambless <bjorn&cs.pdx.edu>
//rkb-oscs	1817/tcp    RKB-OSCS
//rkb-oscs	1817/udp    RKB-OSCS
//#			    Robert Kevin Breton <BOBBRETON&HOTMAIL.COM>
//etftp           1818/tcp    Enhanced Trivial File Transfer Protocol
//etftp           1818/udp    Enhanced Trivial File Transfer Protocol
//#                           William Polites <wpolites&mitre.org>
//plato-lm        1819/tcp    Plato License Manager
//plato-lm        1819/udp    Plato License Manager
//#                           Mark Morris <mim&ermuk.com>
//mcagent         1820/tcp    mcagent
//mcagent         1820/udp    mcagent
//#                           Ryoichi Shinohara <shinohara&VNET.IBM.COM>
//donnyworld      1821/tcp    donnyworld
//donnyworld      1821/udp    donnyworld
//#                           Don Oliver <don&donnyworld.com>
//es-elmd         1822/tcp    es-elmd
//es-elmd         1822/udp    es-elmd
//#                           David Duncan <dduncan&es.com>
//unisys-lm       1823/tcp    Unisys Natural Language License Manager
//unisys-lm       1823/udp    Unisys Natural Language License Manager
//#                           Raymond A. Diedrichs <rayd&slu.tr.unisys.com>
//metrics-pas     1824/tcp    metrics-pas
//metrics-pas     1824/udp    metrics-pas
//#                           Tom Haapanen <tomh&metrics.com>
//direcpc-video	1825/tcp    DirecPC Video
//direcpc-video	1825/udp    DirecPC Video
//#			    Chris Kerrigan <ckerrigan&hns.com>    
//ardt		1826/tcp    ARDT
//ardt		1826/udp    ARDT
//#			    Mike Goddard <mike.goddard&ardent.com.au>
//asi		1827/tcp    ASI 
//asi		1827/udp    ASI 
//#			    Bob Tournoux <bob.tournoux&usiny.mail.abb.com>
//itm-mcell-u	1828/tcp    itm-mcell-u
//itm-mcell-u	1828/udp    itm-mcell-u
//#			    Portnoy Boxman <portnoy_boxman&bmc.com>
//optika-emedia	1829/tcp    Optika eMedia 
//optika-emedia	1829/udp    Optika eMedia 
//#			    Daryle DeBalski <ddebalski&optika.com>
//net8-cman	1830/tcp    Oracle Net8 CMan Admin
//net8-cman	1830/udp    Oracle Net8 CMan Admin
//#			    Shuvayu Kanjilal
//myrtle		1831/tcp    Myrtle
//myrtle		1831/udp    Myrtle
//#			    Ron Achin <RAchin&genscan.com>
//tht-treasure	1832/tcp    ThoughtTreasure
//tht-treasure	1832/udp    ThoughtTreasure
//#			    Erik Mueller <erik&signiform.com>
//udpradio	1833/tcp    udpradio
//udpradio	1833/udp    udpradio
//#			    Guus Sliepen <guus&warande3094.warande.uu.nl>
//ardusuni	1834/tcp    ARDUS Unicast
//ardusuni	1834/udp    ARDUS Unicast
//ardusmul	1835/tcp    ARDUS Multicast
//ardusmul	1835/udp    ARDUS Multicast
//#			    Toshikatsu Ito <ito-t&pfu.co.jp>
//ste-smsc	1836/tcp    ste-smsc
//ste-smsc	1836/udp    ste-smsc
//#			    Tom Snauwaert <tom.snauwaert&st-electronics.be>
//csoft1		1837/tcp    csoft1
//csoft1		1837/udp    csoft1
//#			    John Coll <john&csoft.co.uk> 
//talnet		1838/tcp    TALNET
//talnet		1838/udp    TALNET
//#			    Aaron Lav <aaron&taltrade.com>
//netopia-vo1	1839/tcp    netopia-vo1
//netopia-vo1	1839/udp    netopia-vo1
//netopia-vo2	1840/tcp    netopia-vo2
//netopia-vo2	1840/udp    netopia-vo2
//netopia-vo3	1841/tcp    netopia-vo3
//netopia-vo3	1841/udp    netopia-vo3
//netopia-vo4	1842/tcp    netopia-vo4
//netopia-vo4	1842/udp    netopia-vo4
//netopia-vo5	1843/tcp    netopia-vo5
//netopia-vo5	1843/udp    netopia-vo5
//#			    Marc Epard <marc&netopia.com>
//direcpc-dll	1844/tcp    DirecPC-DLL
//direcpc-dll	1844/udp    DirecPC-DLL
//#			    Chris Kerrigan <ckerrigan&hns.com>
//altalink        1845/tcp    altalink
//altalink        1845/udp    altalink
//#                           Alberto Raydan <alberto&altasol.com>
//tunstall-pnc    1846/tcp    Tunstall PNC
//tunstall-pnc    1846/udp    Tunstall PNC
//#                           Robert M. Moore <r_moore&tunstall.co.uk>
//slp-notify      1847/tcp    SLP Notification
//slp-notify      1847/udp    SLP Notification
//#                           James Kempf <james.kempf&sun.com> 
//fjdocdist       1848/tcp    fjdocdist
//fjdocdist       1848/udp    fjdocdist
//#                           Yuichi Ohiwa <y-ohiwa&ael.fujitsu.co.jp>
//alpha-sms       1849/tcp    ALPHA-SMS
//alpha-sms       1849/udp    ALPHA-SMS
//#                           Benjamin Grimm <bg&webnetix.de> 
//gsi		1850/tcp    GSI
//gsi		1850/udp    GSI
//#			    William Mullaney <mullanwi&usa.net>
//ctcd		1851/tcp    ctcd
//ctcd		1851/udp    ctcd
//#			    John Ryan <john&cybertrace.com>
//virtual-time    1852/tcp    Virtual Time
//virtual-time    1852/udp    Virtual Time
//#                           Angie S. Morner <webmaster&dsbcpas.com>
//vids-avtp       1853/tcp    VIDS-AVTP
//vids-avtp       1853/udp    VIDS-AVTP
//#                           Sascha Kuemmel <kuemmel&vidsoft.de>
//buddy-draw      1854/tcp    Buddy Draw
//buddy-draw      1854/udp    Buddy Draw
//#                           Marvin Shin <president&medialingo.com>  
//fiorano-rtrsvc  1855/tcp    Fiorano RtrSvc
//fiorano-rtrsvc  1855/udp    Fiorano RtrSvc
//fiorano-msgsvc  1856/tcp    Fiorano MsgSvc
//fiorano-msgsvc  1856/udp    Fiorano MsgSvc
//#                           Albert Holt <alberth&fiorano.com> 
//datacaptor      1857/tcp    DataCaptor
//datacaptor      1857/udp    DataCaptor
//#                           Steven M. Forrester <StevenF&CapsuleTech.com>
//privateark      1858/tcp    PrivateArk
//privateark      1858/udp    PrivateArk
//#                           Ronen Zoran <ronenz&cyber-ark.com>  
//gammafetchsvr   1859/tcp    Gamma Fetcher Server
//gammafetchsvr   1859/udp    Gamma Fetcher Server
//#                           Cnaan Aviv <cnaan&gammasite.com>     
//sunscalar-svc	1860/tcp    SunSCALAR Services
//sunscalar-svc	1860/udp    SunSCALAR Services
//#			    Sanjay Radia <srradia&kasumbi.Eng.Sun.COM>
//lecroy-vicp	1861/tcp    LeCroy VICP
//lecroy-vicp	1861/udp    LeCroy VICP
//#			    Anthony Cake <anthonyrc&lecroy.com>
//techra-server	1862/tcp    techra-server
//techra-server	1862/udp    techra-server
//#			    Roy Lyseng <roy.lyseng&maxware.no>
//msnp		1863/tcp    MSNP
//msnp		1863/udp    MSNP
//#			    William Lai <wlai&microsoft.com>
//paradym-31port	1864/tcp    Paradym 31 Port
//paradym-31port	1864/udp    Paradym 31 Port
//#			    David Wooden <dwooden&wizdom.com>
//entp		1865/tcp    ENTP
//entp		1865/udp    ENTP
//#			    Seiko Epson <Ishida.Hitoshi&exc.epson.co.jp>
//swrmi           1866/tcp    swrmi
//swrmi           1866/udp    swrmi
//#                           Jun Yoshii <yoshii&ael.fujitsu.co.jp> 
//udrive          1867/tcp    UDRIVE
//udrive          1867/udp    UDRIVE
//#                           Robby Walker <webmaster&cd-lab.com>
//viziblebrowser  1868/tcp    VizibleBrowser
//viziblebrowser  1868/udp    VizibleBrowser
//#                           Jimmy Talbot <jtalbot&vizible.com> 
//transact        1869/tcp    TransAct
//transact        1869/udp    TransAct
//#                           TransAct Futures Development Team <1869info&transactfutures.com> 
//sunscalar-dns   1870/tcp    SunSCALAR DNS Service
//sunscalar-dns	1870/udp    SunSCALAR DNS Service
//#                           Sanjay Radia <srradia&kasumbi.Eng.Sun.COM>
//canocentral0	1871/tcp    Cano Central 0
//canocentral0	1871/udp    Cano Central 0
//canocentral1	1872/tcp    Cano Central 1
//canocentral1	1872/udp    Cano Central 1
//#			    Mark McNamara <markm&research.canon.com.au>
//fjmpjps		1873/tcp    Fjmpjps
//fjmpjps		1873/udp    Fjmpjps
//fjswapsnp	1874/tcp    Fjswapsnp
//fjswapsnp	1874/udp    Fjswapsnp
//#			    Y. Ohiwa <y-ohiwa&ael.fujitsu.co.jp>
//westell-stats   1875/tcp    westell stats
//westell-stats   1875/udp    westell stats
//#                           Thomas McCabe <tmcca&westell.com>
//ewcappsrv       1876/tcp    ewcappsrv
//ewcappsrv       1876/udp    ewcappsrv
//#                           Howard Yin <howard.yin&ericsson.com>
//hp-webqosdb     1877/tcp    hp-webqosdb
//hp-webqosdb     1877/udp    hp-webqosdb
//#                           Kim Scott <kims&cup.hp.com>
//drmsmc          1878/tcp    drmsmc
//drmsmc          1878/udp    drmsmc
//#                           Katsuhiko Abe <kabe&hst.fujitsu.co.jp>
//nettgain-nms    1879/tcp    NettGain NMS
//nettgain-nms    1879/udp    NettGain NMS
//#                           Dr. Yair Shapira <yair&flashnetworks.com>
//vsat-control    1880/tcp    Gilat VSAT Control
//vsat-control    1880/udp    Gilat VSAT Control
//#                           Yariv Kaplan <yarivk&gilat.com> 
//ibm-mqseries2	1881/tcp    IBM WebSphere MQ Everyplace
//ibm-mqseries2	1881/udp    IBM WebSphere MQ Everyplace
//#                           Jane Porter <janeporter&uk.ibm.com>
//ecsqdmn         1882/tcp    CA eTrust Common Services
//ecsqdmn         1882/udp    CA eTrust Common Services
//#                           Paul Wissmiller <Paul.Wissmiller&ca.com>
//ibm-mqisdp      1883/tcp    IBM MQSeries SCADA
//ibm-mqisdp      1883/udp    IBM MQSeries SCADA
//#                           Andy Stanford-Clark <andysc&uk.ibm.com>
//idmaps          1884/tcp    Internet Distance Map Svc
//idmaps          1884/udp    Internet Distance Map Svc
//#                           Sugih Jamim <jamin&eecs.umich.edu> 
//vrtstrapserver  1885/tcp    Veritas Trap Server
//vrtstrapserver  1885/udp    Veritas Trap Server
//#                           Russell Thrasher <rthrashe&veritas.com>
//leoip           1886/tcp    Leonardo over IP
//leoip           1886/udp    Leonardo over IP
//#                           Dietmar Finkler <d.finkler&hermstedt.de>
//filex-lport     1887/tcp    FileX Listening Port
//filex-lport     1887/udp    FileX Listening Port
//#                           Megan Woods <meganwoods&datafast.net.au>
//ncconfig        1888/tcp    NC Config Port
//ncconfig        1888/udp    NC Config Port
//#                           Simon Parker <simon.j.parker&philips.com>
//unify-adapter   1889/tcp    Unify Web Adapter Service
//unify-adapter   1889/udp    Unify Web Adapter Service
//#                           Duane Gibson <ianaportmaster&unify.com>
//wilkenlistener  1890/tcp    wilkenListener
//wilkenlistener  1890/udp    wilkenListener
//#                           Wilken GmbH <fy&wilken.de> 
//childkey-notif	1891/tcp    ChildKey Notification
//childkey-notif  1891/udp    ChildKey Notification
//childkey-ctrl   1892/tcp    ChildKey Control
//childkey-ctrl   1892/udp    ChildKey Control 	
//#                           Ivan Berardinelli <ivan&gestweb.com>
//elad            1893/tcp    ELAD Protocol
//elad            1893/udp    ELAD Protocol
//#                           Franco Milan <franco&eladit.com>
//o2server-port	1894/tcp    O2Server Port
//o2server-port   1894/udp    O2Server Port
//#                           Tim Howard <timothygh&hotmail.com> 	
//#####  Microsoft (unoffically) using 1895     #####  
//b-novative-ls   1896/tcp    b-novative license server
//b-novative-ls   1896/udp    b-novative license server
//#                           Matthias Riese <Matthias.Riese&b-novative.de>
//metaagent       1897/tcp    MetaAgent
//metaagent       1897/udp    MetaAgent
//#                           Marie-France Dubreuil <Marie-France.Dubreuil&evidian.com> 
//cymtec-port	1898/tcp    Cymtec secure management
//cymtec-port     1898/udp    Cymtec secure management
//#                           Michael Mester <mmester&cymtec.com>
//mc2studios	1899/tcp    MC2Studios
//mc2studios	1899/udp    MC2Studios
//#			    Michael Coon <michael&thecube.com>	
//ssdp		1900/tcp    SSDP
//ssdp		1900/udp    SSDP
//#			    UPnP Forum <upnpadmin&forum.upnp.org>
//fjicl-tep-a     1901/tcp    Fujitsu ICL Terminal Emulator Program A
//fjicl-tep-a     1901/udp    Fujitsu ICL Terminal Emulator Program A
//#                           Bob Lyon <bl&oasis.icl.co.uk>
//fjicl-tep-b     1902/tcp    Fujitsu ICL Terminal Emulator Program B
//fjicl-tep-b     1902/udp    Fujitsu ICL Terminal Emulator Program B
//#                           Bob Lyon <bl&oasis.icl.co.uk>
//linkname        1903/tcp    Local Link Name Resolution
//linkname        1903/udp    Local Link Name Resolution
//#                           Dan Harrington <dth&lucent.com>
//fjicl-tep-c     1904/tcp    Fujitsu ICL Terminal Emulator Program C
//fjicl-tep-c     1904/udp    Fujitsu ICL Terminal Emulator Program C
//#                           Bob Lyon <bl&oasis.icl.co.uk>
//sugp   		1905/tcp    Secure UP.Link Gateway Protocol
//sugp            1905/udp    Secure UP.Link Gateway Protocol
//#			    Peter King <king&uplanet.com>
//tpmd		1906/tcp    TPortMapperReq
//tpmd		1906/udp    TPortMapperReq
//# 			    Sheila Devins <sheila_devins&VNET.IBM.COM>
//intrastar	1907/tcp    IntraSTAR
//intrastar	1907/udp    IntraSTAR
//#			    Peter Schoenberger <ps&teles.de>
//dawn		1908/tcp    Dawn
//dawn		1908/udp    Dawn
//#			    Michael Crawford <michaelc&travsoft.com>
//global-wlink	1909/tcp    Global World Link
//global-wlink	1909/udp    Global World Link
//#			    Nicholas Davies <N.Davies&globalcomm.co.uk>
//ultrabac        1910/tcp    UltraBac Software communications port
//ultrabac        1910/udp    UltraBac Software communications port
//#                           Paul Bunn <iana&ultrabac.com>	
//mtp             1911/tcp    Starlight Networks Multimedia Transport Protocol
//mtp             1911/udp    Starlight Networks Multimedia Transport Protocol
//#                           Bruce Lieberman <brucel&iserver.starlight.com>
//rhp-iibp	1912/tcp    rhp-iibp	
//rhp-iibp	1912/udp    rhp-iibp	
//#			    George Nachman
//#                           Tom Lake <tlake&m-ware.com>
//armadp          1913/tcp    armadp
//armadp          1913/udp    armadp
//#                           Kevin Welton <Kevin.Welton&armltd.co.uk>
//elm-momentum    1914/tcp    Elm-Momentum
//elm-momentum    1914/udp    Elm-Momentum
//#                           Willie Wu <willie&mds.com>
//facelink        1915/tcp    FACELINK
//facelink        1915/udp    FACELINK
//#                           J.H. Hermans <j.h.hermans&hiscom.nl>
//persona         1916/tcp    Persoft Persona
//persona         1916/udp    Persoft Persona
//#                           Tom Spidell <spidell&persoft.com>
//noagent		1917/tcp    nOAgent
//noagent		1917/udp    nOAgent
//#			    Martin Bestmann <martin&datawatch.de>
//can-nds   	1918/tcp    IBM Tivole Directory Service - NDS    
//can-nds		1918/udp    IBM Tivole Directory Service - NDS
//can-dch		1919/tcp    IBM Tivoli Directory Service - DCH
//can-dch   	1919/udp    IBM Tivoli Directory Service - DCH
//can-ferret	1920/tcp    IBM Tivoli Directory Service - FERRET
//can-ferret	1920/udp    IBM Tivoli Directory Service - FERRET
//#			    nic catrambone <ncatramb&us.ibm.com>
//noadmin		1921/tcp    NoAdmin
//noadmin		1921/udp    NoAdmin
//#			    Martin Bestmann <martin&datawatch.de>
//tapestry	1922/tcp    Tapestry	
//tapestry	1922/udp    Tapestry	
//#			    Ken Oliver <koliver02&yahoo.com>
//spice		1923/tcp    SPICE
//spice		1923/udp    SPICE
//#			    Nicholas Chua <nick&sendit.se>
//xiip		1924/tcp    XIIP
//xiip		1924/udp    XIIP
//#			    Alain Robert <Alain.Robert&HMRinc.com>	
//discovery-port  1925/tcp    Surrogate Discovery Port
//discovery-port  1925/udp    Surrogate Discovery Port
//#                           Keith Thompson <keith.thompson&sun.com>
//egs             1926/tcp    Evolution Game Server
//egs             1926/udp    Evolution Game Server
//#                           Simon Butcher <simonb&alien.net.au>
//videte-cipc     1927/tcp    Videte CIPC Port
//videte-cipc     1927/udp    Videte CIPC Port
//#                           Videte IT <info&videte.com>
//emsd-port       1928/tcp    Expnd Maui Srvr Dscovr
//emsd-port       1928/udp    Expnd Maui Srvr Dscovr
//#                           Edo Yahav <standards&expand.com>
//bandwiz-system  1929/tcp    Bandwiz System - Server
//bandwiz-system  1929/udp    Bandwiz System - Server
//#                           Joseph Weihs <yossi&bandwiz.com>
//driveappserver	1930/tcp    Drive AppServer
//driveappserver	1930/udp    Drive AppServer
//#			    Andrew Johnson
//#			    <andrew.johnson&bliss-support.demon.co.uk>
//amdsched	1931/tcp    AMD SCHED
//amdsched	1931/udp    AMD SCHED
//#			    Michael Walsh <mww&warwick.net>
//ctt-broker      1932/tcp    CTT Broker
//ctt-broker      1932/udp    CTT Broker
//#                           Jens Edlund <edlund&speech.kth.se>
//xmapi		1933/tcp    IBM LM MT Agent
//xmapi           1933/udp    IBM LM MT Agent
//xaapi           1934/tcp    IBM LM Appl Agent
//xaapi           1934/udp    IBM LM Appl Agent
//#                           Helga Wolin <hwolin&us.ibm.com>
//macromedia-fcs  1935/tcp    Macromedia Flash Communications Server MX
//macromedia-fcs  1935/udp    Macromedia Flash Communications server MX
//#                           Pritham Shetty <pritham&macromedia.com> 
//jetcmeserver    1936/tcp    JetCmeServer Server Port
//jetcmeserver    1936/udp    JetCmeServer Server Port
//jwserver        1937/tcp    JetVWay Server Port
//jwserver        1937/udp    JetVWay Server Port
//jwclient        1938/tcp    JetVWay Client Port
//jwclient        1938/udp    JetVWay Client Port
//jvserver        1939/tcp    JetVision Server Port
//jvserver        1939/udp    JetVision Server Port
//jvclient        1940/tcp    JetVision Client Port
//jvclient        1940/udp    JetVision Client Port
//#                           Stephen Tsun <stsun&jetstream.com>
//dic-aida        1941/tcp    DIC-Aida
//dic-aida        1941/udp    DIC-Aida
//#                           Frans S.C. Witte <fscwitte&dicgroep.nl> 
//res             1942/tcp    Real Enterprise Service
//res             1942/udp    Real Enterprise Service
//#                           Bob Janssen <bob&res.nl>
//beeyond-media   1943/tcp    Beeyond Media
//beeyond-media   1943/udp    Beeyond Media
//#                           Bob Deblier <bob&virtualunlimited.com>
//close-combat    1944/tcp    close-combat
//close-combat    1944/udp    close-combat
//#                           David Hua <davhua&microsoft.com>
//dialogic-elmd   1945/tcp    dialogic-elmd
//dialogic-elmd   1945/udp    dialogic-elmd
//#                           Roger Kay <r.kay&nz.dialogic.com>
//tekpls          1946/tcp    tekpls
//tekpls          1946/udp    tekpls
//#                           Brian Abramson <brianab&vnd.tek.com>
//hlserver        1947/tcp    hlserver
//hlserver        1947/udp    hlserver
//#                           Michael Zzunke <mzunke&fast-ag.de>
//eye2eye         1948/tcp    eye2eye
//eye2eye         1948/udp    eye2eye
//#                           Trevor Bell <Trevor&iguana.iosoftware.com>
//ismaeasdaqlive  1949/tcp    ISMA Easdaq Live
//ismaeasdaqlive  1949/udp    ISMA Easdaq Live
//ismaeasdaqtest  1950/tcp    ISMA Easdaq Test
//ismaeasdaqtest  1950/udp    ISMA Easdaq Test
//#                           Stephen Dunne <sdun&isma.co.uk>
//bcs-lmserver    1951/tcp    bcs-lmserver
//bcs-lmserver    1951/udp    bcs-lmserver
//#                           Andy Warner <andyw&knoware.nl>
//mpnjsc		1952/tcp    mpnjsc
//mpnjsc		1952/udp    mpnjsc
//#			    Takenori Miyahara <miyahara&pfu.co.jp>	
//rapidbase	1953/tcp    Rapid Base
//rapidbase	1953/udp    Rapid Base
//#			    Antoni Wolski <antoni.wolski&vtt.fi>
//abr-api		1954/tcp    ABR-API (diskbridge) 
//abr-api		1954/udp    ABR-API (diskbridge)
//abr-secure      1955/tcp    ABR-Secure Data (diskbridge)
//abr-secure      1955/udp    ABR-Secure Data (diskbridge)
//#			    Graham Wooden <graham&g-rock.net> 
//vrtl-vmf-ds     1956/tcp    Vertel VMF DS
//vrtl-vmf-ds     1956/udp    Vertel VMF DS
//#                           Alan Akahoshi <alan-akahoshi&vertel.com>
//unix-status     1957/tcp    unix-status
//unix-status     1957/udp    unix-status
//#                           Thomas Erskine <erskine&sourceworks.com>
//dxadmind        1958/tcp    CA Administration Daemon
//dxadmind        1958/udp    CA Administration Daemon
//#                           John Birrell <birjo99&cai.com> 
//simp-all        1959/tcp    SIMP Channel
//simp-all        1959/udp    SIMP Channel
//#                           Tim Hunnewell <thunnewell&pinna.com> 
//nasmanager      1960/tcp    Merit DAC NASmanager
//nasmanager      1960/udp    Merit DAC NASmanager
//#                           Richard S. Conto <rsc&merit.edu>
//bts-appserver	1961/tcp   BTS APPSERVER
//bts-appserver	1961/udp   BTS APPSERVER
//#			   Carl Obsorn <carl_osborn&sabre.com>
//biap-mp         1962/tcp   BIAP-MP
//biap-mp         1962/udp   BIAP-MP
//#                          Louis Slothouber <lpslot&biap.com>
//webmachine      1963/tcp   WebMachine
//webmachine      1963/udp   WebMachine
//#                          Tim Jowers <Tim.Jowers&ColumbiaSC.NCR.com>
//solid-e-engine	1964/tcp   SOLID E ENGINE
//solid-e-engine	1964/udp   SOLID E ENGINE
//#			   Ari Valtanen <ari.valtanen&solidtech.com>
//tivoli-npm	1965/tcp   Tivoli NPM
//tivoli-npm	1965/udp   Tivoli NPM
//#			   Ivana Cuozzo <Ivana.Cuozzo&tivoli.com>
//slush		1966/tcp   Slush
//slush		1966/udp   Slush
//#			   Damien Miller <damien&ibs.com.au>
//sns-quote	1967/tcp   SNS Quote
//sns-quote	1967/udp   SNS Quote
//#			   Robert Ellman <rellman&calicotech.com>
//lipsinc         1968/tcp   LIPSinc
//lipsinc         1968/udp   LIPSinc
//lipsinc1        1969/tcp   LIPSinc 1
//lipsinc1        1969/udp   LIPSinc 1
//#                          Robert Armington <rarmington&lipsinc.com> 
//netop-rc        1970/tcp   NetOp Remote Control
//netop-rc        1970/udp   NetOp Remote Control
//netop-school    1971/tcp   NetOp School
//netop-school    1971/udp   NetOp School
//#                          NetOp Technical Support <support&danware.dk>
//intersys-cache	1972/tcp   Cache
//intersys-cache	1972/udp   Cache
//#                          Mark Hanson <markh&intersys.com>
//dlsrap          1973/tcp   Data Link Switching Remote Access Protocol
//dlsrap          1973/udp   Data Link Switching Remote Access Protocol
//#                          Steve T. Chiang <schiang&cisco.com>
//drp             1974/tcp   DRP
//drp             1974/udp   DRP
//#                          Richard Alan Johnson <raj&cisco.com>
//tcoflashagent	1975/tcp   TCO Flash Agent
//tcoflashagent	1975/udp   TCO Flash Agent
//tcoregagent     1976/tcp   TCO Reg Agent 
//tcoregagent     1976/udp   TCO Reg Agent 
//tcoaddressbook	1977/tcp   TCO Address Book
//tcoaddressbook	1977/udp   TCO Address Book
//#                          Allan Panitch <allanp&tcosoft.com>
//unisql          1978/tcp   UniSQL
//unisql          1978/udp   UniSQL
//unisql-java     1979/tcp   UniSQL Java
//unisql-java     1979/udp   UniSQL Java
//#                          Keith Yarbrough <kyarbro&windtraveller.com>
//pearldoc-xact   1980/tcp   PearlDoc XACT
//pearldoc-xact   1980/udp   PearlDoc XACT
//#                          Chris Vertonghen <chrisv&pearldoc.com>
//p2pq            1981/tcp   p2pQ
//p2pq            1981/udp   p2pQ
//#                          Warren Alexander <warren&chameleon-creative.co.uk>
//estamp          1982/tcp   Evidentiary Timestamp
//estamp          1982/udp   Evidentiary Timestamp
//#                          Todd Glassey <todd.glassey&att.net>
//lhtp            1983/tcp   Loophole Test Protocol
//lhtp            1983/udp   Loophole Test Protocol
//#                          Kade Hansson <kade_fh&postoffice.utas.edu.au>
//bb              1984/tcp   BB
//bb              1984/udp   BB
//#                          Sean MacGuire <sean&maclawran.ca>
//hsrp            1985/tcp   Hot Standby Router Protocol
//hsrp            1985/udp   Hot Standby Router Protocol
//#                          [RFC2281]
//licensedaemon   1986/tcp   cisco license management
//licensedaemon   1986/udp   cisco license management
//tr-rsrb-p1      1987/tcp   cisco RSRB Priority 1 port
//tr-rsrb-p1      1987/udp   cisco RSRB Priority 1 port
//tr-rsrb-p2      1988/tcp   cisco RSRB Priority 2 port
//tr-rsrb-p2      1988/udp   cisco RSRB Priority 2 port
//tr-rsrb-p3      1989/tcp   cisco RSRB Priority 3 port
//tr-rsrb-p3      1989/udp   cisco RSRB Priority 3 port
//# The following entry records an unassigned but widespread use
//mshnet          1989/tcp   MHSnet system
//mshnet          1989/udp   MHSnet system
//#                          Bob Kummerfeld <bob&sarad.cs.su.oz.au>
//stun-p1         1990/tcp   cisco STUN Priority 1 port
//stun-p1         1990/udp   cisco STUN Priority 1 port
//stun-p2         1991/tcp   cisco STUN Priority 2 port
//stun-p2         1991/udp   cisco STUN Priority 2 port
//stun-p3         1992/tcp   cisco STUN Priority 3 port
//stun-p3         1992/udp   cisco STUN Priority 3 port
//# The following entry records an unassigned but widespread use
//ipsendmsg       1992/tcp   IPsendmsg
//ipsendmsg       1992/udp   IPsendmsg
//#                          Bob Kummerfeld <bob&sarad.cs.su.oz.au>
//snmp-tcp-port   1993/tcp   cisco SNMP TCP port
//snmp-tcp-port   1993/udp   cisco SNMP TCP port
//stun-port       1994/tcp   cisco serial tunnel port
//stun-port       1994/udp   cisco serial tunnel port
//perf-port       1995/tcp   cisco perf port
//perf-port       1995/udp   cisco perf port
//tr-rsrb-port    1996/tcp   cisco Remote SRB port
//tr-rsrb-port    1996/udp   cisco Remote SRB port
//gdp-port        1997/tcp   cisco Gateway Discovery Protocol
//gdp-port        1997/udp   cisco Gateway Discovery Protocol
//x25-svc-port    1998/tcp   cisco X.25 service (XOT)
//x25-svc-port    1998/udp   cisco X.25 service (XOT)
//tcp-id-port     1999/tcp   cisco identification port
//tcp-id-port     1999/udp   cisco identification port
//#
//cisco-sccp      2000/tcp   Cisco SCCP
//cisco-sccp      2000/udp   Cisco SCCp
//#                          Dan Wing <dwing&cisco.com> November 2003
//dc              2001/tcp
//wizard          2001/udp   curry
//globe           2002/tcp
//globe           2002/udp
//#
//brutus          2003/tcp   Brutus Server
//brutus          2003/udp   Brutus Server
//#                          Johannes Skov Frandsen <joe&42tools.com> 28 February 2008
//mailbox         2004/tcp
//emce            2004/udp   CCWS mm conf
//berknet         2005/tcp
//oracle          2005/udp
//invokator       2006/tcp
//raid-cd         2006/udp   raid
//dectalk         2007/tcp
//raid-am         2007/udp
//conf		2008/tcp
//terminaldb	2008/udp
//news		2009/tcp
//whosockami	2009/udp
//search		2010/tcp
//pipe_server	2010/udp
//raid-cc		2011/tcp   raid
//servserv	2011/udp
//ttyinfo		2012/tcp
//raid-ac		2012/udp
//raid-am		2013/tcp
//raid-cd		2013/udp
//troff		2014/tcp
//raid-sf		2014/udp
//cypress		2015/tcp
//raid-cs		2015/udp
//bootserver	2016/tcp
//bootserver	2016/udp
//cypress-stat	2017/tcp
//bootclient	2017/udp
//terminaldb	2018/tcp
//rellpack	2018/udp
//whosockami	2019/tcp
//about		2019/udp
//xinupageserver	2020/tcp
//xinupageserver	2020/udp
//servexec	2021/tcp
//xinuexpansion1	2021/udp
//down		2022/tcp
//xinuexpansion2	2022/udp
//xinuexpansion3	2023/tcp
//xinuexpansion3	2023/udp
//xinuexpansion4	2024/tcp
//xinuexpansion4	2024/udp
//ellpack		2025/tcp
//xribs		2025/udp
//scrabble	2026/tcp
//scrabble	2026/udp
//shadowserver	2027/tcp
//shadowserver	2027/udp
//submitserver	2028/tcp
//submitserver	2028/udp
//hsrpv6          2029/tcp   Hot Standby Router Protocol IPv6
//hsrpv6          2029/udp   Hot Standby Router Protocol IPv6
//#                          Ian Wilson <hsrp-info&cisco.com> November 2004
//device2		2030/tcp
//device2		2030/udp
//mobrien-chat    2031/tcp   mobrien-chat 
//mobrien-chat    2031/udp   mobrien-chat 
//#                          Mike O'Brien <mike&mobrien.com> November 2004
//blackboard      2032/tcp
//blackboard      2032/udp
//glogger		2033/tcp
//glogger		2033/udp
//scoremgr	2034/tcp
//scoremgr	2034/udp
//imsldoc		2035/tcp
//imsldoc		2035/udp
//#
//e-dpnet		2036/tcp   Ethernet WS DP network
//e-dpnet		2036/udp   Ethernet WS DP network
//#      		           Peter Kaever <kaever.peter&westfalia.com> August 2005
//applus          2037/tcp   APplus Application Server
//applus          2037/udp   APplus Application Server
//#                          Formerly was P2plus Application Server
//#                          Thomas Boerkel <tbo&ap-ag.com> 06 June 2008
//objectmanager	2038/tcp
//objectmanager	2038/udp
//#
//prizma		2039/tcp   Prizma Monitoring Service
//prizma		2039/udp   Prizma Monitoring Service
//#                          Dotan Ofek <dotan.ofek&prizmasoft.com> December 2005
//lam		2040/tcp
//lam		2040/udp
//interbase	2041/tcp
//interbase	2041/udp
//isis		2042/tcp   isis
//isis		2042/udp   isis
//isis-bcast	2043/tcp   isis-bcast
//isis-bcast	2043/udp   isis-bcast
//#                          Ken Chapman <kchapman&isis.com>
//rimsl		2044/tcp
//rimsl		2044/udp
//cdfunc		2045/tcp
//cdfunc		2045/udp
//sdfunc		2046/tcp
//sdfunc		2046/udp
//dls		2047/tcp
//dls		2047/udp
//dls-monitor	2048/tcp
//dls-monitor	2048/udp
//#                         <== NOTE Conflict on 2049 !
//shilp		2049/tcp
//shilp		2049/udp
//nfs             2049/tcp   Network File System - Sun Microsystems
//nfs             2049/udp   Network File System - Sun Microsystems
//#                          Brent Callaghan <brent&terra.eng.sun.com>
//nfs             2049/sctp  Network File System
//#                          [RFC-draft-ietf-nfsv4-rpc-netid-06.txt]
//av-emb-config   2050/tcp   Avaya EMB Config Port
//av-emb-config   2050/udp   Avaya EMB Config Port
//#                          John Yeager <johnyeager&avaya.com>
//epnsdp          2051/tcp   EPNSDP
//epnsdp          2051/udp   EPNSDP
//#                          Hiroyasu Ogata <Ogata.Hiroyasu&exc.epson.co.jp>
//clearvisn       2052/tcp   clearVisn Services Port
//clearvisn       2052/udp   clearVisn Services Port
//#                          Dave Lyons <dlyons&dnpg.com>    
//lot105-ds-upd   2053/tcp   Lot105 DSuper Updates
//lot105-ds-upd   2053/udp   Lot105 DSuper Updates
//#                          Piers Scannell <iana-form&lot105.com>
//weblogin        2054/tcp   Weblogin Port
//weblogin        2054/udp   Weblogin Port
//#                          Diego Saravia <dsa&unsa.edu.ar>
//iop             2055/tcp   Iliad-Odyssey Protocol
//iop             2055/udp   Iliad-Odyssey Protocol
//#                          Bruce Lueckenhoff <brucelu&cisco.com>
//omnisky         2056/tcp   OmniSky Port
//omnisky         2056/udp   OmniSky Port
//#	                   Oren Hurvitz <oren&omnisky.com>  
//rich-cp         2057/tcp   Rich Content Protocol
//rich-cp         2057/udp   Rich Content Protocol
//#                          Ronen Vainish <ronen&digitalfountain.com> 
//newwavesearch   2058/tcp   NewWaveSearchables RMI
//newwavesearch   2058/udp   NewWaveSearchables RMI
//#                          Thomas Kerkau <Thomas.Kerkau&io-software.com>  
//bmc-messaging   2059/tcp   BMC Messaging Service
//bmc-messaging   2059/udp   BMC Messaging Service
//#                          Portnoy Boxman <portnoy_boxman&bmc.com>
//teleniumdaemon  2060/tcp   Telenium Daemon IF
//teleniumdaemon  2060/udp   Telenium Daemon IF
//#                          Nick Woronuk <nick.woronuk&megasys.com>
//netmount        2061/tcp   NetMount
//netmount        2061/udp   NetMount
//#                          Alex Oberlander <alexo&netmount.com>
//icg-swp         2062/tcp   ICG SWP Port
//icg-swp         2062/udp   ICG SWP Port
//icg-bridge      2063/tcp   ICG Bridge Port
//icg-bridge      2063/udp   ICG Bridge Port
//icg-iprelay     2064/tcp   ICG IP Relay Port
//icg-iprelay     2064/udp   ICG IP Relay Port
//#                          Steve Quintana <steve&icgresearch.com> 
//dlsrpn          2065/tcp   Data Link Switch Read Port Number
//dlsrpn          2065/udp   Data Link Switch Read Port Number
//#                          Amir Peless <amirp&radware.co.il>
//aura		2066/tcp   AVM USB Remote Architecture
//aura		2066/udp   AVM USB Remote Architecture
//#			   Diego Friedel <d.friedel&avm.de> March 2006
//dlswpn          2067/tcp   Data Link Switch Write Port Number
//dlswpn          2067/udp   Data Link Switch Write Port Number
//#                          Amir Peless <amirp&radware.co.il>   
//avauthsrvprtcl  2068/tcp   Avocent AuthSrv Protocol
//avauthsrvprtcl  2068/udp   Avocent AuthSrv Protocol
//#                          Steven W. Clark <sclark&equinox.com>
//event-port      2069/tcp   HTTP Event Port
//event-port      2069/udp   HTTP Event Port
//#                          Larry Emlich <larry.emlich&compaq.com>
//ah-esp-encap    2070/tcp   AH and ESP Encapsulated in UDP packet
//ah-esp-encap    2070/udp   AH and ESP Encapsulated in UDP packet
//#                          Amy Weaver <aweaver&vpnet.com> 
//acp-port        2071/tcp   Axon Control Protocol
//acp-port        2071/udp   Axon Control Protocol
//#                          Christiaan Simons <christiaan.simons&axon.nl>
//msync           2072/tcp   GlobeCast mSync
//msync           2072/udp   GlobeCast mSync
//#                          Piers Scannell <piers&globecastne.com>
//gxs-data-port   2073/tcp   DataReel Database Socket
//gxs-data-port   2073/udp   DataReel Database Socket
//#                          Douglas M. Gaer <doug&datareel.com>
//vrtl-vmf-sa     2074/tcp   Vertel VMF SA
//vrtl-vmf-sa     2074/udp   Vertel VMF SA
//#                          Alan Akahoshi <alan-akahoshi&vertel.com>
//newlixengine    2075/tcp   Newlix ServerWare Engine
//newlixengine    2075/udp   Newlix ServerWare Engine
//newlixconfig    2076/tcp   Newlix JSPConfig
//newlixconfig    2076/udp   Newlix JSPConfig
//#                          Jean-Serge Gagnon <jean-serge.gagnon&newlix.com>
//tsrmagt		2077/tcp   Old Tivoli Storage Manager
//tsrmagt		2077/udp   Old Tivoli Storage Manager
//tpcsrvr		2078/tcp   IBM Total Productivity Center Server
//tpcsrvr		2078/udp   IBM Total Productivity Center Server
//#                          Justin R. Bendich <jbendich&us.ibm.com>
//idware-router   2079/tcp   IDWARE Router Port
//idware-router   2079/udp   IDWARE Router Port
//#                          Zdenek Kolba <zdenek.kolba&id-karta.cz>
//autodesk-nlm    2080/tcp   Autodesk NLM (FLEXlm)
//autodesk-nlm    2080/udp   Autodesk NLM (FLEXlm)
//#                          Greg Suppes <greg.suppes&autodesk.com>  
//kme-trap-port   2081/tcp   KME PRINTER TRAP PORT
//kme-trap-port   2081/udp   KME PRINTER TRAP PORT
//#                          Masakatsu Matsuo <masa&sdsft.kme.mei.co.jp>
//infowave        2082/tcp   Infowave Mobility Server
//infowave        2082/udp   Infowave Mobiltiy Server
//#                          Kaz Kylheku <kkylheku&infowave.com>
//radsec          2083/tcp   Secure Radius Service
//radsec          2083/udp   Secure Radius Service
//#                          Mike McCauley <mikem&open.com.au> May 2005
//sunclustergeo   2084/tcp   SunCluster Geographic
//sunclustergeo   2084/udp   SunCluster Geographic
//#                          Steve McKinty <steve.mckinty&sun.com> November 2005
//ada-cip         2085/tcp   ADA Control
//ada-cip         2085/udp   ADA Control
//#                          Eugene Frenkel <eugene&ada-usa.com> November 2005
//gnunet          2086/tcp   GNUnet
//gnunet          2086/udp   GNUnet
//#                          Christian Grothoff <grothoff&cs.purdue.edu> October 2002
//eli             2087/tcp   ELI - Event Logging Integration
//eli             2087/udp   ELI - Event Logging Integration
//#                          Maya Zimerman <mayaz&radware.co.il>  
//ip-blf          2088/tcp   IP Busy Lamp Field
//ip-blf          2088/udp   IP Busy Lamp Field
//#                          Jeffrey Szczepanski <jrs&inscitek.com> February 2005
//sep             2089/tcp   Security Encapsulation Protocol - SEP 
//sep             2089/udp   Security Encapsulation Protocol - SEP 
//#                          Maya Zimerman <mayaz&radware.co.il>
//lrp		2090/tcp   Load Report Protocol
//lrp		2090/udp   Load Report Protocol
//#			   Amir Peless <amirp&radware.co.il>
//prp		2091/tcp   PRP
//prp		2091/udp   PRP
//#			   Amir Peless <amirp&radware.co.il>
//descent3	2092/tcp   Descent 3
//descent3	2092/udp   Descent 3
//#			   Kevin Bentley <Kevin&outrage.com>
//nbx-cc		2093/tcp   NBX CC
//nbx-cc		2093/udp   NBX CC
//nbx-au		2094/tcp   NBX AU
//nbx-au		2094/udp   NBX AU
//nbx-ser		2095/tcp   NBX SER
//nbx-ser		2095/udp   NBX SER
//nbx-dir		2096/tcp   NBX DIR
//nbx-dir		2096/udp   NBX DIR
//#			   Henry Houh <hhouh&nbxcorp.com>
//jetformpreview	2097/tcp   Jet Form Preview
//jetformpreview	2097/udp   Jet Form Preview
//#			   Zygmunt Wiercioch <zyg&jetform.com>
//dialog-port	2098/tcp   Dialog Port
//dialog-port	2098/udp   Dialog Port
//#			   Joseph Mathew <mjoseph&dosa.cisco.com>
//h2250-annex-g	2099/tcp   H.225.0 Annex G
//h2250-annex-g	2099/udp   H.225.0 Annex G
//#			   Gur Kimchi <gur.kimchi&vocaltec.com>
//amiganetfs      2100/tcp   Amiga Network Filesystem
//amiganetfs      2100/udp   Amiga Network Filesystem
//#                          Rudi Chiarito <nutello&sweetness.com>
//rtcm-sc104	2101/tcp   rtcm-sc104
//rtcm-sc104	2101/udp   rtcm-sc104
//#			   Wolfgang Rupprecht <wolfgang&wsrcc.com>
//zephyr-srv      2102/tcp   Zephyr server
//zephyr-srv      2102/udp   Zephyr server
//zephyr-clt      2103/tcp   Zephyr serv-hm connection
//zephyr-clt      2103/udp   Zephyr serv-hm connection
//zephyr-hm       2104/tcp   Zephyr hostmanager
//zephyr-hm       2104/udp   Zephyr hostmanager
//#                          Greg Hudson <zephyr-bugs&mit.edu>
//minipay		2105/tcp   MiniPay
//minipay		2105/udp   MiniPay
//#			   Amir Herzberg <amirh&vnet.ibm.com>
//mzap		2106/tcp   MZAP
//mzap		2106/udp   MZAP
//#			   Dave Thaler <dthaler&microsoft.com>
//bintec-admin	2107/tcp   BinTec Admin 
//bintec-admin	2107/udp   BinTec Admin 
//#			   Thomas Schmidt <ts&bintec.de>
//comcam		2108/tcp   Comcam
//comcam		2108/udp   Comcam
//#			   Don Gilbreath <don&comcam.net>
//ergolight       2109/tcp   Ergolight
//ergolight       2109/udp   Ergolight
//#                          Jindra Ryvola <jryvola&ledalite.com>
//umsp            2110/tcp   UMSP
//umsp            2110/udp   UMSP
//#                          Alexander Bogdanov <alexander_bgd&softhome.net>    
//dsatp           2111/tcp   DSATP
//dsatp           2111/udp   DSATP
//#                          Ralph Beck <beck&altaworks.com>
//idonix-metanet  2112/tcp   Idonix MetaNet
//idonix-metanet  2112/udp   Idonix MetaNet
//#                          Paul Harrison <paulh&idonix.co.uk>
//hsl-storm       2113/tcp   HSL StoRM
//hsl-storm       2113/udp   HSL StoRM
//#                          Jost Faganel <jost.faganel&hermes.si>   
//newheights      2114/tcp   NEWHEIGHTS
//newheights      2114/udp   NEWHEIGHTS
//#                          Michael Levy <ml&nh.ca>
//kdm             2115/tcp   Key Distribution Manager
//kdm             2115/udp   Key Distribution Manager
//#                          Mike Little <mike.little&GDC4S.com>
//ccowcmr         2116/tcp   CCOWCMR
//ccowcmr         2116/udp   CCOWCMR
//#                          Mark Morwood <markm&sentillion.com> 
//mentaclient     2117/tcp   MENTACLIENT
//mentaclient     2117/udp   MENTACLIENT
//mentaserver     2118/tcp   MENTASERVER
//mentaserver     2118/udp   MENTASERVER
//#                          Ilan Shlosberg <ilan&mentasoftware.com>
//gsigatekeeper   2119/tcp   GSIGATEKEEPER
//gsigatekeeper   2119/udp   GSIGATEKEEPER
//#                          Steve Tuecke <tuecke&mcs.anl.gov>
//qencp           2120/tcp   Quick Eagle Networks CP
//qencp           2120/udp   Quick Eagle Networks CP
//#                          Santa Dasu <Santa_Dasu&quickeagle.com>
//scientia-ssdb   2121/tcp   SCIENTIA-SSDB
//scientia-ssdb   2121/udp   SCIENTIA-SSDB
//#                          SYSTEMS MANAGER <systems-manager&scientia.com>
//caupc-remote    2122/tcp   CauPC Remote Control
//caupc-remote    2122/udp   CauPC Remote Control
//#                          Environics Oy <pasi.nuutinmaki&environics.fi>    
//gtp-control     2123/tcp   GTP-Control Plane (3GPP)
//gtp-control     2123/udp   GTP-Control Plane (3GPP)
//#                          Alessio Casati <a.casati&computer.org>
//elatelink       2124/tcp   ELATELINK
//elatelink       2124/udp   ELATELINK
//#                          Tim Lawrence <lawrence&tao-group.com>
//lockstep        2125/tcp   LOCKSTEP
//lockstep        2125/udp   LOCKSTEP
//#                          Karl Forster <kforster&lockstep.com> 
//pktcable-cops   2126/tcp   PktCable-COPS
//pktcable-cops   2126/udp   PktCable-COPS
//#                          Glenn Russell <grussell&cablelabs.com> 
//index-pc-wb     2127/tcp   INDEX-PC-WB
//index-pc-wb     2127/udp   INDEX-PC-WB
//#                          James David Fisher <jfisher1&avaya.com>
//net-steward     2128/tcp   Net Steward Control
//net-steward     2128/udp   Net Steward Control
//#                          Martin Norman <martin&ndl.co.uk>
//cs-live         2129/tcp   cs-live.com
//cs-live         2129/udp   cs-live.com
//#                          Matt Lachance <matt&cs-live.com>
//xds             2130/tcp   XDS
//xds             2130/udp   XDS
//#                          Peter Zurich <pbz&Lowpft.com>
//avantageb2b     2131/tcp   Avantageb2b
//avantageb2b     2131/udp   Avantageb2b
//#                          Avi Software <srobert&logava.com>
//solera-epmap    2132/tcp   SoleraTec End Point Map
//solera-epmap    2132/udp   SoleraTec End Point Map
//#                          Mark Armstrong <Mark.Armstrong&SoleraTec.com>
//zymed-zpp       2133/tcp   ZYMED-ZPP
//zymed-zpp       2133/udp   ZYMED-ZPP
//#                          Gregg Welker <greggw&zmi.com>
//avenue          2134/tcp   AVENUE
//avenue          2134/udp   AVENUE
//#                          Jason Cater <jason&ncsmags.com>
//gris            2135/tcp   Grid Resource Information Server
//gris            2135/udp   Grid Resource Information Server
//#                          Steve Tuecke <tuecke&mcs.anl.gov>   
//appworxsrv      2136/tcp   APPWORXSRV
//appworxsrv      2136/udp   APPWORXSRV
//#                          Fred McLain <fmclain&appworx.com>
//connect         2137/tcp   CONNECT
//connect         2137/udp   CONNECT
//#                          Reid Ligon <reid&connectrf.com>   
//unbind-cluster  2138/tcp   UNBIND-CLUSTER
//unbind-cluster  2138/udp   UNBIND-CLUSTER
//#                          Francois Harvey <securiweb&pandore.qc.ca>
//ias-auth        2139/tcp   IAS-AUTH	     
//ias-auth        2139/udp   IAS-AUTH
//ias-reg         2140/tcp   IAS-REG
//ias-reg         2140/udp   IAS-REG
//ias-admind      2141/tcp   IAS-ADMIND
//ias-admind      2141/udp   IAS-ADMIND
//#                          Baiju V. Patel <Baiju.v.patel&intel.com>
//tdmoip		2142/tcp   TDM OVER IP
//tdmoip		2142/udp   TDM OVER IP
//#                          [RFC5087]
//lv-jc           2143/tcp   Live Vault Job Control
//lv-jc           2143/udp   Live Vault Job Control
//lv-ffx          2144/tcp   Live Vault Fast Object Transfer
//lv-ffx          2144/udp   Live Vault Fast Object Transfer
//lv-pici         2145/tcp   Live Vault Remote Diagnostic Console Support
//lv-pici         2145/udp   Live Vault Remote Diagnostic Console Support
//lv-not          2146/tcp   Live Vault Admin Event Notification
//lv-not          2146/udp   Live Vault Admin Event Notification
//lv-auth         2147/tcp   Live Vault Authentication
//lv-auth         2147/udp   Live Vault Authentication
//#                          Ted Hess <thess&livevault.com>
//veritas-ucl     2148/tcp   VERITAS UNIVERSAL COMMUNICATION LAYER
//veritas-ucl     2148/udp   VERITAS UNIVERSAL COMMUNICATION LAYER
//#                          Songlin Ren <ren&veritas.com>	
//acptsys         2149/tcp   ACPTSYS
//acptsys         2149/udp   ACPTSYS
//#                          Michael Lekias <admin&psdesign.com.au>         
//dynamic3d       2150/tcp   DYNAMIC3D
//dynamic3d       2150/udp   DYNAMIC3D
//#                          Tobias Wegner <wegner&novagate.de>		
//docent          2151/tcp   DOCENT
//docent          2151/udp   DOCENT
//#                          Hali Lindbloom <halil&docent.com>
//gtp-user        2152/tcp   GTP-User Plane (3GPP)
//gtp-user        2152/udp   GTP-User Plane (3GPP)
//#                          Alessio Casati <a.casati&computer.org> 
//ctlptc		2153/tcp   Control Protocol 
//ctlptc		2153/udp   Control Protocol 
//stdptc		2154/tcp   Standard Protocol
//stdptc		2154/udp   Standard Protocol
//brdptc		2155/tcp   Bridge Protocol 
//brdptc		2155/udp   Bridge Protocol 
//#			   Mr.Hideki Hatta <ponum&canon-is.co.jp> 27 September 2007
//trp		2156/tcp   Talari Reliable Protocol
//trp		2156/udp   Talari Reliable Protocol
//#			   John E. Dickey <jdickey&talarinetworks.com> 27 September 2007
//xnds            2157/tcp   Xerox Network Document Scan Protocol
//xnds            2157/udp   Xerox Network Document Scan Protocol
//#                          William R. Lear <william.lear&xerox.com> 06 March 2008
//touchnetplus    2158/tcp   TouchNetPlus Service
//touchnetplus    2158/udp   TouchNetPlus Service
//#                          Brian Toothill <brian.toothill&touchstar.co.uk> 06 March 2008
//gdbremote       2159/tcp   GDB Remote Debug Port
//gdbremote       2159/udp   GDB Remote Debug Port
//#                          Nigel Stephens <nigel&algor.co.uk>
//apc-2160        2160/tcp   APC 2160
//apc-2160        2160/udp   APC 2160
//#                          American Power Conversion <ports&apcc.com>
//apc-2161        2161/tcp   APC 2161
//apc-2161        2161/udp   APC 2161
//#                          American Power Conversion <ports&apcc.com>
//navisphere      2162/tcp   Navisphere
//navisphere      2162/udp   Navisphere
//navisphere-sec  2163/tcp   Navisphere Secure
//navisphere-sec  2163/udp   Navisphere Secure
//#                          Andreas Bauer <bauer_andreas&emc.com>
//ddns-v3         2164/tcp   Dynamic DNS Version 3
//ddns-v3         2164/udp   Dynamic DNS Version 3
//#                          Alan Yates <alany&ay.com.au>
//x-bone-api	2165/tcp   X-Bone API
//x-bone-api	2165/udp   X-Bone API
//#			   Joe Touch <touch&isi.edu>
//iwserver        2166/tcp   iwserver
//iwserver        2166/udp   iwserver
//#                          Fred Surr <quest_iana&oz.quest.com>
//raw-serial      2167/tcp   Raw Async Serial Link
//raw-serial      2167/udp   Raw Async Serial Link
//#                          Benjamin Green <ben&lh.co.nz>
//easy-soft-mux   2168/tcp   easy-soft Multiplexer
//easy-soft-mux   2168/udp   easy-soft Multiplexer
//#                          Norbert Kintzler <NKintzler&easy-soft-dresden.de> November 2004
//brain		2169/tcp   Backbone for Academic Information Notification (BRAIN)
//brain		2169/udp   Backbone for Academic Information Notification (BRAIN)
//#			   Archishmat Gore <archisgore&yahoo.com> November 2004
//eyetv           2170/tcp   EyeTV Server Port
//eyetv           2170/udp   EyeTV Server Port
//#                          Elgato Systems <portinfo&elgato.com> November 2004    
//msfw-storage    2171/tcp   MS Firewall Storage
//msfw-storage    2171/udp   MS Firewall Storage
//msfw-s-storage  2172/tcp   MS Firewall SecureStorage
//msfw-s-storage  2172/udp   MS Firewall SecureStorage
//msfw-replica    2173/tcp   MS Firewall Replication
//msfw-replica    2173/udp   MS Firewall Replication
//msfw-array      2174/tcp   MS Firewall Intra Array
//msfw-array      2174/udp   MS Firewall Intra Array
//#                          Itai Greenberg <itaig&microsoft.com> November 2004
//airsync         2175/tcp   Microsoft Desktop AirSync Protocol
//airsync         2175/udp   Microsoft Desktop AirSync Protocol
//rapi            2176/tcp   Microsoft ActiveSync Remote API
//rapi            2176/udp   Microsoft ActiveSync Remote API
//#                          Jon Xu <jonxu&microsoft.com> August 2005
//qwave           2177/tcp   qWAVE Bandwidth Estimate
//qwave           2177/udp   qWAVE Bandwidth Estimate
//#                          Gabe Frost <gfrost&microsoft.com> August 2005
//bitspeer        2178/tcp   Peer Services for BITS
//bitspeer        2178/udp   Peer Services for BITS
//#                          Jeff Roberts <jroberts&microsoft.com> November 2005
//vmrdp		2179/tcp   Microsoft RDP for virtual machines
//vmrdp		2179/udp   Microsoft RDP for virtual machines
//#			   Brian Henry <brian.henry&microsoft.com> March 2007
//mc-gt-srv	2180/tcp   Millicent Vendor Gateway Server
//mc-gt-srv	2180/udp   Millicent Vendor Gateway Server
//#			   Steve Glassman <steveg&pa.dec.com>
//eforward        2181/tcp   eforward
//eforward        2181/udp   eforward
//#                          Greg Pringle <admin&corvedia.com>
//cgn-stat        2182/tcp   CGN status
//cgn-stat        2182/udp   CGN status
//cgn-config      2183/tcp   Code Green configuration
//cgn-config      2183/udp   Code Green configuration
//#                          Chris Michaelson <chris&codegreennetworks.com> August 2005
//nvd             2184/tcp   NVD User
//nvd             2184/udp   NVD User
//#                          Yves Gattegno <iana&qualystem.org> December 2004
//onbase-dds      2185/tcp   OnBase Distributed Disk Services
//onbase-dds      2185/udp   OnBase Distributed Disk Services
//#                          Paul Tam <ianaportmaster&onbase.com> December 2004
//gtaua           2186/tcp   Guy-Tek Automated Update Applications
//gtaua           2186/udp   Guy-Tek Automated Update Applications
//#                          Daniel Story <dan&guy-tek.com> 25 January 2008
//ssmc            2187/tcp   Sepehr System Management Control
2187,//ssmd            2187/udp   Sepehr System Management Data
//#                          Shahriar Pourazin <pourazin&sepehrs.com> 02 December 2008
//#               2188-2189  Unassigned
2190,//tivoconnect     2190/tcp   TiVoConnect Beacon
//tivoconnect     2190/udp   TiVoConnect Beacon
//#                          Jeffrey J. Peters <jpeters&tivo.com> August 2002
//tvbus           2191/tcp   TvBus Messaging
//tvbus           2191/udp   TvBus Messaging
//#                          Brian W. Beach <brian&tivo.com> January 2003               
//asdis           2192/tcp   ASDIS software management
//asdis           2192/udp   ASDIS software management
//#                          ASDIS Support <support&asdis.de> August 2005
//drwcs           2193/tcp   Dr.Web Enterprise Management Service
//drwcs           2193/udp   Dr.Web Enterprise Management Service
2193,//#                          Eugeny Gladkih <john&drweb.com> 31 January 2008
//#               2194-2196  Unassigned
2197,//mnp-exchange    2197/tcp   MNP data exchange
//mnp-exchange    2197/udp   MNP data exchange
//#                          Peter Pramberger <peter.pramberger&telering.co.at> November 2004
//onehome-remote  2198/tcp   OneHome Remote Access
//onehome-remote  2198/udp   OneHome Remote Access
//onehome-help    2199/tcp   OneHome Service Port
//onehome-help    2199/udp   OneHome Service Port
//#                          Jim Herman <jherman&homelogic.com> August 2005
//ici             2200/tcp   ICI
//ici             2200/udp   ICI
//#                          Brent Hines <brent.hines&unisys.com>
//ats             2201/tcp   Advanced Training System Program
//ats             2201/udp   Advanced Training System Program
//#                          (Need contact info)
//imtc-map        2202/tcp   Int. Multimedia Teleconferencing Cosortium
//imtc-map        2202/udp   Int. Multimedia Teleconferencing Cosortium
//#                          Pat Galvin <pgalvin&databeam.com>
//b2-runtime	2203/tcp   b2 Runtime Protocol
//b2-runtime	2203/udp   b2 Runtime Protocol
//b2-license	2204/tcp   b2 License Server
//b2-license	2204/udp   b2 License Server
//#			   Helge-Frank Zimpel <helge.zimpel&baeurer.de> January 2006
//jps 		2205/tcp   Java Presentation Server
//jps 		2205/udp   Java Presentation Server
//#			   Leif Jakob <leif+iana&cube.ch> January 2006
//hpocbus         2206/tcp   HP OpenCall bus
//hpocbus         2206/udp   HP OpenCall bus
//#                          Jerome Forissier <Jerome.Forissier&hp.com> December 2005
//hpssd		2207/tcp   HP Status and Services
//hpssd		2207/udp   HP Status and Services
//#			   Donald Welch <donald.welch&hp.com> May 2006
//hpiod		2208/tcp   HP I/O Backend
//hpiod		2208/udp   HP I/O Backend
//#			   David Suffield <david.suffield&hp.com> May 2006
//rimf-ps		2209/tcp   HP RIM for Files Portal Service
//rimf-ps		2209/udp   HP RIM for Files Portal Service
//#			   Patty Ho <rimf&core.rose.hp.com> May 2007
//noaaport        2210/tcp   NOAAPORT Broadcast Network
//noaaport        2210/udp   NOAAPORT Broadcast Network
//emwin           2211/tcp   EMWIN
//emwin           2211/udp   EMWIN
//#                          Antonio Querubin <tony&lava.net> 10 March 2008
//leecoposserver  2212/tcp   LeeCO POS Server Service
//leecoposserver  2212/udp   LeeCO POS Server Service
//#                          Patrick Lee <leecotechnologies&comcast.net> 10 March 2008
//kali            2213/tcp   Kali
//kali            2213/udp   Kali
//#                          Jay Cotton <JAY&calc.vet.uga.edu>
//rpi		2214/tcp   RDQ Protocol Interface
//rpi		2214/udp   RDQ Protocol Interface
//#			   Les Mather <lm&remsdaq.com> December 2005
//ipcore		2215/tcp   IPCore.co.za GPRS
//ipcore		2215/udp   IPCore.co.za GPRS
//#			   Administrator <admin&ipcore.co.za> December 2005
//vtu-comms       2216/tcp   VTU data service
//vtu-comms       2216/udp   VTU data service
//#			   David Barrass <dbarrass&bartecautoid.com> January 2006
//gotodevice      2217/tcp   GoToDevice Device Management
//gotodevice      2217/udp   GoToDevice Device Management
//#			   John Lisek <jl&gotodevice.com> January 2006
//bounzza         2218/tcp   Bounzza IRC Proxy
//bounzza         2218/udp   Bounzza IRC Proxy
//#			   Danko Alexeyev <virtuall&virtuall.info> February 2006
//netiq-ncap  	2219/tcp   NetIQ NCAP Protocol
//netiq-ncap  	2219/udp   NetIQ NCAP Protocol
//#			   Roger Huebner <Roger.Huebner&netiq.com> January 2006
//netiq           2220/tcp   NetIQ End2End
//netiq           2220/udp   NetIQ End2End
//#			   Gary Weichinger <gary.weichinger&netiq.com>
//rockwell-csp1	2221/tcp   Rockwell CSP1
//rockwell-csp1	2221/udp   Rockwell CSP1
//#                          Brian Batke <csp.protocol&gmail.com> 
//EtherNet/IP-1   2222/tcp   EtherNet/IP I/O
//EtherNet/IP-1   2222/udp   EtherNet/IP I/O
//#                          Brian Batke <eip.jsig&gmail.com>
//#                          New contact added for port 2222 on 2008-02-01
//rockwell-csp2   2223/tcp   Rockwell CSP2
//rockwell-csp2   2223/udp   Rockwell CSP2
//#                          Brian Batke <csp.protocol&gmail.com>	
//efi-mg		2224/tcp   Easy Flexible Internet/Multiplayer Games
//efi-mg		2224/udp   Easy Flexible Internet/Multiplayer Games
//#			   Thomas Efer <mail&thomasefer.de> March 2006
//rcip-itu	2225/tcp   Resource Connection Initiation Protocol
//rcip-itu	2225/sctp  Resource Connection Initiation Protocol
//#			   ITU TSB, Place des Nations, CH-1211 Geneva 20 <tsbmail&itu.int> June 2006
//di-drm		2226/tcp   Digital Instinct DRM
//di-drm		2226/udp   Digital Instinct DRM
//di-msg		2227/tcp   DI Messaging Service
//di-msg		2227/udp   DI Messaging Service
//#			   Sean Ni <seanni&digitalinstinct.com.tw> February 2006
//ehome-ms	2228/tcp   eHome Message Server
//ehome-ms	2228/udp   eHome Message Server
//#			   Peter Gabriel <peter.gabriel&ims.fraunhofer.de> January 2006
//datalens	2229/tcp   DataLens Service
//datalens	2229/udp   DataLens Service
//#			   Christopher Bidwell <cbidwell&silvercreeksystems.com> February 2006
//queueadm	2230/tcp   MetaSoft Job Queue Administration Service
//queueadm	2230/udp   MetaSoft Job Queue Administration Service
//#			   Ilya Melamed <ilya77&gmail.com> June 2006
//wimaxasncp	2231/tcp   WiMAX ASN Control Plane Protocol
//wimaxasncp	2231/udp   WiMAX ASN Control Plane Protocol
//#			   Prakash Iyer <prakash.iyer&intel.com> June 2006
//ivs-video       2232/tcp   IVS Video default
//ivs-video       2232/udp   IVS Video default
//#                  Thierry Turletti <Thierry.Turletti&sophia.inria.fr>
//infocrypt	2233/tcp   INFOCRYPT
//infocrypt	2233/udp   INFOCRYPT
//#			   Erica Liu <liue&isolation.com>
//directplay      2234/tcp   DirectPlay
//directplay      2234/udp   DirectPlay
//#                          Ajay Jindal <ajayj&microsoft.com>
//sercomm-wlink	2235/tcp   Sercomm-WLink
//sercomm-wlink   2235/udp   Sercomm-WLink
//#			   Melinda Tsao <melinda&tpe1.sercomm.com.tw>
//nani		2236/tcp   Nani
//nani		2236/udp   Nani
//#			   Steve Benoit <sbenoi01&eng.eds.com>
//optech-port1-lm 2237/tcp   Optech Port1 License Manager
//optech-port1-lm 2237/udp   Optech Port1 License Manager
//#		 	   Gerard Cannie <jcannie&opticaltech.com>
//aviva-sna	2238/tcp   AVIVA SNA SERVER
//aviva-sna	2238/udp   AVIVA SNA SERVER
//#			   Vick Keshishian <vickenK&192.219.82.71>
//imagequery	2239/tcp   Image Query	
//imagequery      2239/udp   Image Query
//#			   Charles Jacobs <cjacobs&numinous.com>
//recipe		2240/tcp   RECIPe
//recipe		2240/udp   RECIPe
//#			   Charlie Limoges <Charlie.Limoges&GDC4S.com>
//ivsd            2241/tcp   IVS Daemon
//ivsd            2241/udp   IVS Daemon
//#                          Thierry Turletti 
//#                          <Thierry.Turletti&sophia.inria.fr>
//foliocorp       2242/tcp   Folio Remote Server
//foliocorp       2242/udp   Folio Remote Server
//#                          Pat Mcgowan <pmcgowan&folio.com>
//magicom		2243/tcp   Magicom Protocol
//magicom		2243/udp   Magicom Protocol
//#			   Yossi Appleboum <yossia&magicom.co.il>
//nmsserver	2244/tcp   NMS Server
//nmsserver	2244/udp   NMS Server
//#			   Dmitry Krasnonosenkikh
//#			   <Dmitry_Krasnonosenkih&nmss.com>
//hao		2245/tcp   HaO
//hao		2245/udp   HaO
//#			   Panic Ride <panicride&hao.org>
//pc-mta-addrmap  2246/tcp   PacketCable MTA Addr Map
//pc-mta-addrmap  2246/udp   PacketCable MTA Addr Map
//#                          Dave Maxwell <d.maxwell&cablelabs.com>
//antidotemgrsvr  2247/tcp   Antidote Deployment Manager Service
//antidotemgrsvr  2247/udp   Antidote Deployment Manager Service
//#			   Rod Waltermann <walterma&us.lenovo.com> February 2006
//ums             2248/tcp   User Management Service
//ums 		2248/udp   User Management Service
//#                          Andrew Crockford 
//#                          <andrew.crockford&modus-interactive.co.uk>
//rfmp		2249/tcp   RISO File Manager Protocol
//rfmp		2249/udp   RISO File Manager Protocol
//#                          Shinji Yamanaka <syamanaka&jci.co.jp>
//remote-collab   2250/tcp   remote-collab
//remote-collab   2250/udp   remote-collab
//#                          Richard Walters <walters&cs.ucdavis.edu>
//dif-port	2251/tcp   Distributed Framework Port
//dif-port        2251/udp   Distributed Framework Port
//#                          Sebastien Lambla <lambla&bouygtel.com>
//njenet-ssl      2252/tcp   NJENET using SSL
//njenet-ssl      2252/udp   NJENET using SSL
//#                          Hans U Schmidt <schmidth&de.ibm.com>
//dtv-chan-req	2253/tcp   DTV Channel Request
//dtv-chan-req    2253/udp   DTV Channel Request
//#                          Richard Hodges <rh&matriplex.com>
//seispoc         2254/tcp   Seismic P.O.C. Port
//seispoc         2254/udp   Seismic P.O.C. Port
//#                          Robert Reimiller <bob&certsoft.com>
//vrtp            2255/tcp   VRTP - ViRtue Transfer Protocol
//vrtp            2255/udp   VRTP - ViRtue Transfer Protocol
//#                          Max Fudim <fudim&virtue3d.com> 
//pcc-mfp         2256/tcp   PCC MFP
//pcc-mfp         2256/udp   PCC MFP
//#                          Kunihiko Morota <morota.kunihiko&jp.panasonic.com> August 2005
//simple-tx-rx	2257/tcp   simple text/file transfer
//simple-tx-rx	2257/udp   simple text/file transfer
//#			   Daniel Kilsdonk <dan&prospeed.net> August 2006
//rcts		2258/tcp   Rotorcraft Communications Test System
//rcts		2258/udp   Rotorcraft Communications Test System
//#			   Terry Eldridge <Terry.Eldridge&6pointn.com> August 2006
//acd-pm		2259/tcp   Accedian Performance Measurement
//acd-pm		2259/udp   Accedian Performance Measurement
//#			   Claude Robitaille <clauder&accedian.com> August 2006
//apc-2260        2260/tcp   APC 2260
//apc-2260        2260/udp   APC 2260
//#                          American Power Conversion <ports&apcc.com> February 2002
//comotionmaster  2261/tcp   CoMotion Master Server
//comotionmaster  2261/udp   CoMotion Master Server
//comotionback    2262/tcp   CoMotion Backup Server
//comotionback    2262/udp   CoMotion Backup Server
//#                          Friedman Wagner-Dobler <Friedman.Wagner-Dobler&gdc4s.com> September 2005
//ecwcfg		2263/tcp   ECweb Configuration Service
//ecwcfg		2263/udp   ECweb Configuration Service
//#			   Anders Hjelm <anders.hjelm&ec.se> March 2006
//apx500api-1	2264/tcp   Audio Precision Apx500 API Port 1
//apx500api-1	2264/udp   Audio Precision Apx500 API Port 1
//apx500api-2	2265/tcp   Audio Precision Apx500 API Port 2
//apx500api-2	2265/udp   Audio Precision Apx500 API Port 2
//#			   Robert Wright, Founder and Principal Engineer, Audio Precision Inc.
//#			   <ianaports&ap.com> May 2006
//mfserver        2266/tcp   M-Files Server
//mfserver        2266/udp   M-files Server
//#                          Samppa Lahtinen <samppa.lahtinen&motivesys.com>, June 2004
//ontobroker      2267/tcp   OntoBroker
//ontobroker      2267/udp   OntoBroker
//#                          Dr. Michael Erdmann <erdmann&ontoprise.de> December 2004
//amt             2268/tcp   AMT
//amt             2268/udp   AMT
//#                          Tom Pusateri <pusateri&juniper.net> December 2004
//mikey           2269/tcp   MIKEY
//mikey           2269/udp   MIKEY
//#                          Karl Norrman <karl.norrman&ericsson.com> December 2004
//starschool      2270/tcp   starSchool
//starschool      2270/udp   starSchool
//#                          Adam Ernst <cosmicsoft&cosmicsoft.net> December 2004
//mmcals          2271/tcp   Secure Meeting Maker Scheduling
//mmcals          2271/udp   Secure Meeting Maker Scheduling
//mmcal           2272/tcp   Meeting Maker Scheduling
//mmcal           2272/udp   Meeting Maker Scheduling
//#                          Andrew H Derbyshire <ahd&meetingmaker.plus.kew.com> December 2004 
//mysql-im        2273/tcp   MySQL Instance Manager
//mysql-im        2273/udp   MySQL Instance Manager
//#                          Petr Chardin <petr&mysql.com> December 2004
//pcttunnell      2274/tcp   PCTTunneller
//pcttunnell      2274/udp   PCTTunneller
//#                          ProControl Technology AB <info&pctworld.com> December 2004
//ibridge-data    2275/tcp   iBridge Conferencing
//ibridge-data    2275/udp   iBridge Conferencing
//ibridge-mgmt    2276/tcp   iBridge Management 
//ibridge-mgmt    2276/udp   iBridge Management 
//#                          Patrick Fisher <pfisher&hns.com> December 2004
//bluectrlproxy   2277/tcp   Bt device control proxy
//bluectrlproxy   2277/udp   Bt device control proxy
//#                          Mark de Rooi <derooi&xs4all.nl> December 2004         
//s3db		2278/tcp   Simple Stacked Sequences Database
//s3db		2278/udp   Simple Stacked Sequences Database
//#			   David Brandon <dade&smoolabs.net> August 2006
//xmquery         2279/tcp   xmquery
//xmquery         2279/udp   xmquery
//#                          Niels Christiansen <nchris&austin.ibm.com>
//lnvpoller       2280/tcp   LNVPOLLER
//lnvpoller       2280/udp   LNVPOLLER
//lnvconsole      2281/tcp   LNVCONSOLE
//lnvconsole      2281/udp   LNVCONSOLE
//lnvalarm        2282/tcp   LNVALARM
//lnvalarm        2282/udp   LNVALARM
//lnvstatus       2283/tcp   LNVSTATUS
//lnvstatus       2283/udp   LNVSTATUS
//lnvmaps         2284/tcp   LNVMAPS
//lnvmaps         2284/udp   LNVMAPS
//lnvmailmon      2285/tcp   LNVMAILMON
//lnvmailmon      2285/udp   LNVMAILMON
//#                          John Payne <jpayne&lotus.com> 
//nas-metering    2286/tcp   NAS-Metering
//nas-metering    2286/udp   NAS-Metering
//#                          Steven Sawkins <ssawkins&symantec.com>    
//dna		2287/tcp   DNA
//dna		2287/udp   DNA
//#			   Tung Nguyen <dash&ricochet.net>
//netml		2288/tcp   NETML
//netml		2288/udp   NETML
//#			   Jochen Hansmeyer <cjh&krypton.de>
//dict-lookup     2289/tcp   Lookup dict server 
//dict-lookup     2289/udp   Lookup dict server  
//#                          William Fernando Maton Sotomayor <wfms&acm.org> January 2005
//sonus-logging   2290/tcp   Sonus Logging Services
//sonus-logging   2290/udp   Sonus Logging Services
//#                          Adwait Sathe <asathe&sonusnet.com> August 2005
//eapsp		2291/tcp   EPSON Advanced Printer Share Protocol
//eapsp		2291/udp   EPSON Advanced Printer Share Protocol
//#			   SEIKO EPSON <APD.admin&exc.epson.co.jp> June 2006
//mib-streaming   2292/tcp   Sonus Element Management Services
//mib-streaming   2292/udp   Sonus Element Management Services
//#			   Linda Lin <llin&sonusnet.com> August 2006
//npdbgmngr	2293/tcp   Network Platform Debug Manager
//npdbgmngr	2293/udp   Network Platform Debug Manager
//#			   Robert Byrne <robert.byrne&ie.abb.com> September 2006
//konshus-lm	2294/tcp   Konshus License Manager (FLEX)
//konshus-lm	2294/udp   Konshus License Manager (FLEX)
//#			   Francois Painchaud <fpainchaud&konshus.com>
//advant-lm	2295/tcp   Advant License Manager
//advant-lm	2295/udp   Advant License Manager
//#			   Lars-Goran Magnusson 
//#                          <lars-goran.magnusson&seisy.mail.abb.com>
//theta-lm	2296/tcp   Theta License Manager (Rainbow)
//theta-lm	2296/udp   Theta License Manager (Rainbow)
//#		   	   David Thompson <theta&theta-ent.com>
//d2k-datamover1	2297/tcp   D2K DataMover 1
//d2k-datamover1	2297/udp   D2K DataMover 1
//d2k-datamover2  2298/tcp   D2K DataMover 2
//d2k-datamover2	2298/udp   D2K DataMover 2
//#			   Eric Lan <elan&d2k.com>
//pc-telecommute	2299/tcp   PC Telecommute
//pc-telecommute	2299/udp   PC Telecommute
//#			   John Daniel Bonamico <jbonamico&symantec.com>
//cvmmon          2300/tcp   CVMMON
//cvmmon          2300/udp   CVMMON
//#                          Roger Kumpf <kumpf&cup.hp.com>
//cpq-wbem        2301/tcp   Compaq HTTP
//cpq-wbem        2301/udp   Compaq HTTP
//#                          Scott Shaffer <scott.shaffer&hp.com>
//binderysupport	2302/tcp   Bindery Support
//binderysupport	2302/udp   Bindery Support
//#			   Narasimha Rao N. <nnarasimharao&novell.com>
//proxy-gateway	2303/tcp   Proxy Gateway
//proxy-gateway	2303/udp   Proxy Gateway
//#			   Paul Funk <paul&funk.com>
//attachmate-uts	2304/tcp   Attachmate UTS
//attachmate-uts	2304/udp   Attachmate UTS
//#			   George Gianelos <Georgegi&Attachmate.com>
//mt-scaleserver	2305/tcp   MT ScaleServer
//mt-scaleserver	2305/udp   MT ScaleServer
//#			   Paul Glaubitz <Paul.Glaubitz&mt.com>
//tappi-boxnet	2306/tcp   TAPPI BoxNet
//tappi-boxnet	2306/udp   TAPPI BoxNet
//#			   Richard Spartz <rspartz&alliancetechnical.com>
//pehelp          2307/tcp   pehelp
//pehelp          2307/udp   pehelp
//#                          Jens Kilian <jensk&hpbeo82.bbn.hp.com>
//sdhelp		2308/tcp   sdhelp
//sdhelp		2308/udp   sdhelp
//#			   Annette Klecha <annette_klecha&bbn.hp.com>
//sdserver	2309/tcp   SD Server
//sdserver	2309/udp   SD Server
//sdclient	2310/tcp   SD Client
//sdclient	2310/udp   SD Client
//#			   Jeurgen Broesamle <juergb&bbn.hp.com>
//messageservice	2311/tcp   Message Service
//messageservice	2311/udp   Message Service
//#			   No contact Listed	
//wanscaler	2312/tcp   WANScaler Communication Service
//wanscaler	2312/udp   WANScaler Communication Service
//#			   Allen Samuels <allen.samuels&citrix.com> November 2006
//iapp		2313/tcp   IAPP (Inter Access Point Protocol)
//iapp		2313/udp   IAPP (Inter Access Point Protocol)
//#			   Henri Moelard <moelard&lucent.com>
//cr-websystems	2314/tcp   CR WebSystems
//cr-websystems	2314/udp   CR WebSystems
//#			   Robin Giese <rgiese&peddie.org>
//precise-sft	2315/tcp   Precise Sft.
//precise-sft	2315/udp   Precise Sft.
//#			   Michael Landwehr <mikel&precisesoft.co.il>
//sent-lm		2316/tcp   SENT License Manager
//sent-lm		2316/udp   SENT License Manager
//#			   Pisharath Krishnan <krishnan&axis-inc.com>
//attachmate-g32	2317/tcp   Attachmate G32
//attachmate-g32	2317/udp   Attachmate G32
//#			   Bryce Bhatnagar <BRYCEBH&Attachmate.com>
//cadencecontrol	2318/tcp   Cadence Control
//cadencecontrol	2318/udp   Cadence Control
//#			   Buck Caldwell <buck_c&polygon.com>
//infolibria	2319/tcp   InfoLibria
//infolibria	2319/udp   InfoLibria
//#			   Chris Chiotasso <cchiotasso&infolibria.com>
//siebel-ns	2320/tcp   Siebel NS
//siebel-ns	2320/udp   Siebel NS
//#			   Gilberto Arnaiz <garnaiz&siebel.com>
//rdlap		2321/tcp   RDLAP
//rdlap		2321/udp   RDLAP
//#			   Robert Wiebe <crw010&email.mot.com>
//ofsd		2322/tcp   ofsd
//ofsd		2322/udp   ofsd
//3d-nfsd		2323/tcp   3d-nfsd
//3d-nfsd		2323/udp   3d-nfsd
//#			   Mike Sherrill <sherrill&commvault.com>
//cosmocall	2324/tcp   Cosmocall
//cosmocall	2324/udp   Cosmocall
//#			   Steve Dellutri
//ansysli         2325/tcp   ANSYS Licensing Interconnect
//ansysli         2325/udp   ANSYS Licensing Interconnect
//#			   Suzanne Lorrin <suzanne.lorrin&ansys.com>
//#                          Modified: 27 October 2008
//idcp		2326/tcp   IDCP
//idcp		2326/udp   IDCP
//#			   Keisokugiken Corp. <adda&kgc.co.jp>
//xingcsm		2327/tcp   xingcsm
//xingcsm		2327/udp   xingcsm
//#			   Dave Spencer <dspencer&xingtech.com>
//netrix-sftm	2328/tcp   Netrix SFTM
//netrix-sftm	2328/udp   Netrix SFTM
//#			   Garrett Herschleb <garrett&netrix.com>
//nvd		2329/tcp   NVD
//nvd		2329/udp   NVD
//#			   Peter Weyman <pjweyman&noblenet.com>
//tscchat		2330/tcp   TSCCHAT
//tscchat		2330/udp   TSCCHAT
//#                          Mike Jackson <mhjack&tscnet.com>
//agentview       2331/tcp   AGENTVIEW
//agentview       2331/udp   AGENTVIEW
//#			               Ram Iyer <ram&aaccorp.com>
//rcc-host        2332/tcp   RCC Host 
//rcc-host        2332/udp   RCC Host
//#			               Martin Shoemaker <shoemakerml&rapistan.com>
//snapp           2333/tcp   SNAPP
//snapp           2333/udp   SNAPP
//#                          Kevin Osborn <kosborn&snapappliance.com>
//ace-client      2334/tcp   ACE Client Auth
//ace-client      2334/udp   ACE Client Auth
//ace-proxy	2335/tcp   ACE Proxy
//ace-proxy	2335/udp   ACE Proxy
//#			               Riaz Zolfonoon <rzolfonoon&securitydynamics.com>
//appleugcontrol  2336/tcp   Apple UG Control
//appleugcontrol	2336/udp   Apple UG Control
//#			               Gene Tyacke <gene&apple.com>
//ideesrv         2337/tcp   ideesrv
//ideesrv	        2337/udp   ideesrv
//#			               Marazzi <fmarazzi&ideetique.com>
//norton-lambert	2338/tcp   Norton Lambert
//norton-lambert	2338/udp   Norton Lambert
//#			               Richard de Mornay <rdemornay&norton-lambert.com>
//3com-webview	2339/tcp   3Com WebView
//3com-webview	2339/udp   3Com WebView
//#			   Jennifer Grace <Jennifer_Grace&3com.com>
//wrs_registry	2340/tcp   WRS Registry
//wrs_registry	2340/udp   WRS Registry
//#			   Christophe Cleraux <chrisc&wrs.com>
//xiostatus	2341/tcp   XIO Status
//xiostatus	2341/udp   XIO Status
//#			   Randy Maas <randym&xiotech.com>
//manage-exec     2342/tcp   Seagate Manage Exec
//manage-exec	2342/udp   Seagate Manage Exec
//#			   Jim Flaherty <jim.flaherty&seagatesoftware.com>
//nati-logos	2343/tcp   nati logos
//nati-logos	2343/udp   nati logos
//#			   James Juhasz <james.juhasz&ni.com>
//fcmsys		2344/tcp   fcmsys
//fcmsys   	2344/udp   fcmsys
//dbm             2345/tcp   dbm
//dbm             2345/udp   dbm
//#			   Dean Robson <dean.robson&fujitsu.com.au>
//redstorm_join	2346/tcp   Game Connection Port
//redstorm_join	2346/udp   Game Connection Port
//redstorm_find	2347/tcp   Game Announcement and Location
//redstorm_find	2347/udp   Game Announcement and Location
//redstorm_info	2348/tcp   Information to query for game status
//redstorm_info	2348/udp   Information to query for game status
//redstorm_diag	2349/tcp   Diagnostics Port
//redstorm_diag	2349/udp   Diagnostics Port
//#                          David Weinstein <david.weinstein&redstorm.com>
//psbserver       2350/tcp   Pharos Booking Server 
//psbserver       2350/udp   Pharos Booking Server 
//psrserver       2351/tcp   psrserver
//psrserver       2351/udp   psrserver
//pslserver       2352/tcp   pslserver
//pslserver       2352/udp   pslserver
//pspserver       2353/tcp   pspserver
//pspserver       2353/udp   pspserver
//psprserver      2354/tcp   psprserver
//psprserver      2354/udp   psprserver
//psdbserver      2355/tcp   psdbserver
//psdbserver      2355/udp   psdbserver
//#                          Paul Reddy <preddy&pharos.com>
//gxtelmd         2356/tcp   GXT License Managemant
//gxtelmd         2356/udp   GXT License Managemant
//#                          Robert Hodgson <rrh&gxt.com>
//unihub-server   2357/tcp   UniHub Server
//unihub-server   2357/udp   UniHub Server
//#                          Tim Kenyon <Tim_Kenyon&csicontrols.com>
//futrix          2358/tcp   Futrix
//futrix          2358/udp   Futrix
//#                          Peter Frankenberg <pcfberg&ibm.net>
//flukeserver     2359/tcp   FlukeServer
//flukeserver     2359/udp   FlukeServer
//#                          Bill Marbaker <wrm&fortenet.com>
//nexstorindltd   2360/tcp   NexstorIndLtd
//nexstorindltd   2360/udp   NexstorIndLtd
//#                          NexStor India Limited <next&nda.vsnl.net.in>	
//tl1             2361/tcp   TL1
//tl1             2361/udp   TL1
//#                          Charles Scott Roberson <chip&cerent.com> 
//digiman         2362/tcp   digiman
//digiman         2362/udp   digiman
//#                          Aaron S. Kurland <akurland&netsilicon.com>
//mediacntrlnfsd  2363/tcp   Media Central NFSD 
//mediacntrlnfsd  2363/udp   Media Central NFSD 
//#                          shivakumar s. govindarajapuram <shivak&eng.sun.com>
//oi-2000         2364/tcp   OI-2000
//oi-2000         2364/udp   OI-2000
//#                          Software Horizons Inc. <oi2000&shorizons.com>   
//dbref           2365/tcp   dbref
//dbref           2365/udp   dbref
//#                          Yoshihiro Yamazaki <yamazaki&ael.fujitsu.co.jp>
//qip-login       2366/tcp   qip-login
//qip-login       2366/udp   qip-login
//#			               Mike Morgan <mmorgan&lucent.com>
//service-ctrl	2367/tcp   Service Control
//service-ctrl	2367/udp   Service Control
//#                          Humberto Sanchez <Humberto_Sanchez&hp.com>
//opentable       2368/tcp   OpenTable
//opentable       2368/udp   OpenTable
//#                          Brett Goldstein <bgoldstein&opentable.com>
//#		2369       De-registered (28 March 2006)
//l3-hbmon        2370/tcp   L3-HBMon
//l3-hbmon        2370/udp   L3-HBMon
//#                          Dolores Scott <Dolores.Scott&L-3security.com>
//#### Port 2370 Unofficially used by Compaq ####
//worldwire       2371/tcp   Compaq WorldWire Port
//worldwire       2371/udp   Compaq WorldWire Port
//#                          Michael Spratte <michael.spratte&compaq.com>
//lanmessenger    2372/tcp   LanMessenger
//lanmessenger    2372/udp   LanMessenger
//#                          Garrett Padera <garrett&garrettsites.net> 01 February 2008
//remographlm     2373/tcp   Remograph License Manager
//#                          Per Fahlberg <support&remograph.com> 21 January 2009
//#               2373/udp   Reserved
//hydra           2374/tcp   Hydra RPC
//#                          Jacob Feisley <jacob&hydralabs.com> 21 January 2009
2374,//#               2374/udp   Reserved 
//#               2375-2380  Unassigned
2381,//compaq-https    2381/tcp   Compaq HTTPS
//compaq-https    2381/udp   Compaq HTTPS
//#                          Scott Shaffer <scott.shaffer&hp.com>
//ms-olap3        2382/tcp   Microsoft OLAP
//ms-olap3        2382/udp   Microsoft OLAP
//ms-olap4        2383/tcp   Microsoft OLAP
//ms-olap4        2383/udp   Microsoft OLAP
//#                          Mosha Pasumansky <moshap&microsoft.com>
//sd-request      2384/tcp   SD-REQUEST
//sd-capacity     2384/udp   SD-CAPACITY
//#                          Jason McManus <jasonm&sleepdep.net>
//sd-data         2385/tcp   SD-DATA
//sd-data         2385/udp   SD-DATA
//#                          Jason McManus <jasonm&sleepdep.net>
//virtualtape     2386/tcp   Virtual Tape
//virtualtape     2386/udp   Virtual Tape
//vsamredirector  2387/tcp   VSAM Redirector
//vsamredirector  2387/udp   VSAM Redirector
//#                          Ingo Franzki <ifranzki&de.ibm.com>
//mynahautostart  2388/tcp   MYNAH AutoStart
//mynahautostart  2388/udp   MYNAH AutoStart
//#                          Thomas J. Klehr <tklehr&telcordia.com>
//ovsessionmgr	2389/tcp   OpenView Session Mgr
//ovsessionmgr	2389/udp   OpenView Session Mgr
//#                          Eric Pulsipher <eric_pulsipher&hp.com>
//rsmtp           2390/tcp   RSMTP
//rsmtp           2390/udp   RSMTP
//#                          Geoff Collyer <geoff&research.bell-labs.com>
//3com-net-mgmt	2391/tcp   3COM Net Management
//3com-net-mgmt	2391/udp   3COM Net Management
//#                          Prathibha Nagvar
//tacticalauth	2392/tcp   Tactical Auth
//tacticalauth	2392/udp   Tactical Auth
//#                          David Yon <yon&tactical-sw.com>   
//ms-olap1	2393/tcp   MS OLAP 1
//ms-olap1	2393/udp   MS OLAP 1
//ms-olap2	2394/tcp   MS OLAP 2
//ms-olap2	2394/udp   MS OLAP 2
//#			   Mosha Pasumansky <moshap&microsoft.com>
//lan900_remote	2395/tcp   LAN900 Remote
//lan900_remote	2395/udp   LAN900 Remote
//#			   Tom Quinlan <tquinlan&digitechinc.com>
//wusage		2396/tcp   Wusage
//wusage 		2396/udp   Wusage
//#			   Thomas Boutell <boutell&boutell.com>
//ncl		2397/tcp   NCL
//ncl		2397/udp   NCL
//#			   Robert Wiebe <crw010&email.mot.com>
//orbiter		2398/tcp   Orbiter
//orbiter		2398/udp   Orbiter
//#			   David Goldberg <dgoldberg&callisto.com>
//fmpro-fdal	2399/tcp   FileMaker, Inc. - Data Access Layer
//fmpro-fdal	2399/udp   FileMaker, Inc. - Data Access Layer
//#			   Clay Maeckal <clay_maeckel&filemaker.com>
//opequus-server	2400/tcp   OpEquus Server
//opequus-server	2400/udp   OpEquus Server
//#			   Gavin Hutchinson <gavinh&tesl.com>
//cvspserver      2401/tcp   cvspserver
//cvspserver      2401/udp   cvspserver
//#                          Jim Kingdon <kingdon&harvey.cyclic.com>
//taskmaster2000	2402/tcp   TaskMaster 2000 Server
//taskmaster2000	2402/udp   TaskMaster 2000 Server
//taskmaster2000	2403/tcp   TaskMaster 2000 Web
//taskmaster2000	2403/udp   TaskMaster 2000 Web
//#			   Ed Odjaghian <edo&datacap.com>
//iec-104         2404/tcp   IEC 60870-5-104 process control over IP
//iec-104         2404/udp   IEC 60870-5-104 process control over IP
//#                          Walter K. Eichelburg <walter.eichelburg&sat-automation.com>
//trc-netpoll	2405/tcp   TRC Netpoll
//trc-netpoll	2405/udp   TRC Netpoll
//#			   Bizhan Ghavami <ghavami&telcores.com>
//jediserver	2406/tcp   JediServer
//jediserver	2406/udp   JediServer
//#			   Paul McEntire <paul.mcentire&columbiasc.ncr.com>
//orion           2407/tcp   Orion
//orion           2407/udp   Orion
//#                          Matthew Horoschun <mhoroschun&canprint.com.au>
//optimanet	2408/tcp   OptimaNet
//optimanet	2408/udp   OptimaNet
//#			   John Graham-Cumming <jgc&optimal.com>
//sns-protocol	2409/tcp   SNS Protocol
//sns-protocol	2409/udp   SNS Protocol
//#			   Amir Blich <amir&netmanage.co.il>
//vrts-registry	2410/tcp   VRTS Registry
//vrts-registry	2410/udp   VRTS Registry
//#			   Pranay Varma <pran&veritas.com>
//netwave-ap-mgmt	2411/tcp   Netwave AP Management
//netwave-ap-mgmt	2411/udp   Netwave AP Management
//#			   Johnny Zweig <zweig&netwave-wireless.com>
//cdn		2412/tcp   CDN
//cdn		2412/udp   CDN
//#			   Alan Noble <noble&netmind.com>
//orion-rmi-reg	2413/tcp   orion-rmi-reg 
//orion-rmi-reg	2413/udp   orion-rmi-reg
//#			   J.S. Greenfield <greeny&us.ibm.com>
//beeyond		2414/tcp   Beeyond
//beeyond		2414/udp   Beeyond
//#			   Bob Deblier <bob&virtualunlimited.com>
//codima-rtp      2415/tcp   Codima Remote Transaction Protocol
//codima-rtp      2415/udp   Codima Remote Transaction Protocol
//#                          Sylvia Ross <sross&codimatech.com>
//rmtserver	2416/tcp   RMT Server	
//rmtserver	2416/udp   RMT Server
//#			   Yvon Marineau <yvon&simware.com>
//composit-server	2417/tcp   Composit Server
//composit-server	2417/udp   Composit Server
//#			   Katsuaki Naoi <naoi&pfu.co.jp>
//cas		2418/tcp   cas
//cas		2418/udp   cas
//#			   Akiyoshi Ochi <akiyoshi&net.paso.fujitsu.co.jp>
//attachmate-s2s	2419/tcp   Attachmate S2S
//attachmate-s2s	2419/udp   Attachmate S2S
//#			   Chris Rominski <ChrisRom&attachmate.com>
//dslremote-mgmt	2420/tcp   DSL Remote Management
//dslremote-mgmt	2420/udp   DSL Remote Management
//#			   Westell, Inc. <jronk&westell.com> 	
//g-talk		2421/tcp   G-Talk
//g-talk		2421/udp   G-Talk
//#			   Matt Hammond <matt_hammond&four-sight.co.uk>
//crmsbits	2422/tcp   CRMSBITS
//crmsbits	2422/udp   CRMSBITS
//#			   Rod Ward <RWard&vaccmel1.telstra.com.au>
//rnrp		2423/tcp   RNRP
//rnrp		2423/udp   RNRP
//#			   Per Sahlqvist <psahlqvi&sw.seisy.abb.se>
//kofax-svr	2424/tcp   KOFAX-SVR
//kofax-svr	2424/udp   KOFAX-SVR
//#			   Terry Reagan <treagan&kofax.com>
//fjitsuappmgr	2425/tcp   Fujitsu App Manager
2425,//fjitsuappmgr	2425/udp   Fujitsu App Manager
//#			   Hiroyuki Kawabuchi <buchi&ael.fujitsu.co.jp>
//#               2426       Unassigned (Removed 2002-04-29)
2427,//mgcp-gateway    2427/tcp   Media Gateway Control Protocol Gateway
//mgcp-gateway    2427/udp   Media Gateway Control Protocol Gateway
//#                          Christian Huitema <huitema&research.telcordia.com>
//ott             2428/tcp   One Way Trip Time
//ott             2428/udp   One Way Trip Time
//#                          Greg Troxel <gdt&ir.bbn.com>
//ft-role		2429/tcp   FT-ROLE
//ft-role		2429/udp   FT-ROLE
//#			   Doug Boone <dboone&atg.CLR.com>
//venus		2430/tcp   venus
//venus		2430/udp   venus
//venus-se	2431/tcp   venus-se
//venus-se	2431/udp   venus-se
//codasrv		2432/tcp   codasrv
//codasrv		2432/udp   codasrv
//codasrv-se	2433/tcp   codasrv-se
//codasrv-se	2433/udp   codasrv-se
//#			   Robert Watson <robert&cyrus.watson.org>
//pxc-epmap	2434/tcp   pxc-epmap
//pxc-epmap	2434/udp   pxc-epmap
//#			   Jun Nakamura <jnakamur&cp10.es.xerox.com>
//optilogic	2435/tcp   OptiLogic
//optilogic	2435/udp   OptiLogic
//#			   Clark Williams <clark&wirespeed.com>
//topx		2436/tcp   TOP/X
//topx		2436/udp   TOP/X
//#			   Dragos Pop <dragos&cs.ubbcluj.ro>
//unicontrol	2437/tcp   UniControl
//unicontrol	2437/udp   UniControl
//#			   Ing. Markus Huemer <markus.huemer&hsd.at>
//msp		2438/tcp   MSP
//msp		2438/udp   MSP
//#			   Evan Caves <evan&acc.com>
//sybasedbsynch	2439/tcp   SybaseDBSynch
//sybasedbsynch	2439/udp   SybaseDBSynch
//#			   Dave Neudoerffer <Dave.Neudoerffer&ianywhere.com>
//spearway	2440/tcp   Spearway Lockers
//spearway	2440/udp   Spearway Lockers
//#			   Pierre Frisch <Pierre.Frisch&spearway.com>
//pvsw-inet       2441/tcp   Pervasive I*net Data Server
//pvsw-inet       2441/udp   Pervasive I*net Data Server
//#                          Chuck Talk <ctalk&pervasive.com>
//netangel	2442/tcp   Netangel
//netangel	2442/udp   Netangel
//#			   Ladislav Baranyay <identcod&identcode.sk>
//powerclientcsf  2443/tcp   PowerClient Central Storage Facility
//powerclientcsf  2443/udp   PowerClient Central Storage Facility
//#			   Brian Klassen <Brian.Klassen&Unisys.com>	
//btpp2sectrans   2444/tcp   BT PP2 Sectrans
//btpp2sectrans   2444/udp   BT PP2 Sectrans
//#                          Ian Daniels <btexact.ports&bt.com> 
//dtn1		2445/tcp   DTN1
//dtn1		2445/udp   DTN1
//#			   Bob Gaddie <bobg&dtn.com> 
//bues_service	2446/tcp   bues_service
//bues_service	2446/udp   bues_service
//#			   Leonhard Diekmann
//#                          <diekmann&04.mstr02.telekom400.dbp.de>
//ovwdb		2447/tcp   OpenView NNM daemon
//ovwdb		2447/udp   OpenView NNM daemon
//#			   Eric Pulsipher <eric_pulsipher&fc.hp.com>
//hpppssvr	2448/tcp   hpppsvr
//hpppssvr	2448/udp   hpppsvr
//#			   Bridgette Landers <blanders&boi.hp.com>
//ratl		2449/tcp   RATL
//ratl		2449/udp   RATL
//#			               Paul Greenfield <paul.greenfield&unisys.com>
//netadmin        2450/tcp   netadmin
//netadmin    	2450/udp   netadmin
//netchat		2451/tcp   netchat
//netchat		2451/udp   netchat
//#			               Julian Mehnle <julian&mehnle.net>
//snifferclient	2452/tcp   SnifferClient
//snifferclient	2452/udp   SnifferClient
//#			               Amy Weaver <amy_weaver&nai.com>
//madge-ltd	2453/tcp   madge ltd
//madge-ltd	2453/udp   madge ltd
//#			               Mark Lyall <mark.lyall&madge.com>
//indx-dds	2454/tcp   IndX-DDS
//indx-dds  	2454/udp   IndX-DDS
//#			               Paul Carmichael <paulcarmichael&indx.net>
//wago-io-system	2455/tcp   WAGO-IO-SYSTEM
//wago-io-system	2455/udp   WAGO-IO-SYSTEM
//#			               J�rg Hoffmann <electronicc_rd&wago.com>
//altav-remmgt	2456/tcp   altav-remmgt
//altav-remmgt	2456/udp   altav-remmgt
//#			               Gary M. Allen <gallen&symantec.com>
//rapido-ip	2457/tcp   Rapido_IP
//rapido-ip       2457/udp   Rapido_IP
//#			               Man Shuen Cheung <man_shuen_cheung&wamnet.co.uk>
//griffin         2458/tcp   griffin
//griffin		2458/udp   griffin
//#			               Tom Taylor <Tom.Taylor&unisys.com>
//community       2459/tcp   Community
//community       2459/udp   Community
//#			               David Schwartz <davids&webmaster.com>
//ms-theater      2460/tcp   ms-theater
//ms-theater      2460/udp   ms-theater
//#                          Anton Kucer <akucer&microsoft.com>
//qadmifoper	2461/tcp   qadmifoper
//qadmifoper	2461/udp   qadmifoper
//qadmifevent	2462/tcp   qadmifevent
//qadmifevent	2462/udp   qadmifevent	
//#			   Pekka Takaranta <pekka.takaranta&tellabs.fi>
//lsi-raid-mgmt   2463/tcp   LSI RAID Management
//lsi-raid-mgmt   2463/udp   LSI RAID Management
//#                          Previous Contact: Bill Delaney <bill.delaney&symbios.com>
//#                          Current Contact: Kevin Copas <Kevin.Copas&lsi.com> 07 February 2008
//direcpc-si	2464/tcp   DirecPC SI
//direcpc-si	2464/udp   DirecPC SI
//#			   Doug Dillon <dillon&hns.com>
//lbm		2465/tcp   Load Balance Management
//lbm		2465/udp   Load Balance Management
//lbf		2466/tcp   Load Balance Forwarding
//lbf		2466/udp   Load Balance Forwarding
//#			   Kazuhiro Koide <kaz&pfu.co.jp>
//high-criteria	2467/tcp   High Criteria
//high-criteria	2467/udp   High Criteria
//#			   Konstantin Iavid <kiavid&highcriteria.com>
//qip-msgd	2468/tcp   qip_msgd
//qip-msgd	2468/udp   qip_msgd
//#			   Mike Morgan <mmorgan&lucent.com>
//mti-tcs-comm	2469/tcp   MTI-TCS-COMM
//mti-tcs-comm	2469/udp   MTI-TCS-COMM
//#			   Mario Bonin <boninm&microtempus.com>
//taskman-port	2470/tcp   taskman port
//taskman-port	2470/udp   taskman port
//#			   Boris Panteleev <bpanteleev&himel.com>
//seaodbc		2471/tcp   SeaODBC
//seaodbc		2471/udp   SeaODBC
//#			   Adrian Hornby <Adrian.Hornby&aran.co.uk>
//c3		2472/tcp   C3
//c3		2472/udp   C3
//#			   Eckhard Grieger <e.grieger&com-on.de>
//aker-cdp	2473/tcp   Aker-cdp
//aker-cdp	2473/udp   Aker-cdp
//#			   Rodrigo Ormonde <ormonde&aker.com.br>
//vitalanalysis	2474/tcp   Vital Analysis
//vitalanalysis	2474/udp   Vital Analysis
//#			   Srinivas Reddy <sreddy&vitalsigns.com>
//ace-server	2475/tcp   ACE Server
//ace-server	2475/udp   ACE Server
//ace-svr-prop	2476/tcp   ACE Server Propagation
//ace-svr-prop	2476/udp   ACE Server Propagation
//ssm-cvs		2477/tcp   SecurSight Certificate Valifation Service
//ssm-cvs		2477/udp   SecurSight Certificate Valifation Service
//ssm-cssps	2478/tcp   SecurSight Authentication Server (SSL)
//ssm-cssps	2478/udp   SecurSight Authentication Server (SSL)
//ssm-els		2479/tcp   SecurSight Event Logging Server (SSL)
//ssm-els		2479/udp   SecurSight Event Logging Server (SSL)
//#			   John Linn <jlinn&securitydynamics.com>
//powerexchange   2480/tcp   Informatica PowerExchange Listener
//powerexchange   2480/udp   Informatica PowerExchange Listener
//#			   Dale Norman <dnorman&informatica.com>
//giop		2481/tcp   Oracle GIOP
//giop		2481/udp   Oracle GIOP
//giop-ssl	2482/tcp   Oracle GIOP SSL
//giop-ssl	2482/udp   Oracle GIOP SSL
//ttc		2483/tcp   Oracle TTC
//ttc		2483/udp   Oracle TTC
//ttc-ssl		2484/tcp   Oracle TTC SSL
//ttc-ssl		2484/udp   Oracle TTC SSL
//#			   Chandar Venkataraman <CVENKATA&us.oracle.com>
//netobjects1	2485/tcp   Net Objects1
//netobjects1	2485/udp   Net Objects1
//netobjects2	2486/tcp   Net Objects2
//netobjects2	2486/udp   Net Objects2
//#			   Francois Granade <francois&netobjects.com>
//pns		2487/tcp   Policy Notice Service
//pns		2487/udp   Policy Notice Service
//#			   Akiyoshi Ochi <akiyoshi&net.paso.fujitsu.co.jp>
//moy-corp	2488/tcp   Moy Corporation
//moy-corp	2488/udp   Moy Corporation
//#			   Gang Gong Moy
//tsilb		2489/tcp   TSILB
//tsilb		2489/udp   TSILB
//#			   James Irwin <jimi&travsoft.com>
//qip-qdhcp	2490/tcp   qip_qdhcp
//qip-qdhcp	2490/udp   qip_qdhcp
//#			   Mike Morgan <mmorgan&lucent.com>
//conclave-cpp	2491/tcp   Conclave CPP
//conclave-cpp	2491/udp   Conclave CPP
//#			   Larry Lipstone <lrl&interdyn.com>
//groove		2492/tcp   GROOVE
//groove		2492/udp   GROOVE
//#			   Ray Ozzie <ray&rocks.net>
//talarian-mqs	2493/tcp   Talarian MQS
//talarian-mqs	2493/udp   Talarian MQS
//#			   Jim Stabile <jstabile&talarian.com>
//bmc-ar		2494/tcp   BMC AR
//bmc-ar		2494/udp   BMC AR
//#			   Portnoy Boxman <portnoy_boxman&bmc.com>
//fast-rem-serv	2495/tcp   Fast Remote Services
//fast-rem-serv	2495/udp   Fast Remote Services
//#			   Scott St. Clair <stclair&NTC.ADAPTEC.com>
//dirgis		2496/tcp   DIRGIS
//dirgis		2496/udp   DIRGIS
//#			   Deutschland Informations- und
//#                          Reservierungsgesellschaft mbH <beratung&dirg.de>
//quaddb		2497/tcp   Quad DB
//quaddb		2497/udp   Quad DB
//#			   Jeff Rosenthal <jrosenthal&quad-sys.com>
//odn-castraq	2498/tcp   ODN-CasTraq
//odn-castraq	2498/udp   ODN-CasTraq
//#			   Richard Hodges <rh&source.net>
//unicontrol	2499/tcp   UniControl
//unicontrol	2499/udp   UniControl
//#			   Ing. Markus Huemer
//rtsserv         2500/tcp   Resource Tracking system server
//rtsserv         2500/udp   Resource Tracking system server
//rtsclient       2501/tcp   Resource Tracking system client
//rtsclient       2501/udp   Resource Tracking system client
//#                          Aubrey Turner
//#                          <S95525ta%etsuacad.bitnet&ETSUADMN.ETSU.EDU>
//kentrox-prot	2502/tcp   Kentrox Protocol
//kentrox-prot	2502/udp   Kentrox Protocol
//#			   Anil Lakhwara <anil_lakhwara&kentrox.com>
//nms-dpnss	2503/tcp   NMS-DPNSS
//nms-dpnss	2503/udp   NMS-DPNSS
//#			   Jean-Christophe Desire
//#			   <Jean-Christophe_Desire&NMS-Europe.com>	
//wlbs		2504/tcp   WLBS 
//wlbs		2504/udp   WLBS 
//#			   William Bain <bbain&microsoft.com>
//ppcontrol       2505/tcp   PowerPlay Control
//ppcontrol       2505/udp   PowerPlay Control
//#                          Max Magliaro <mmagliaro&bnisolutions.com> November 2004
//jbroker		2506/tcp   jbroker
//jbroker		2506/udp   jbroker
//#			   Rohit Garg <rohit&objectScape.com>
//spock		2507/tcp   spock
//spock		2507/udp   spock
//#			   Jon A. Christopher <jac8792&tamu.edu>
//jdatastore	2508/tcp   JDataStore
//jdatastore	2508/udp   JDataStore
//#			   Tod Landis <tlandis&inprise.com>
//fjmpss		2509/tcp   fjmpss
//fjmpss		2509/udp   fjmpss
//#			   Makoto Watanabe <makoto&saint.nm.fujitsu.co.jp>
//fjappmgrbulk	2510/tcp   fjappmgrbulk
//fjappmgrbulk	2510/udp   fjappmgrbulk
//#			   Hiroyuki Kawabuchi <buchi&ael.fujitsu.co.jp>
//metastorm	2511/tcp   Metastorm
//metastorm	2511/udp   Metastorm
//#			   Eric Isom <eisom&metastorm.com>
//citrixima	2512/tcp   Citrix IMA
//citrixima	2512/udp   Citrix IMA
//citrixadmin	2513/tcp   Citrix ADMIN
//citrixadmin	2513/udp   Citrix ADMIN
//#			   Myk Willis <myk.willis&citrix.com>
//facsys-ntp	2514/tcp   Facsys NTP
//facsys-ntp	2514/udp   Facsys NTP
//facsys-router	2515/tcp   Facsys Router
//facsys-router	2515/udp   Facsys Router
//#			   Jeff Hoffman <jeffh&facsys.com>
//maincontrol	2516/tcp   Main Control   
//maincontrol	2516/udp   Main Control   
//#			   Nathan Sadia <sadia&maincontrol.com>	
//call-sig-trans	2517/tcp   H.323 Annex E call signaling transport
//call-sig-trans	2517/udp   H.323 Annex E call signaling transport
//#			   Gur Kimchi <gur.kimchi&vocaltec.com>
//willy		2518/tcp   Willy
//willy		2518/udp   Willy
//#			   Carl-Johan Wik <cjw&hudsmoar.com>
//globmsgsvc	2519/tcp   globmsgsvc
//globmsgsvc	2519/udp   globmsgsvc
//#			   David Wiltz <dwiltz&hf.intel.com>	
//pvsw            2520/tcp   Pervasive Listener
//pvsw            2520/udp   Pervasive Listener
//#                          Chuck Talk <ctalk&pervasive.com>
//adaptecmgr	2521/tcp   Adaptec Manager
//adaptecmgr	2521/udp   Adaptec Manager
//#			   Mark Parenti <map&ntc.adaptec.com>
//windb		2522/tcp   WinDb
//windb		2522/udp   WinDb
//#			   Larry Traylor <larry&arium.com>
//qke-llc-v3      2523/tcp   Qke LLC V.3
//qke-llc-v3      2523/udp   Qke LLC V.3
//#                          Joerg Niehoff <joerg.niehoff&alcatel-ke.de>
//optiwave-lm	2524/tcp   Optiwave License Management
//optiwave-lm	2524/udp   Optiwave License Management
//#			   Slawomir Krzesinski <slavek&optiwave.com>
//ms-v-worlds	2525/tcp   MS V-Worlds 
//ms-v-worlds	2525/udp   MS V-Worlds 
//#			   Pete Wong <petewong&microsoft.com>
//ema-sent-lm	2526/tcp   EMA License Manager
//ema-sent-lm	2526/udp   EMA License Manager
//#			   Thaddeus Perala <trperala&emaden.com>
//iqserver	2527/tcp   IQ Server
//iqserver	2527/udp   IQ Server
//#			   Nick Straguzzi <Nick_Straguzzi&akbs.com>
//ncr_ccl		2528/tcp   NCR CCL
//ncr_ccl		2528/udp   NCR CCL
//#			   Amitava Dutta <Amitava.Dutta&WoodbridgeNJ.ncr.com>
//utsftp		2529/tcp   UTS FTP
//utsftp		2529/udp   UTS FTP
//#			   David Moore <dmoore&uttc-uts.com>
//vrcommerce	2530/tcp   VR Commerce
//vrcommerce	2530/udp   VR Commerce
//#			   Yosi Mass <yosimass&haifa.vnet.ibm.com>
//ito-e-gui	2531/tcp   ITO-E GUI
//ito-e-gui	2531/udp   ITO-E GUI
//#			   Michael Haeuptle <Michael_Haeuptle&hp.com>
//ovtopmd		2532/tcp   OVTOPMD
//ovtopmd		2532/udp   OVTOPMD
//#			   Eric Pulsipher <eric_pulsipher&hp.com>
//snifferserver	2533/tcp   SnifferServer
//snifferserver	2533/udp   SnifferServer
//#			   Amy Weaver <Amy_Weaver&NAI.com>
//combox-web-acc	2534/tcp   Combox Web Access
//combox-web-acc	2534/udp   Combox Web Access
//#		   	   Yochai Cohen <yochai&combox.co.il>
//madcap		2535/tcp   MADCAP
//madcap		2535/udp   MADCAP
//#			   Stephen Hanna <steve.hanna&sun.com>
//btpp2audctr1    2536/tcp   btpp2audctr1
//btpp2audctr1    2536/udp   btpp2audctr1
//#                          Ian Daniels <btexact.ports&bt.com>
//upgrade		2537/tcp   Upgrade Protocol
//upgrade		2537/udp   Upgrade Protocol
//#			   Breck Auten <bauten&dst-inc.com>
//vnwk-prapi	2538/tcp   vnwk-prapi
//vnwk-prapi	2538/udp   vnwk-prapi
//#			   John Hasselkus <Jhasselkus&VisualNetworks.com>
//vsiadmin	2539/tcp   VSI Admin
//vsiadmin	2539/udp   VSI Admin
//#			   Rob Juergens <robj&vsi.com>
//lonworks	2540/tcp   LonWorks
//lonworks	2540/udp   LonWorks
//lonworks2	2541/tcp   LonWorks2
//lonworks2	2541/udp   LonWorks2 
//#			   Gary Bartlett <garyb&echelon.com>
//udrawgraph	2542/tcp   uDraw(Graph)
//udrawgraph	2542/udp   uDraw(Graph)
//#			   University of Bremen, FB3 <udrawgraph&informatik.uni-bremen.de> 
//reftek		2543/tcp   REFTEK
//reftek		2543/udp   REFTEK
//#			   Phil Davidson <p.davidson&reftek.com>
//novell-zen	2544/tcp   Management Daemon Refresh
//novell-zen	2544/udp   Management Daemon Refresh
//#			   Ty Ellis <tellis&novell.com>
//sis-emt		2545/tcp   sis-emt
//sis-emt		2545/udp   sis-emt
//#			   Bill Crawford <Bill.Crawford&securicor.co.uk>
//vytalvaultbrtp  2546/tcp   vytalvaultbrtp
//vytalvaultbrtp	2546/udp   vytalvaultbrtp
//vytalvaultvsmp	2547/tcp   vytalvaultvsmp
//vytalvaultvsmp	2547/udp   vytalvaultvsmp
//vytalvaultpipe	2548/tcp   vytalvaultpipe
//vytalvaultpipe	2548/udp   vytalvaultpipe
//#			   Tim Boldt <timb&vytalnet.com>
//ipass		2549/tcp   IPASS
//ipass		2549/udp   IPASS
//#			   Michael Fischer <otterley&Pass.COM>
//ads		2550/tcp   ADS
//ads		2550/udp   ADS
//#			   Michael O'Connor <moconnor&adobe.com>
//isg-uda-server	2551/tcp   ISG UDA Server
//isg-uda-server	2551/udp   ISG UDA Server
//#			   Dror Harari <Dror.Harari&isgsoft.com>
//call-logging	2552/tcp   Call Logging
//call-logging	2552/udp   Call Logging
//#			   Dean Webb <dean.webb&ascend.com>
//efidiningport	2553/tcp   efidiningport
//efidiningport	2553/udp   efidiningport
//#			   Lynn Carter <carterl&execpc.com>
//vcnet-link-v10	2554/tcp   VCnet-Link v10
//vcnet-link-v10	2554/udp   VCnet-Link v10
//#			   Csaba Mate <mc36&freemail.c3.hu>
//compaq-wcp	2555/tcp   Compaq WCP
//compaq-wcp	2555/udp   Compaq WCP
//#			   Ferruccio Barletta <ferruccio.barletta&compaq.com>
//nicetec-nmsvc	2556/tcp   nicetec-nmsvc
//nicetec-nmsvc	2556/udp   nicetec-nmsvc
//nicetec-mgmt	2557/tcp   nicetec-mgmt
//nicetec-mgmt	2557/udp   nicetec-mgmt
//#                          Joerg Paulus <tech&nicetec.de>	
//pclemultimedia	2558/tcp   PCLE Multi Media
//pclemultimedia	2558/udp   PCLE Multi Media
//#                          Jacob Gsoedl <jgsoedl&pinnaclesys.com>
//lstp		2559/tcp   LSTP
//lstp		2559/udp   LSTP
//#			               Waiki Wright <waiki&us.ibm.com>
//labrat          2560/tcp   labrat
//labrat          2560/udp   labrat
//#                          John Harvey <johnbob&austin.ibm.com>
//mosaixcc        2561/tcp   MosaixCC
//mosaixcc        2561/udp   MosaixCC
//#                          Steven Frare <stevefr&mosaix.com>
//delibo          2562/tcp   Delibo
//delibo          2562/udp   Delibo
//#                          NovaWiz LTD <Moshe&Novawiz.com>
//cti-redwood	2563/tcp   CTI Redwood
//cti-redwood	2563/udp   CTI Redwood
//#			   Songwon Chi <swchi&daou.co.kr>
//hp-3000-telnet  2564/tcp   HP 3000 NS/VT block mode telnet
//#
//coord-svr	2565/tcp   Coordinator Server
//coord-svr	2565/udp   Coordinator Server
//#			   Richard Steiger <steiger&ensemblesoft.com>
//pcs-pcw		2566/tcp   pcs-pcw
//pcs-pcw		2566/udp   pcs-pcw
//#			   W. Jordan Fitzhugh <jfitz&pcare.com>
//clp		2567/tcp   Cisco Line Protocol
//clp		2567/udp   Cisco Line Protocol
//#			   Susan Hinrichs <shinrich&cisco.com>
//spamtrap	2568/tcp   SPAM TRAP
//spamtrap	2568/udp   SPAM TRAP
//#			   Previous Contact: Chuck Bennett <chuck&benatong.com>
//#                          Current Contact: Charles Bennett <bennettc&ohio.edu> 29 August 2008
//sonuscallsig	2569/tcp   Sonus Call Signal
//sonuscallsig	2569/udp   Sonus Call Signal
//#			   Mark Garti <mgarti&sonusnet.com>
//hs-port		2570/tcp   HS Port
//hs-port		2570/udp   HS Port
//#			   Uri Doron <uri&il.netect.com>
//cecsvc		2571/tcp   CECSVC
//cecsvc		2571/udp   CECSVC
//#			   Roger Pao <rpao&corder-eng.com>
//ibp		2572/tcp   IBP
//ibp		2572/udp   IBP
//#			   Jonathan Downes <jonno&activ.net.au>
//trustestablish  2573/tcp   Trust Establish
//trustestablish  2573/udp   Trust Establish
//#                          Yosi Mass <yosimass&haifa.vnet.ibm.com>
//blockade-bpsp   2574/tcp   Blockade BPSP
//blockade-bpsp   2574/udp   Blockade BPSP
//#                          VP - Research & Development <development&blockade.com>
//hl7             2575/tcp   HL7
//hl7             2575/udp   HL7
//#                          Tim Jacobs
//tclprodebugger  2576/tcp   TCL Pro Debugger
//tclprodebugger  2576/udp   TCL Pro Debugger
//scipticslsrvr   2577/tcp   Scriptics Lsrvr
//scipticslsrvr   2577/udp   Scriptics Lsrvr
//#                          Brent Welch <welch&scriptics.com>
//rvs-isdn-dcp	2578/tcp   RVS ISDN DCP
//rvs-isdn-dcp	2578/udp   RVS ISDN DCP
//#			   Michael Zirpel <mbz&rvscom.com>	
//mpfoncl		2579/tcp   mpfoncl
//mpfoncl		2579/udp   mpfoncl
//#			   Itaru Kimura <kimura&kel.fujitsu.co.jp>
//tributary	2580/tcp   Tributary
//tributary	2580/udp   Tributary
//#			   Louis Lu <LouisL&bristol.com>
//argis-te	2581/tcp   ARGIS TE
//argis-te	2581/udp   ARGIS TE
//argis-ds	2582/tcp   ARGIS DS
//argis-ds	2582/udp   ARGIS DS
//#			   John Legh-Page <john.legh-page&argis.com>
//mon		2583/tcp   MON
//mon		2583/udp   MON
//#			   Jim Trocki <trockij&transmeta.com>
//cyaserv		2584/tcp   cyaserv
//cyaserv		2584/udp   cyaserv
//#			   Morgan Jones <mwj&cyasolutions.com>
//netx-server	2585/tcp   NETX Server
//netx-server	2585/udp   NETX Server
//netx-agent	2586/tcp   NETX Agent
//netx-agent	2586/udp   NETX Agent
//#			   Brett Dolecheck <Dolecheck&IPMetrics.com>
//masc		2587/tcp   MASC
//masc		2587/udp   MASC
//#			   Pavlin Ivanov Radoslavov 
//#			   <pavlin&catarina.usc.edu> 
//privilege	2588/tcp   Privilege
//privilege	2588/udp   Privilege
//#			   Gil Hecht <GilH&aks.com>
//quartus-tcl	2589/tcp   quartus tcl
//quartus-tcl	2589/udp   quartus tcl
//#			   Subroto Datta <subrotod&altera.com>
//idotdist	2590/tcp   idotdist
//idotdist	2590/udp   idotdist
//#			   Jason Hunter <jthunter&invino.com>
//maytagshuffle	2591/tcp   Maytag Shuffle
//maytagshuffle	2591/udp   Maytag Shuffle
//#			               Ken Ksiazek <kksiazek&maytag.com
//netrek          2592/tcp   netrek
//netrek          2592/udp   netrek
//#                          Al Guetzlaff aeg&teamquest.com>
//mns-mail	2593/tcp   MNS Mail Notice Service
//mns-mail	2593/udp   MNS Mail Notice Service
//#			   Rumiko Kikuta <kiku&nd.net.fujitsu.co.jp>
//dts		2594/tcp   Data Base Server
//dts		2594/udp   Data Base Server
//#			   Andreas Roene <support&home-online.de>
//worldfusion1	2595/tcp   World Fusion 1
//worldfusion1	2595/udp   World Fusion 1
//worldfusion2	2596/tcp   World Fusion 2
//worldfusion2	2596/udp   World Fusion 2
//#			   World Fusion <net&worldfusion.com>
//homesteadglory	2597/tcp   Homestead Glory
//homesteadglory	2597/udp   Homestead Glory
//#			   John Tokash <jtokash&homestead.com>
//citriximaclient	2598/tcp   Citrix MA Client
//citriximaclient	2598/udp   Citrix MA Client
//#			   Myk Willis <myk.willis&citrix.com>
//snapd           2599/tcp   Snap Discovery
//snapd           2599/udp   Snap Discovery
//#                          Kevin Osborn <kosborn&snapappliance.com>
//hpstgmgr	2600/tcp   HPSTGMGR
//hpstgmgr	2600/udp   HPSTGMGR
//#			   Kevin Collins <kevinc@.cnd.hp.com>
//discp-client	2601/tcp   discp client
//discp-client	2601/udp   discp client
//discp-server	2602/tcp   discp server
//discp-server	2602/udp   discp server
//#			   Peter White <peter_white&3com.com>
//servicemeter	2603/tcp   Service Meter
//servicemeter	2603/udp   Service Meter
//#			   Duncan Hare <Duncan.Hare&synoia.com>
//nsc-ccs		2604/tcp   NSC CCS	
//nsc-ccs		2604/udp   NSC CCS	
//nsc-posa	2605/tcp   NSC POSA
//nsc-posa	2605/udp   NSC POSA
//#			   Tom Findley <tom.findley&networksciences.net>
//netmon		2606/tcp   Dell Netmon
//netmon		2606/udp   Dell Netmon
//connection	2607/tcp   Dell Connection
//connection	2607/udp   Dell Connection
//#			   Sudhir Shetty <Sudhir_Shetty&Dell.com>
//wag-service	2608/tcp   Wag Service
//wag-service	2608/udp   Wag Service
//#			   Gilles Bourquard <gbo&wag.ch>
//system-monitor	2609/tcp   System Monitor 
//system-monitor	2609/udp   System Monitor 
//#			   Greg Robson-Garth <gregr&alphalink.com.au>
//versa-tek	2610/tcp   VersaTek
//versa-tek	2610/udp   VersaTek
//#			   James Kou <Jamesk&versatek.com>
//lionhead	2611/tcp   LIONHEAD
//lionhead	2611/udp   LIONHEAD
//#			   Tim Rance <trance&lionhead.co.uk>
//qpasa-agent	2612/tcp   Qpasa Agent
//qpasa-agent	2612/udp   Qpasa Agent
//#			   Craig Ching <cching&mqsoftware.com> 
//smntubootstrap	2613/tcp   SMNTUBootstrap
//smntubootstrap	2613/udp   SMNTUBootstrap
//#			   Matt Cecile <mattc&metrics.com>
//neveroffline	2614/tcp   Never Offline
//neveroffline	2614/udp   Never Offline
//#			   Dustin Brand <amo&amo.net>
//firepower       2615/tcp   firepower
//firepower       2615/udp   firepower
//#                          Jason Volk <jason&teknidude.com>
//appswitch-emp	2616/tcp   appswitch-emp
//appswitch-emp	2616/udp   appswitch-emp
//#			   Ted Ross <ross&TopLayer.com>
//cmadmin		2617/tcp   Clinical Context Managers
//cmadmin		2617/udp   Clinical Context Managers
//#			   Mark Morwood <markm&sentillion.com>  
//priority-e-com	2618/tcp   Priority E-Com
//priority-e-com	2618/udp   Priority E-Com
//#			   Marcelo Einhorn <marcelo&eshbel.com>
//bruce		2619/tcp   bruce
//bruce		2619/udp   bruce
//#			   Alec Muffett <alecm&sun.com>
//lpsrecommender	2620/tcp   LPSRecommender
//lpsrecommender	2620/udp   LPSRecommender
//#			   Pritham Shetty <pritham&andromedia.com>
//miles-apart	2621/tcp   Miles Apart Jukebox Server
//miles-apart	2621/udp   Miles Apart Jukebox Server
//#			   Michael Rathmann <rathmann_ia&milesinfo.com>
//metricadbc	2622/tcp   MetricaDBC
//metricadbc	2622/udp   MetricaDBC
//#			   Russ Olivant <russ.olivant&metrica.co.uk>
//lmdp		2623/tcp   LMDP
//lmdp		2623/udp   LMDP
//#			   Ken Bailey <kbailey&rockettalk.com>
//aria		2624/tcp   Aria
//aria		2624/udp   Aria
//#			   Logan Bruns <logan&andromedia.com>
//blwnkl-port	2625/tcp   Blwnkl Port
//blwnkl-port	2625/udp   Blwnkl Port
//#			   Weng Chin (Winson) Yung <Winson_Yung&3com.com>
//gbjd816		2626/tcp   gbjd816
//gbjd816		2626/udp   gbjd816
//#			   George Balesta <George.Baletsa&tfn.com>
//moshebeeri	2627/tcp   Moshe Beeri
//moshebeeri	2627/udp   Moshe Beeri
//#			   Moshe Beeri <moshe&whale-com.com>
//dict		2628/tcp   DICT
//dict		2628/udp   DICT
//#			   Rik Faith <faith&cs.unc.edu>
//sitaraserver	2629/tcp   Sitara Server
//sitaraserver	2629/udp   Sitara Server
//sitaramgmt	2630/tcp   Sitara Management
//sitaramgmt	2630/udp   Sitara Management
//sitaradir	2631/tcp   Sitara Dir
//sitaradir	2631/udp   Sitara Dir
//#		  	   Manickam R.Sridhar <msridhar&sitaranetworks.com>
//irdg-post	2632/tcp   IRdg Post
//irdg-post	2632/udp   IRdg Post
//#			   IRdg, Inc. <jtaylor&irdg.com>
//interintelli	2633/tcp   InterIntelli
//interintelli	2633/udp   InterIntelli
//#			   Mike Gagle <MikeG&inter-intelli.com>
//pk-electronics  2634/tcp   PK Electronics
//pk-electronics  2634/udp   PK Electronics
//#			   Seb Ibis <seb_ibis&pkworld.com>
//backburner	2635/tcp   Back Burner
//backburner	2635/udp   Back Burner
//#			   Kevin Teiskoetter <kevint&metacreations.com>
//solve		2636/tcp   Solve
//solve		2636/udp   Solve
//#			   Peter Morrison <peter_morrison&sydney.sterling.com>
//imdocsvc	2637/tcp   Import Document Service
//imdocsvc	2637/udp   Import Document Service
//#			   Zia Bhatti <zia&netright.com>
//sybaseanywhere  2638/tcp   Sybase Anywhere
//sybaseanywhere	2638/udp   Sybase Anywhere
//#			   Dave Neudoerffer <Dave.Neudoerffer&ianywhere.com>
//aminet		2639/tcp   AMInet
//aminet		2639/udp   AMInet
//#			   Alcorn McBride Inc. <jeff&alcorn.com>
//sai_sentlm	2640/tcp   Sabbagh Associates Licence Manager
//sai_sentlm	2640/udp   Sabbagh Associates Licence Manager
//#			   Elias Sabbagh <ehs&sabbagh.com>
//hdl-srv		2641/tcp   HDL Server
//hdl-srv		2641/udp   HDL Server
//#			   David Ely <dely&cnri.reston.va.us>
//tragic		2642/tcp   Tragic
//tragic		2642/udp   Tragic
//#			   Stu Mark <fordii&j51.com>
//gte-samp	2643/tcp   GTE-SAMP
//gte-samp	2643/udp   GTE-SAMP
//#			   Asher Altman <Asher.Altman&GSC.GTE.Com>
//travsoft-ipx-t	2644/tcp   Travsoft IPX Tunnel
//travsoft-ipx-t	2644/udp   Travsoft IPX Tunnel
//#			   Jack Wilson <JackW&travsoft.com>
//novell-ipx-cmd	2645/tcp   Novell IPX CMD
//novell-ipx-cmd	2645/udp   Novell IPX CMD
//#			   Juan Carlos Luciani <jluciani&novell.com>
//and-lm		2646/tcp   AND License Manager
//and-lm		2646/udp   AND License Manager
//#			   Dick van der Sijs <dick&and.nl>
//syncserver	2647/tcp   SyncServer
//syncserver	2647/udp   SyncServer
//#			   Shawn Casey <Shawn.Casey&matrixone.com>
//upsnotifyprot	2648/tcp   Upsnotifyprot
//upsnotifyprot	2648/udp   Upsnotifyprot
//#			   Mario Leboute <leboute&pro.via-rs.com.br>
//vpsipport	2649/tcp   VPSIPPORT
//vpsipport	2649/udp   VPSIPPORT
//#			   Joon Radley <jradley&csir.co.za>
//eristwoguns     2650/tcp   eristwoguns
//eristwoguns     2650/udp   eristwoguns
//#                          Previous contact: NetPro Computing <ports&netpro.com>
//#                          New contacts: Jason Lockett <Jay.Lockett&quest.com> 16 December 2008
//#                          New contacts: Melanie Kacerek <melanie.kacerek&quest.com> 16 December 2008
//ebinsite	2651/tcp   EBInSite
//ebinsite	2651/udp   EBInSite
//#			   Lefteris Kalamaras <lefteris&ebi.com>
//interpathpanel	2652/tcp   InterPathPanel
//interpathpanel	2652/udp   InterPathPanel
//#			   Stephen Misel <steve.misel&interpath.net>
//sonus		2653/tcp   Sonus
//sonus		2653/udp   Sonus
//#			   Mark Garti <mgarti&sonusnet.com>
//corel_vncadmin	2654/tcp   Corel VNC Admin
//corel_vncadmin  2654/udp   Corel VNC Admin
//#			   Oleg Noskov <olegn&corelcomputer.com>
//unglue		2655/tcp   UNIX Nt Glue
//unglue		2655/udp   UNIX Nt Glue
//#			   Peter Santoro <peter&pscomp.com>
//kana		2656/tcp   Kana
//kana		2656/udp   Kana
//#			   Colin Goldstein <Colin&kana.com>
//sns-dispatcher	2657/tcp   SNS Dispatcher
//sns-dispatcher	2657/udp   SNS Dispatcher
//sns-admin	2658/tcp   SNS Admin
//sns-admin	2658/udp   SNS Admin
//sns-query	2659/tcp   SNS Query
//sns-query	2659/udp   SNS Query
//#			   Mary Holstege <holstege&firstfloor.com>
//gcmonitor	2660/tcp   GC Monitor
//gcmonitor	2660/udp   GC Monitor
//#			   Gustavo Rodriguez-Rivera <grr&geodesic.com>
//olhost		2661/tcp   OLHOST
//olhost		2661/udp   OLHOST
//#			   Robert Ripberger <rip&lan-aces.com>
//bintec-capi	2662/tcp   BinTec-CAPI
//bintec-capi	2662/udp   BinTec-CAPI
//bintec-tapi	2663/tcp   BinTec-TAPI
//bintec-tapi	2663/udp   BinTec-TAPI
//#
//patrol-mq-gm	2664/tcp   Patrol for MQ GM
//patrol-mq-gm	2664/udp   Patrol for MQ GM
//patrol-mq-nm	2665/tcp   Patrol for MQ NM
//patrol-mq-nm	2665/udp   Patrol for MQ NM
//#			   Portnoy Boxman <portnoy_boxman&bmc.com>
//extensis	2666/tcp   extensis
//extensis	2666/udp   extensis
//#			   Milton Sagen <msagen&extensis.com>	
//alarm-clock-s	2667/tcp   Alarm Clock Server
//alarm-clock-s	2667/udp   Alarm Clock Server
//alarm-clock-c	2668/tcp   Alarm Clock Client
//alarm-clock-c	2668/udp   Alarm Clock Client
//toad		2669/tcp   TOAD
//toad		2669/udp   TOAD
//#			   Michael Marking <marking&tatanka.com>
//tve-announce	2670/tcp   TVE Announce
//tve-announce	2670/udp   TVE Announce
//#			   Dean Blackketter <dean&corp.webtv.net>
//newlixreg	2671/tcp   newlixreg
//newlixreg	2671/udp   newlixreg
//#			   Jean-Serge Gagnon <jsg&newlix.com>
//nhserver	2672/tcp   nhserver
//nhserver	2672/udp   nhserver
//#			   Adrian Hornby <Adrian.Hornby&aran.co.uk>
//firstcall42	2673/tcp   First Call 42 
//firstcall42	2673/udp   First Call 42 
//#			   Luke Bowen <leb&tfn.com>
//ewnn		2674/tcp   ewnn
//ewnn		2674/udp   ewnn
//#			   Yasunari Yamashita <yamasita&omronsoft.co.jp>
//ttc-etap	2675/tcp   TTC ETAP
//ttc-etap	2675/udp   TTC ETAP
//#			   Daniel Becker <becker2d&ttc.com>
//simslink	2676/tcp   SIMSLink
//simslink	2676/udp   SIMSLink
//#			   Steve Ryckman <iana&simsware.com>
//gadgetgate1way	2677/tcp   Gadget Gate 1 Way
//gadgetgate1way	2677/udp   Gadget Gate 1 Way
//gadgetgate2way	2678/tcp   Gadget Gate 2 Way
//gadgetgate2way	2678/udp   Gadget Gate 2 Way
//#			   Matt Rollins <matt&anybusiness.com>
//syncserverssl	2679/tcp   Sync Server SSL
//syncserverssl	2679/udp   Sync Server SSL
//#			   Shawn Casey <Shawn.Casey&matrixone.com>
//pxc-sapxom	2680/tcp   pxc-sapxom
//pxc-sapxom	2680/udp   pxc-sapxom
//#			   Hideki Kiriyama <kiriyama&cp10.es.xerox.com>
//mpnjsomb	2681/tcp   mpnjsomb
//mpnjsomb	2681/udp   mpnjsomb
//#			   Takenori Miyahara <miyahara&pfu.co.jp>
//#               2682       Removed (2002-04-30)
//ncdloadbalance	2683/tcp   NCDLoadBalance 
//ncdloadbalance	2683/udp   NCDLoadBalance 
//#			   Tim Stevenson <tes&ncd.com>
//mpnjsosv	2684/tcp   mpnjsosv
//mpnjsosv	2684/udp   mpnjsosv
//mpnjsocl	2685/tcp   mpnjsocl
//mpnjsocl	2685/udp   mpnjsocl
//mpnjsomg	2686/tcp   mpnjsomg
//mpnjsomg	2686/udp   mpnjsomg
//#			   Takenori Miyahara <miyahara&pfu.co.jp>
//pq-lic-mgmt	2687/tcp   pq-lic-mgmt
//pq-lic-mgmt	2687/udp   pq-lic-mgmt
//#			   Bob Sledge <bob&pqsystems.com>
//md-cg-http	2688/tcp   md-cf-http
//md-cg-http	2688/udp   md-cf-http
//#			   Lyndon Nerenberg <lyndon&execmail.ca>
//fastlynx	2689/tcp   FastLynx
//fastlynx	2689/udp   FastLynx
//#			   Dave Sewell <dave&sewelldev.com>
//hp-nnm-data	2690/tcp   HP NNM Embedded Database
//hp-nnm-data	2690/udp   HP NNM Embedded Database
//#			   Chris Das <cdas&cnd.hp.com>
//itinternet	2691/tcp   ITInternet ISM Server
//itinternet	2691/udp   ITInternet ISM Server
//#			   Ron Ehli <ron&itinternet.net>
//admins-lms	2692/tcp   Admins LMS
2692,//admins-lms	2692/udp   Admins LMS
//#                          Dagfinn Saether <Dagfinn&admins.com>
//#               2693/tcp   Unassigned (Removed 2004-2-6)
//#               2693/udp   
//#			   
2694,//pwrsevent	2694/tcp   pwrsevent	
//pwrsevent	2694/udp   pwrsevent	
//#			   Yoshinobu Nakamura
//#			   <nakamura&np.lps.cs.fujitsu.co.jp>
//vspread		2695/tcp   VSPREAD
//vspread		2695/udp   VSPREAD
//#			   Sumitake kobayashi
//#			   <kobayashi&np.lps.cs.fujitsu.co.jp>
//unifyadmin      2696/tcp   Unify Admin
//unifyadmin      2696/udp   Unify Admin
//#                          Duane Gibson <ianaportmaster&unify.com>
//oce-snmp-trap   2697/tcp   Oce SNMP Trap Port 
//oce-snmp-trap   2697/udp   Oce SNMP Trap Port 
//#                          Peter Teeuwen <ptee&oce.nl>
//mck-ivpip	2698/tcp   MCK-IVPIP
//mck-ivpip	2698/udp   MCK-IVPIP
//#			   Robert Vincent <bert&mck.com>
//csoft-plusclnt	2699/tcp   Csoft Plus Client
//csoft-plusclnt	2699/udp   Csoft Plus Client
//#			   Nedelcho Stanev <nstanev&csoft.bg>
//tqdata          2700/tcp   tqdata
//tqdata          2700/udp   tqdata
//#                          Al Guetzlaff <aeg&teamquest.com>
//sms-rcinfo	2701/tcp   SMS RCINFO
//sms-rcinfo	2701/udp   SMS RCINFO
//sms-xfer	2702/tcp   SMS XFER
//sms-xfer	2702/udp   SMS XFER
//sms-chat	2703/tcp   SMS CHAT
//sms-chat	2703/udp   SMS CHAT
//sms-remctrl	2704/tcp   SMS REMCTRL
//sms-remctrl	2704/udp   SMS REMCTRL
//#			   Tom Friend <tomfr&microsoft.com>
//sds-admin	2705/tcp   SDS Admin
//sds-admin	2705/udp   SDS Admin
//#			   Don Traub <don.traub&sun.com>
//ncdmirroring	2706/tcp   NCD Mirroring
//ncdmirroring	2706/udp   NCD Mirroring
//#			   Tim Stevenson <tes&ncd.com>
//emcsymapiport	2707/tcp   EMCSYMAPIPORT
//emcsymapiport	2707/udp   EMCSYMAPIPORT
//#			   Bruce Ferjulian <ferjulian_bruce&emc.com>
//banyan-net	2708/tcp   Banyan-Net
//banyan-net	2708/udp   Banyan-Net
//#			   R. Thirumurthy <rtm&banyannetworks.com>
//supermon	2709/tcp   Supermon
//supermon	2709/udp   Supermon
//#			   Ron Minnich <rminnich&acl.lanl.gov>
//sso-service	2710/tcp   SSO Service
//sso-service	2710/udp   SSO Service
//sso-control	2711/tcp   SSO Control
//sso-control	2711/udp   SSO Control
//#			   Axel Kern <axel.kern&betasystems.com>
//aocp		2712/tcp   Axapta Object Communication Protocol
//aocp		2712/udp   Axapta Object Communication Protocol
//#			   Jakob Steen Hansen <jsh&dk.damgaard.com>
//raventbs        2713/tcp   Raven Trinity Broker Service
//raventbs        2713/udp   Raven Trinity Broker Service
//raventdm        2714/tcp   Raven Trinity Data Mover
//raventdm        2714/udp   Raven Trinity Data Mover
//#			   Daniel Sorlov <Daniel&sorlov.com>
//hpstgmgr2	2715/tcp   HPSTGMGR2
//hpstgmgr2	2715/udp   HPSTGMGR2
//#			   Kevin Collins <kevinc&cnd.hp.com>
//inova-ip-disco	2716/tcp   Inova IP Disco
//inova-ip-disco	2716/udp   Inova IP Disco
//#			   Chris Koeritz <ckoeritz&inovacorp.com>
//pn-requester	2717/tcp   PN REQUESTER
//pn-requester	2717/udp   PN REQUESTER
//pn-requester2	2718/tcp   PN REQUESTER 2
//pn-requester2	2718/udp   PN REQUESTER 2
//#			   Portnoy Boxman <portnoy_boxman&bmc.com>
//scan-change	2719/tcp   Scan & Change
//scan-change	2719/udp   Scan & Change
//#			   Alexander Raji <araji&lucent.com>
//wkars		2720/tcp   wkars
//wkars		2720/udp   wkars
//#			   Barry Shelton <bshelton&wirelessknowledge.com>
//smart-diagnose	2721/tcp   Smart Diagnose
//smart-diagnose	2721/udp   Smart Diagnose
//#			   Geoffry Meek <geoff&meek.com>
//proactivesrvr	2722/tcp   Proactive Server
//proactivesrvr	2722/udp   Proactive Server
//#			   Dalit Naor <dalit&il.ibm.com>
//watchdog-nt	2723/tcp   WatchDog NT Protocol
//watchdog-nt	2723/udp   WatchDog NT Protocol
//#			   Glen Sansoucie <gsansoucie&loftware.com>
//qotps		2724/tcp   qotps
//qotps		2724/udp   qotps
//#			   Piotr Parlewicz <pparlewicz&queryobject.com>
//msolap-ptp2     2725/tcp   MSOLAP PTP2
//msolap-ptp2     2725/udp   MSOLAP PTP2
//#                          Cristian Petculescu <cristp&microsoft.com>
//tams            2726/tcp   TAMS
//tams            2726/udp   TAMS
//#                          David Leinbach <dleinbach&jti.bc.ca>
//mgcp-callagent  2727/tcp   Media Gateway Control Protocol Call Agent
//mgcp-callagent  2727/udp   Media Gateway Control Protocol Call Agent
//#                          Christian Huitema <huitema&research.telcordia.com>
//sqdr		2728/tcp   SQDR
//sqdr		2728/udp   SQDR
//#			   Matthew Orzen <standards&starquest.com>
//tcim-control	2729/tcp   TCIM Control
//tcim-control	2729/udp   TCIM Control
//#			   Dean Skelton <mdskel&ftw.rsc.raytheon.com>
//nec-raidplus	2730/tcp   NEC RaidPlus
//nec-raidplus	2730/udp   NEC RaidPlus
//#			   Yusuke Asai <yasai&nw1.file.fc.nec.co.jp>
//fyre-messanger	2731/tcp   Fyre Messanger
//fyre-messanger	2731/udp   Fyre Messagner
//#			   Robert Waters <bobtek&hotmail.com>
//g5m		2732/tcp   G5M
//g5m		2732/udp   G5M
//#			   Graham Klyne <GK&ACM.ORG>
//signet-ctf	2733/tcp   Signet CTF
//signet-ctf	2733/udp   Signet CTF
//#			   Greg Broiles <greg&sac.net>
//ccs-software	2734/tcp   CCS Software 
//ccs-software	2734/udp   CCS Software 
//#			   Bertus Jacobs <bertus&ccs-software.co.za>
//netiq-mc        2735/tcp   NetIQ Monitor Console
//netiq-mc        2735/udp   NetIQ Monitor Console
//#			   Scott Southard <scott.southard&netiq.com>
//radwiz-nms-srv	2736/tcp   RADWIZ NMS SRV
//radwiz-nms-srv	2736/udp   RADWIZ NMS SRV
//#			   Israel Shainert <israels&209.88.177.2>
//srp-feedback	2737/tcp   SRP Feedback
//srp-feedback	2737/udp   SRP Feedback
//#			   Werner Almesberger <Werner.Almesberger&epfl.ch>
//ndl-tcp-ois-gw	2738/tcp   NDL TCP-OSI Gateway
//ndl-tcp-ois-gw	2738/udp   NDL TCP-OSI Gateway
//#			   Martin Norman <martin&ndl.co.uk> 
//tn-timing	2739/tcp   TN Timing
//tn-timing	2739/udp   TN Timing
//#			   Paul Roberts <PaulRoberts&engineer.com>
//alarm		2740/tcp   Alarm
//alarm		2740/udp   Alarm
//#			   Uriy Makasjuk <racer&bfpg.ru>
//tsb		2741/tcp   TSB
//tsb		2741/udp   TSB
//tsb2		2742/tcp   TSB2
//tsb2		2742/udp   TSB2
//#			   Ashish Chatterjee
//#			   <achatterjee&freeway.proxy.lucent.com>
//murx		2743/tcp   murx
//murx		2743/udp   murx
//#			   Thomas Kuiper <tkuiper&inxsoft.net>
//honyaku		2744/tcp   honyaku
//honyaku		2744/udp   honyaku
//#			   Yasunari Yamashita <yamasita&omronsoft.co.jp>
//urbisnet	2745/tcp   URBISNET
//urbisnet	2745/udp   URBISNET
//#			   Urbis.Net Ltd <postmaster&urbis.net>
//cpudpencap	2746/tcp   CPUDPENCAP
//cpudpencap	2746/udp   CPUDPENCAP
//#			   Tamir Zegman <zegman&checkpoint.com>
//fjippol-swrly	2747/tcp
//fjippol-swrly	2747/udp
//fjippol-polsvr	2748/tcp
//fjippol-polsvr	2748/udp
//fjippol-cnsl	2749/tcp
//fjippol-cnsl	2749/udp
//fjippol-port1	2750/tcp
//fjippol-port1	2750/udp
//fjippol-port2	2751/tcp
//fjippol-port2	2751/udp
//#			   Shoichi Tachibana <tatibana&yk.fujitsu.co.jp>
//rsisysaccess	2752/tcp   RSISYS ACCESS
//rsisysaccess	2752/udp   RSISYS ACCESS
//#			   Christophe Besant
//de-spot		2753/tcp   de-spot
//de-spot		2753/udp   de-spot
//#			   Sanjay Parekh <spot&digitalenvoy.net>
//apollo-cc	2754/tcp   APOLLO CC
//apollo-cc	2754/udp   APOLLO CC
//#			   Brand Communications <donovan&brandcomms.com>
//expresspay	2755/tcp   Express Pay
//expresspay	2755/udp   Express Pay
//#			   Ben Higgins <bhiggins&netcom.ca>
//simplement-tie	2756/tcp   simplement-tie
//simplement-tie	2756/udp   simplement-tie
//#			   Tzvika Chumash <tzvikac&netvision.net.il>
//cnrp		2757/tcp   CNRP
//cnrp		2757/udp   CNRP
//#			   Jacob Ulmert <Jacob.Ulmert&se.abb.com>
//apollo-status	2758/tcp   APOLLO Status
//apollo-status	2758/udp   APOLLO Status
//apollo-gms	2759/tcp   APOLLO GMS
//apollo-gms	2759/udp   APOLLO GMS
//#			   Simon Hovell <simonh&brandcomms.com>
//sabams		2760/tcp   Saba MS
//sabams		2760/udp   Saba MS
//#			   Davoud Maha <dmaha&saba.com>
//dicom-iscl	2761/tcp   DICOM ISCL
//dicom-iscl	2761/udp   DICOM ISCL
//dicom-tls	2762/tcp   DICOM TLS
//dicom-tls	2762/udp   DICOM TLS
//#			   Lawrence Tarbox <ltarbox&scr.siemens.com>
//desktop-dna	2763/tcp   Desktop DNA
//desktop-dna	2763/udp   Desktop DNA
//#			   Jon Walker <jwalker&miramarsys.com>
//data-insurance	2764/tcp   Data Insurance
//data-insurance	2764/udp   Data Insurance
//#			   Brent Irwin <birwin&standard.com>
//qip-audup	2765/tcp   qip-audup
//qip-audup	2765/udp   qip-audup
//#			   Mike Morgan <mmorgan&lucent.com>
//compaq-scp	2766/tcp   Compaq SCP
//compaq-scp	2766/udp   Compaq SCP
//#			   Ferruccio Barletta <ferruccio.barletta&compaq.com>
//uadtc		2767/tcp   UADTC
//uadtc		2767/udp   UADTC
//uacs		2768/tcp   UACS
//uacs		2768/udp   UACS
//#			   Vishwas Lele <Vishwas_Lele&appliedis.com>
//exce   	        2769/tcp   eXcE
//exce	        2769/udp   eXcE
//#			   Norm Freedman <normfree&san.rr.com>
//veronica	2770/tcp   Veronica
//veronica	2770/udp   Veronica
//#			   Jonas Oberg <jonas&coyote.org>
//vergencecm	2771/tcp   Vergence CM
//vergencecm	2771/udp   Vergence CM
//#			   Mark Morwood <markm&sentillion.com>
//auris		2772/tcp   auris
//auris		2772/udp   auris
//#			   Francisco Saez Arance <fsaez&tid.es>
//rbakcup1        2773/tcp   RBackup Remote Backup
//rbakcup1        2773/udp   RBackup Remote Backup
//rbakcup2        2774/tcp   RBackup Remote Backup
//rbakcup2        2774/udp   RBackup Remote Backup
//#                          Rob Cosgrove <rob&alice.net>
//smpp		2775/tcp   SMPP
//smpp		2775/udp   SMPP
//#			   Owen Sullivan <owen.sullivan&aldiscon.ie>
//ridgeway1	2776/tcp   Ridgeway Systems & Software
//ridgeway1	2776/udp   Ridgeway Systems & Software
//ridgeway2	2777/tcp   Ridgeway Systems & Software
//ridgeway2	2777/udp   Ridgeway Systems & Software
//#			   Steve Read <sread&ridgeway-sys.com>
//gwen-sonya	2778/tcp   Gwen-Sonya 
//gwen-sonya	2778/udp   Gwen-Sonya 
//#			   Mark Hurst <mhurst&inconnect.com>
//lbc-sync	2779/tcp   LBC Sync
//lbc-sync	2779/udp   LBC Sync
//lbc-control	2780/tcp   LBC Control
//lbc-control	2780/udp   LBC Control
//#			   Keiji Michine <michine&net.paso.fujitsu.co.jp>
//whosells	2781/tcp   whosells
//whosells	2781/udp   whosells
//#			   William Randolph Royere III 
//#                          <william&royere.net>
//everydayrc	2782/tcp   everydayrc
//everydayrc	2782/udp   everydayrc
//#			   Ahti Heinla <ahti&ahti.bluemoon.ee>
//aises		2783/tcp   AISES
//aises		2783/udp   AISES
//#			   Daniel Grazioli <dgrazioli&pgaero.co.uk>
//www-dev         2784/tcp   world wide web - development
//www-dev         2784/udp   world wide web - development
//aic-np          2785/tcp   aic-np
//aic-np          2785/udp   aic-np
//#                          Brad Parker <brad&american.com>
//aic-oncrpc      2786/tcp   aic-oncrpc - Destiny MCD database
//aic-oncrpc      2786/udp   aic-oncrpc - Destiny MCD database
//#                          Brad Parker  <brad&american.com>
//piccolo         2787/tcp   piccolo - Cornerstone Software
//piccolo         2787/udp   piccolo - Cornerstone Software
//#                          Dave Bellivea <DaveBelliveau&corsof.com>
//fryeserv        2788/tcp   NetWare Loadable Module - Seagate Software
//fryeserv        2788/udp   NetWare Loadable Module - Seagate Software
//#                          Joseph LoPilato 
//#                          <Joseph_M_LoPilato&notes.seagate.com>
//media-agent     2789/tcp   Media Agent
//media-agent     2789/udp   Media Agent
//#			   Nitzan Daube <nitzan&brm.com>
//plgproxy	2790/tcp   PLG Proxy
//plgproxy	2790/udp   PLG Proxy
//#			   Charlie Hava <charlieh&aks.com>
//mtport-regist	2791/tcp   MT Port Registrator
//mtport-regist	2791/udp   MT Port Registrator
//#			   Maxim Tseitlin <mtseitlin&iname.com>
//f5-globalsite	2792/tcp   f5-globalsite
//f5-globalsite	2792/udp   f5-globalsite
//#			   Christian Saether <c.saether&f5.com>
//initlsmsad	2793/tcp   initlsmsad
2793,//initlsmsad	2793/udp   initlsmsad
//#			   Kelly Green <green&compaq.com>
//#		2794       Unassigned (Removed 2006-12-04)
2795,//livestats	2795/tcp   LiveStats
//livestats	2795/udp   LiveStats
//#			   Chris Greene <cgreeneOA&avidsports.com>
//ac-tech		2796/tcp   ac-tech
//ac-tech		2796/udp   ac-tech
//#			   Chiming Huang <chuang&ac-tech.com>
//esp-encap	2797/tcp   esp-encap
//esp-encap	2797/udp   esp-encap
//#			   Jorn Sierwald <joern.sierwald&datafellows.com>
//tmesis-upshot	2798/tcp   TMESIS-UPShot
//tmesis-upshot	2798/udp   TMESIS-UPShot
//#			   Brian Schenkenberger <VAXman&TMESIS.COM>
//icon-discover	2799/tcp   ICON Discover
//icon-discover	2799/udp   ICON Discover
//#			   Alexander Falk <falk&icon.at>
//acc-raid	2800/tcp   ACC RAID
//acc-raid	2800/udp   ACC RAID
//#			   Scott St. Clair <stclair&ntc.adaptec.com>
//igcp		2801/tcp   IGCP
//igcp		2801/udp   IGCP
//#			   David Hampson <davidha&codemasters.com>
//veritas-tcp1	2802/tcp   Veritas TCP1
//veritas-udp1	2802/udp   Veritas UDP1
//#			   Russ Thrasher <Russell.Thrasher&veritas.com>
//btprjctrl	2803/tcp   btprjctrl
//btprjctrl	2803/udp   btprjctrl
//#			   Huw Thomas <huw.thomas&bt.com>
//dvr-esm      	2804/tcp   March Networks Digital Video Recorders and Enterprise Service Manager products
//dvr-esm  	2804/udp   March Networks Digital Video Recorders and Enterprise Service Manager products
//#			   Paul Streatch <pstreatch&marchnetworks.com> June 2004
//wta-wsp-s	2805/tcp   WTA WSP-S
//wta-wsp-s	2805/udp   WTA WSP-S
//#			   Sebastien Bury (WAP Forum)
//#			   <sebastien.bury&art.alcatel.fr>
//cspuni		2806/tcp   cspuni
//cspuni		2806/udp   cspuni
//cspmulti	2807/tcp   cspmulti
//cspmulti	2807/udp   cspmulti
//#			   Terumasa Yoneda <yonedat&pfu.co.jp>
//j-lan-p		2808/tcp   J-LAN-P
//j-lan-p		2808/udp   J-LAN-P
//#			   Takeshi Sahara <sahara&jdl.co.jp>
//corbaloc	2809/tcp   CORBA LOC
//corbaloc	2809/udp   CORBA LOC
//#			   Ted McFadden <mcfadden&dstc.edu.au>
//netsteward	2810/tcp   Active Net Steward
//netsteward	2810/udp   Active Net Steward
//#			   Keith Morley <keith&ndl.co.uk>
//gsiftp		2811/tcp   GSI FTP
//gsiftp		2811/udp   GSI FTP
//#			   Von Welch <vwelch&ncsa.uiuc.edu>
//atmtcp		2812/tcp   atmtcp
//atmtcp		2812/udp   atmtcp
//#			   Werner Almesberger <Werner.Almesberger&epfl.ch>
//llm-pass	2813/tcp   llm-pass
//llm-pass	2813/udp   llm-pass
//llm-csv		2814/tcp   llm-csv
//llm-csv		2814/udp   llm-csv
//#			   Glen Sansoucie <glen&llmwin.com>
//lbc-measure	2815/tcp   LBC Measurement
//lbc-measure	2815/udp   LBC Measurement
//lbc-watchdog	2816/tcp   LBC Watchdog
//lbc-watchdog	2816/udp   LBC Watchdog
//#			   Akiyoshi Ochi <akiyoshi&net.paso.fujitsu.co.jp>
//nmsigport	2817/tcp   NMSig Port
//nmsigport	2817/udp   NMSig Port
//#			   Peter Egli <peter.egli&mail.inalp.com>
//rmlnk		2818/tcp   rmlnk
//rmlnk		2818/udp   rmlnk
//fc-faultnotify	2819/tcp   FC Fault Notification
//fc-faultnotify	2819/udp   FC Fault Notification
//#			   Dave Watkins <davew&boi.hp.com>
//univision	2820/tcp   UniVision
//univision	2820/udp   UniVision
//#			   Keith Ansell <KeithA&fastfreenet.com> 
//vrts-at-port    2821/tcp   VERITAS Authentication Service
//vrts-at-port    2821/udp   VERITAS Authentication Service
//#                          Stefan Winkel <stefan&veritas.com>
//ka0wuc		2822/tcp   ka0wuc
//ka0wuc		2822/udp   ka0wuc
//#			   Kit Haskins <kit&ka0wuc.org>
//cqg-netlan	2823/tcp   CQG Net/LAN
//cqg-netlan	2823/udp   CQG Net/LAN
//cqg-netlan-1    2824/tcp   CQG Net/LAN 1
//cqg-netlan-1    2824/udp   CQG Net/Lan 1 
//#			   Jeff Wood <jw&cqg.com>
//#               2825       (unassigned) Possibly assigned
//slc-systemlog	2826/tcp   slc systemlog
//slc-systemlog	2826/udp   slc systemlog
//slc-ctrlrloops	2827/tcp   slc ctrlrloops
//slc-ctrlrloops	2827/udp   slc ctrlrloops
//#			   Erwin Hogeweg <erwin&airtech.demon.nl>
//itm-lm		2828/tcp   ITM License Manager 
//itm-lm		2828/udp   ITM License Manager 
//#			   Portnoy Boxman <portnoy_boxman&bmc.com>
//silkp1		2829/tcp   silkp1
//silkp1		2829/udp   silkp1
//silkp2		2830/tcp   silkp2
//silkp2		2830/udp   silkp2
//silkp3		2831/tcp   silkp3
//silkp3		2831/udp   silkp3
//silkp4		2832/tcp   silkp4
//silkp4		2832/udp   silkp4
//#			   Erik Skyten <eki&silknet.com>
//glishd		2833/tcp   glishd
//glishd		2833/udp   glishd
//#			   Darrell Schiebel <dschieb&cv.nrao.edu>
//evtp		2834/tcp   EVTP
//evtp		2834/udp   EVTP
//evtp-data	2835/tcp   EVTP-DATA
//evtp-data	2835/udp   EVTP-DATA
//#			   Eric Bruno <ebruno&solution-soft.com> 
//catalyst	2836/tcp   catalyst
//catalyst	2836/udp   catalyst
//#			   Garret Tollkuhn <garret&multiviewgroup.com>
//repliweb	2837/tcp   Repliweb
//repliweb	2837/udp   Repliweb
//#			   William Orme <bill&repliweb.com>
//starbot		2838/tcp   Starbot
//starbot		2838/udp   Starbot
//#			           Markus Sabadello <sabadello&starbot.org>
//nmsigport	2839/tcp   NMSigPort
//nmsigport	2839/udp   NMSigPort
//#			           Peter Egli <peter.egli&mail.inalp.com>
//l3-exprt	2840/tcp   l3-exprt
//l3-exprt	2840/udp   l3-exprt
//l3-ranger	2841/tcp   l3-ranger
//l3-ranger	2841/udp   l3-ranger
//l3-hawk		2842/tcp   l3-hawk
//l3-hawk		2842/udp   l3-hawk
//#			            Dolores Scott <dolores.scott&l-3security.com>
//pdnet		2843/tcp   PDnet
//pdnet		2843/udp   PDnet
//#			           Torsten Scheffler <pdnetadmin&pdnet.info>
//bpcp-poll	2844/tcp   BPCP POLL
//bpcp-poll	2844/udp   BPCP POLL
//bpcp-trap	2845/tcp   BPCP TRAP
//bpcp-trap	2845/udp   BPCP TRAP
//#			            Steve Van Duser <steve.vanduser&bestpower.gensig.com>
//aimpp-hello	2846/tcp   AIMPP Hello
//aimpp-hello	2846/udp   AIMPP Hello
//aimpp-port-req	2847/tcp   AIMPP Port Req
//aimpp-port-req	2847/udp   AIMPP Port Req
//#			   Brian Martinicky
//#                          <Brian_Martinicky&automationintelligence.com>
//amt-blc-port	2848/tcp   AMT-BLC-PORT
//amt-blc-port	2848/udp   AMT-BLC-PORT
//#			   Sandra Frulloni <frulloni.amtec&interbusiness.it>
//fxp		2849/tcp   FXP
//fxp		2849/udp   FXP
//#			   Martin Lichtin <lichtin&oanda.com>
//metaconsole	2850/tcp   MetaConsole
//metaconsole	2850/udp   MetaConsole
//#			   Rakesh Mahajan <rmahajan&netaphor-software.com>
//webemshttp	2851/tcp   webemshttp
//webemshttp	2851/udp   webemshttp
//#			   Stephen Tsun <stsun&jetstream.com>
//bears-01	2852/tcp   bears-01
//bears-01	2852/udp   bears-01
//#			   Bruce McKinnon <brucemck&bears.aust.com>
//ispipes		2853/tcp   ISPipes
//ispipes		2853/udp   ISPipes
//#			   Rajesh Nandyalam <rnandyal&emc.com>
//infomover	2854/tcp   InfoMover
//infomover	2854/udp   InfoMover
//#			   Carla Caputo <caputo&emc.com>
//msrp		2855/tcp   MSRP over TCP
//msrp		2855/udp   MSRP
//#			   [RFC4975]
//cesdinv		2856/tcp   cesdinv
//cesdinv		2856/udp   cesdinv
//#			   Yoshiaki Tokumoto <toku&pfu.co.jp>
//simctlp		2857/tcp   SimCtIP
//simctlp		2857/udp   SimCtIP
//#			   Christian Zietz <czietz&gmx.net>
//ecnp		2858/tcp   ECNP
//ecnp		2858/udp   ECNP
//#			   Robert Reimiller <bob&certsoft.com>
//activememory	2859/tcp   Active Memory
//activememory	2859/udp   Active Memory
//#			   Joe Graham <joe&edaconsulting.com>
//dialpad-voice1	2860/tcp   Dialpad Voice 1
//dialpad-voice1	2860/udp   Dialpad Voice 1
//dialpad-voice2	2861/tcp   Dialpad Voice 2
//dialpad-voice2	2861/udp   Dialpad Voice 2
//#			   Wongyu Cho <wgcho&dialpad.com>
//ttg-protocol	2862/tcp   TTG Protocol
//ttg-protocol	2862/udp   TTG Protocol
//#			   Mark Boler <markb&ttgsoftware.com>
//sonardata	2863/tcp   Sonar Data
//sonardata	2863/udp   Sonar Data
//#			   Ian Higginbottom <sonardata&sonardata.com>
//astromed-main	2864/tcp   main 5001 cmd
//astromed-main	2864/udp   main 5001 cmd
//#			   Chris Tate <ctate&astromed.com>
//pit-vpn		2865/tcp   pit-vpn
//pit-vpn		2865/udp   pit-vpn
//#			   Norbert Sendetzky <norbert&linuxnetworks.de>
//iwlistener	2866/tcp   iwlistener
//iwlistener	2866/udp   iwlistener
//#			   Fred Surr <quest_iana&oz.quest.com>
//esps-portal	2867/tcp   esps-portal
//esps-portal	2867/udp   esps-portal
//#			   Nicholas Stowfis <nstowfis&esps.com>
//npep-messaging	2868/tcp   NPEP Messaging
//npep-messaging	2868/udp   NPEP Messaging
//#			   Kristian A. Bognaes <kbo&norman.no>
//icslap		2869/tcp   ICSLAP
//icslap		2869/udp   ICSLAP
//#			   Richard Lamb <rlamb&microsoft.com>
//daishi		2870/tcp   daishi
//daishi		2870/udp   daishi
//#			   Patrick Chipman <pchipman&memphis.edu>
//msi-selectplay	2871/tcp   MSI Select Play
//msi-selectplay	2871/udp   MSI Select Play
//#			   Paul Fonte <paul_fonte&mediastation.com>
//radix		2872/tcp   RADIX
2872,//radix		2872/udp   RADIX
//#			   Stein Roger Skaflotten
//#                          <sskaflot&online.no>
//#               2873       Unassigned (Removed 2003-07-23)
2874,//dxmessagebase1	2874/tcp   DX Message Base Transport Protocol
//dxmessagebase1	2874/udp   DX Message Base Transport Protocol
//dxmessagebase2	2875/tcp   DX Message Base Transport Protocol
//dxmessagebase2	2875/udp   DX Message Base Transport Protocol
//#			   Previous contact: Ozz Nixon <root&delphix.com>
//#                          New contact: G.E. Ozz Nixon Jr. <ozznixon&gmail.com> 13 January 2009
//sps-tunnel	2876/tcp   SPS Tunnel
//sps-tunnel	2876/udp   SPS Tunnel
//#			   Bill McIntosh <bmcintosh&fortresstech.com>
//bluelance	2877/tcp   BLUELANCE
//bluelance	2877/udp   BLUELANCE
//#			   Michael Padrezas <mpaderzas&bluelance.com>
//aap		2878/tcp   AAP
//aap		2878/udp   AAP
//#			   Stephen Hanna <steve.hanna&sun.com>
//ucentric-ds	2879/tcp   ucentric-ds
//ucentric-ds	2879/udp   ucentric-ds
//#			   Alex Vasilevsky <alexv&204.165.216.115>
//synapse		2880/tcp   Synapse Transport
//synapse		2880/udp   Synapse Transport
//#			   Ali Fracyon <sxdev&modulardreams.com>
//ndsp		2881/tcp   NDSP
//ndsp		2881/udp   NDSP
//ndtp		2882/tcp   NDTP
//ndtp		2882/udp   NDTP
//ndnp		2883/tcp   NDNP
//ndnp		2883/udp   NDNP
//#			   Khelben Blackstaff <khelben&gmx.at>
//flashmsg	2884/tcp   Flash Msg
//flashmsg	2884/udp   Flash Msg
//#			   Jeffrey Zinkerman <jeff&zinknet.com>
//topflow		2885/tcp   TopFlow
//topflow		2885/udp   TopFlow
//#			   Ted Ross <ross&toplayer.com>
//responselogic   2886/tcp   RESPONSELOGIC
//responselogic   2886/udp   RESPONSELOGIC
//#			   Bruce Casey <bcasey&responselogic.com>
//aironetddp      2887/tcp   aironet
//aironetddp      2887/udp   aironet
//#			   Victor Griswold <vgris&aironet.com> 	
//spcsdlobby      2888/tcp   SPCSDLOBBY
//spcsdlobby      2888/udp   SPCSDLOBBY
//#			   Matthew Williams <SPCsd_MWDD&hotmail.com> 
//rsom            2889/tcp   RSOM
//rsom            2889/udp   RSOM
//#			   Justine Higgins <iana&corsof.com>
//cspclmulti      2890/tcp   CSPCLMULTI
//cspclmulti      2890/udp   CSPCLMULTI
//#			   Yoneda Terumasa <yonedat&pfu.co.jp>
//cinegrfx-elmd   2891/tcp   CINEGRFX-ELMD License Manager
//cinegrfx-elmd   2891/udp   CINEGRFX-ELMD License Manager
//#			   Greg Ercolano <erco&cinegrfx.com>
//snifferdata     2892/tcp   SNIFFERDATA
//snifferdata     2892/udp   SNIFFERDATA
//#			   Jeff Mangasarian <jeffrey_mangasarian&nai.com>
//vseconnector    2893/tcp   VSECONNECTOR
//vseconnector    2893/udp   VSECONNECTOR
//#			   Ingo Franzki <ifranzki&de.ibm.com>
//abacus-remote   2894/tcp   ABACUS-REMOTE
//abacus-remote   2894/udp   ABACUS-REMOTE
//#			   Mike Bello <mbello&zarak.com>
//natuslink       2895/tcp   NATUS LINK
//natuslink       2895/udp   NATUS LINK
//#			   Jonathan Mergy <mergy&natus.com>
//ecovisiong6-1   2896/tcp   ECOVISIONG6-1
//ecovisiong6-1   2896/udp   ECOVISIONG6-1
//#			   Henrik Holst <henrik.holst&ecovision.se>	
//citrix-rtmp	2897/tcp   Citrix RTMP
//citrix-rtmp	2897/udp   Citrix RTMP
//#			   Myk Willis <myk.willis&citrix.com>
//appliance-cfg   2898/tcp   APPLIANCE-CFG
//appliance-cfg   2898/udp   APPLIANCE-CFG
//#                          Gary A. James <gary.james&criticallink.com>
//powergemplus    2899/tcp   POWERGEMPLUS
//powergemplus    2899/udp   POWERGEMPLUS
//#                          Koich Nakamura <naka&case.nm.fujitsu.co.jp>
//quicksuite      2900/tcp   QUICKSUITE
//quicksuite      2900/udp   QUICKSUITE
//#                          William Egge <begge&emagisoft.com> 
//allstorcns      2901/tcp   ALLSTORCNS
//allstorcns      2901/udp   ALLSTORCNS
//#                          Steve Dobson <sdobson&allstor.com> 
//netaspi         2902/tcp   NET ASPI
//netaspi         2902/udp   NET ASPI
//#                          Johnson Luo <johnson_luo&mail.sercomm.com.tw> 
//suitcase        2903/tcp   SUITCASE
//suitcase        2903/udp   SUITCASE
//#                          Milton E. Sagen <msagen&extensis.com> 
//m2ua            2904/tcp   M2UA
//m2ua            2904/udp   M2UA
//m2ua            2904/sctp  M2UA
//#                          Lyndon Ong <LyOng&ciena.com>
//m3ua            2905/tcp   M3UA
//#               2905/udp   De-registered (2001 June 07)
//m3ua            2905/sctp  M3UA
//#                          Lyndon Ong <LyOng&ciena.com>
//caller9         2906/tcp   CALLER9
//caller9         2906/udp   CALLER9
//#                          Shams Naqi <SSNAQVI&aol.com>
//webmethods-b2b  2907/tcp   WEBMETHODS B2B
//webmethods-b2b  2907/udp   WEBMETHODS B2B
//#                          Joseph Hines <jhines&webmethods.com>
//mao             2908/tcp   mao
//mao             2908/udp   mao
//#                          Marc Baudoin <babafou&babafou.eu.org>
//funk-dialout 	2909/tcp   Funk Dialout
//funk-dialout	2909/udp   Funk Dialout
//#			   Cimarron Boozer <cboozer&funk.com>
//tdaccess	2910/tcp   TDAccess
//tdaccess	2910/udp   TDAccess
//#			   Tom Haapanen <tomh&metrics.com>
//blockade        2911/tcp   Blockade
//blockade        2911/udp   Blockade
//#                          VP - Research & Development <development&blockade.com>
//epicon		2912/tcp   Epicon
//epicon		2912/udp   Epicon
//#			   Michael Khalandovsky <mlk&epicon.com>
//boosterware	2913/tcp   Booster Ware
//boosterware	2913/udp   Booster Ware
//#		 	   Ido Ben-David <dgntcom&netvision.net.il>
//gamelobby       2914/tcp   Game Lobby
//gamelobby       2914/udp   Game Lobby
//#                          Paul Ford-Hutchinson <paulfordh&uk.ibm.com>
//tksocket	2915/tcp   TK Socket
//tksocket	2915/udp   TK Socket
//#                          Previous contact: Alan Fahrner <alan&protix.com>
//#                          Current contact: Alan Fahrner <afahrner&tickets.com> 13 March 2009
//elvin_server	2916/tcp   Elvin Server
//elvin_server	2916/udp   Elvin Server
//elvin_client	2917/tcp   Elvin Client
//elvin_client	2917/udp   Elvin Client
//#			   David Arnold <davida&pobox.com>
//kastenchasepad	2918/tcp   Kasten Chase Pad
//kastenchasepad	2918/udp   Kasten Chase Pad
//#			   Marc Gauthier <mgau&kastenchase.com>
//roboer          2919/tcp   roboER
//roboer          2919/udp   roboER
//#                          Paul Snook <paul.snook&itheon.com>
//roboeda         2920/tcp   roboEDA
//roboeda         2920/udp   roboEDA
//#                          Paul Snook <paul.snook&itheon.com>
//cesdcdman       2921/tcp   CESD Contents Delivery Management
//cesdcdman       2921/udp   CESD Contents Delivery Management
//#                          Shinya Abe <abeabe&pfu.co.jp>
//cesdcdtrn       2922/tcp   CESD Contents Delivery Data Transfer
//cesdcdtrn       2922/udp   CESD Contents Delivery Data Transfer
//#                          Shinya Abe <abeabe&pfu.co.jp> 
//wta-wsp-wtp-s   2923/tcp   WTA-WSP-WTP-S
//wta-wsp-wtp-s   2923/udp   WTA-WSP-WTP-S
//#                          Sebastien Bury (WAP Forum)
//#                          <sebastien.bury&art.alcatel.fr>
//precise-vip     2924/tcp   PRECISE-VIP
2924,//precise-vip     2924/udp   PRECISE-VIP
//#                          Michael Landwehr <mikel&precisesoft.co.il>
//#               2925       Unassigned (FRP-Released 12/7/00)
2926,//mobile-file-dl  2926/tcp   MOBILE-FILE-DL
//mobile-file-dl  2926/udp   MOBILE-FILE-DL
//#                          Mitsuji Toda <toda&mmedia.mci.mei.co.jp>
//unimobilectrl   2927/tcp   UNIMOBILECTRL
//unimobilectrl   2927/udp   UNIMOBILECTRL
//#                          Vikas <vikas&graycell.com>
//redstone-cpss   2928/tcp   REDSTONE-CPSS
//redstone-cpss   2928/udp   REDSTONE-CPSS
//#                          Jeff Looman <jeff&looman.org>
//amx-webadmin    2929/tcp   AMX-WEBADMIN
//amx-webadmin    2929/udp   AMX-WEBADMIN
//#                          Mike Morris <mike.morris&amx.com>
//amx-weblinx     2930/tcp   AMX-WEBLINX
//amx-weblinx     2930/udp   AMX-WEBLINX
//#                          Mike Morris <mike.morris&amx.com>
//circle-x        2931/tcp   Circle-X
//circle-x        2931/udp   Circle-X
//#                          Norm Freedman <normfree&worldnet.att.net>
//incp            2932/tcp   INCP
//incp            2932/udp   INCP
//#                          Keith Paulsen <kpaulsen&phobos.com>
//4-tieropmgw     2933/tcp   4-TIER OPM GW 
//4-tieropmgw     2933/udp   4-TIER OPM GW
//#                          Francois Peloffy <fpeloffy&4tier.com>
//4-tieropmcli    2934/tcp   4-TIER OPM CLI
//4-tieropmcli    2934/udp   4-TIER OPM CLI
//#                          Francois Peloffy <fpeloffy&4tier.com>
//qtp             2935/tcp   QTP
//qtp             2935/udp   QTP
//#                          Cameron Young <Cameron_Young&inetco.com>
//otpatch         2936/tcp   OTPatch
//otpatch         2936/udp   OTPatch
//#                          Brett Goldstein <bgoldstein&opentable.com>
//pnaconsult-lm   2937/tcp   PNACONSULT-LM
//pnaconsult-lm   2937/udp   PNACONSULT-LM
//#                          Theo Nijssen <theon&nijssen.nl>
//sm-pas-1        2938/tcp   SM-PAS-1
//sm-pas-1        2938/udp   SM-PAS-1
//sm-pas-2        2939/tcp   SM-PAS-2
//sm-pas-2        2939/udp   SM-PAS-2
//sm-pas-3        2940/tcp   SM-PAS-3
//sm-pas-3        2940/udp   SM-PAS-3
//sm-pas-4        2941/tcp   SM-PAS-4
//sm-pas-4        2941/udp   SM-PAS-4
//sm-pas-5        2942/tcp   SM-PAS-5
//sm-pas-5        2942/udp   SM-PAS-5
//#                          Tom Haapanen <tomh&metrics.com> 
//ttnrepository   2943/tcp   TTNRepository
//ttnrepository   2943/udp   TTNRepository
//#                          Robert Orr <rorr&teltone.com> 
//megaco-h248     2944/tcp   Megaco H-248
//megaco-h248     2944/udp   Megaco H-248
//#                          Tom Taylor <taylor&nortelnetworks.com> 
//megaco-h248	2944/sctp  Megaco-H.248 text
//#			   Tom Taylor <taylor&nortel.com> September 2006
//h248-binary     2945/tcp   H248 Binary
//h248-binary     2945/udp   H248 Binary
//#                          Tom Taylor <taylor&nortelnetworks.com> 
//h248-binary	2945/sctp  Megaco/H.248 binary
//#			   Tom Taylor <taylor&nortel.com> September 2006
//fjsvmpor        2946/tcp   FJSVmpor
//fjsvmpor        2946/udp   FJSVmpor
//#                          Naoki Hayashi <ha&fjh.se.fujitsu.co.jp>
//gpsd            2947/tcp   GPSD
//gpsd            2947/udp   GPSD
//#                          Derrick J. Brashear <shadow&dementia.org>
//wap-push        2948/tcp   WAP PUSH
//wap-push        2948/udp   WAP PUSH
//wap-pushsecure  2949/tcp   WAP PUSH SECURE
//wap-pushsecure  2949/udp   WAP PUSH SECURE
//#                          WAP FORUM <wap-feedback&mail.wapforum.org>
//esip            2950/tcp   ESIP
//esip            2950/udp   ESIP
//#                          David Stephenson <david_stephenson&hp.com>
//ottp            2951/tcp   OTTP
//ottp            2951/udp   OTTP
//#                          Brent Foster <brent.foster&onstreamsystems.com>
//mpfwsas         2952/tcp   MPFWSAS
//mpfwsas         2952/udp   MPFWSAS
//#                          Toru Murai <murai&saint.nm.fujitsu.co.jp>
//ovalarmsrv      2953/tcp   OVALARMSRV
//ovalarmsrv      2953/udp   OVALARMSRV
//ovalarmsrv-cmd  2954/tcp   OVALARMSRV-CMD
//ovalarmsrv-cmd  2954/udp   OVALARMSRV-CMD
//#                          Eric Pulsipher <eric_pulsipher&hp.com>
//csnotify        2955/tcp   CSNOTIFY
//csnotify        2955/udp   CSNOTIFY
//#                          Israel Beniaminy <israel.beniaminy&clickservice.com>
//ovrimosdbman    2956/tcp   OVRIMOSDBMAN
//ovrimosdbman    2956/udp   OVRIMOSDBMAN
//#                          Dimitrios Souflis <dsouflis&altera.gr>
//jmact5          2957/tcp   JAMCT5
//jmact5          2957/udp   JAMCT5
//jmact6          2958/tcp   JAMCT6
//jmact6          2958/udp   JAMCT6
//rmopagt         2959/tcp   RMOPAGT
//rmopagt         2959/udp   RMOPAGT
//#                          Shuji Okubo <okubo&yk.fujitsu.co.jp>
//dfoxserver      2960/tcp   DFOXSERVER
//dfoxserver      2960/udp   DFOXSERVER
//#                          David Holden <mdh&rentek.net>
//boldsoft-lm     2961/tcp   BOLDSOFT-LM
//boldsoft-lm     2961/udp   BOLDSOFT-LM
//#                          Fredrik Haglund <fredik.haglund&boldsoft.com>
//iph-policy-cli  2962/tcp   IPH-POLICY-CLI
//iph-policy-cli  2962/udp   IPH-POLICY-CLI
//iph-policy-adm  2963/tcp   IPH-POLICY-ADM
//iph-policy-adm  2963/udp   IPH-POLICY-ADM
//#                          Shai Herzog <herzog&iphighway.com>
//bullant-srap    2964/tcp   BULLANT SRAP
//bullant-srap    2964/udp   BULLANT SRAP
//bullant-rap     2965/tcp   BULLANT RAP
//bullant-rap     2965/udp   BULLANT RAP
//#                          Michael Cahill <Michael.Cahill&bullant.net>
//idp-infotrieve  2966/tcp   IDP-INFOTRIEVE
//idp-infotrieve  2966/udp   IDP-INFOTRIEVE
//#                          Kevin Bruckert <kbruckert&idpco.com> 
//ssc-agent       2967/tcp   SSC-AGENT
//ssc-agent       2967/udp   SSC-AGENT
//#                          George Dzieciol <gdzieciol&symantec.com>   
//enpp            2968/tcp   ENPP
//enpp            2968/udp   ENPP
//#                          Kazuhito Gassho <Gassho.Kasuhito&exc.epson.co.jp>
//essp            2969/tcp   ESSP
//essp            2969/udp   ESSP
//#                          Hitoshi Ishida <ishida.hitoshi&exc.epson.co.jp>
//index-net       2970/tcp   INDEX-NET
//index-net       2970/udp   INDEX-NET
//#                          Chris J. Wren <C.Wren&lucent.com>
//netclip         2971/tcp   NetClip clipboard daemon
//netclip         2971/udp   NetClip clipboard daemon
//#                          Rudi Chiarito <nutello&sweetness.com>
//pmsm-webrctl	2972/tcp   PMSM Webrctl
//pmsm-webrctl	2972/udp   PMSM Webrctl
//#			   Markus Michels <mmi&pmsmicado.com>
//svnetworks	2973/tcp   SV Networks
//svnetworks	2973/udp   SV Networks
//#			   Sylvia Siu <ssiu&svnetworks.com>
//signal		2974/tcp   Signal
//signal		2974/udp   Signal
//#			   Wyatt Williams <wyattw&icall.com>
//fjmpcm		2975/tcp   Fujitsu Configuration Management Service
//fjmpcm		2975/udp   Fujitsu Configuration Management Service
//#			   Hiroki Kawano <kawano&saint.nm.fujitsu.co.jp>
//cns-srv-port	2976/tcp   CNS Server Port
//cns-srv-port	2976/udp   CNS Server Port
//#			   Ram Golla <rgolla&cisco.com>
//ttc-etap-ns	2977/tcp   TTCs Enterprise Test Access Protocol - NS
//ttc-etap-ns	2977/udp   TTCs Enterprise Test Access Protocol - NS
//ttc-etap-ds	2978/tcp   TTCs Enterprise Test Access Protocol - DS
//ttc-etap-ds	2978/udp   TTCs Enterprise Test Access Protocol - DS
//#			   Daniel Becker <beckerd&ttc.com>
//h263-video	2979/tcp   H.263 Video Streaming 
//h263-video	2979/udp   H.263 Video Streaming 
//#			   Jauvane C. de Oliveira <jauvane&acm.org>
//wimd		2980/tcp   Instant Messaging Service
//wimd		2980/udp   Instant Messaging Service
//#			   Kevin Birch <kbirch&pobox.com>
//mylxamport	2981/tcp   MYLXAMPORT
//mylxamport	2981/udp   MYLXAMPORT
//#			   Wei Gao <wei&mylex.com>
//iwb-whiteboard  2982/tcp   IWB-WHITEBOARD
//iwb-whiteboard  2982/udp   IWB-WHITEBOARD
//#                          David W. Radcliffe <info&radsolution.co.uk>
//netplan         2983/tcp   NETPLAN
//netplan         2983/udp   NETPLAN
//#                          Thomas Driemeyer <thomas&bitrot.de>
//hpidsadmin      2984/tcp   HPIDSADMIN
//hpidsadmin      2984/udp   HPIDSADMIN
//hpidsagent      2985/tcp   HPIDSAGENT
//hpidsagent      2985/udp   HPIDSAGENT
//#                          John Trudeau <jtrudeau&cup.hp.com>
//stonefalls      2986/tcp   STONEFALLS
//stonefalls      2986/udp   STONEFALLS
//#                          Scott Grau <sgrau&stonefalls.com>
//identify        2987/tcp   identify
//identify        2987/udp   identify
//hippad          2988/tcp   HIPPA Reporting Protocol
//hippad          2988/udp   HIPPA Reporting Protocol
//#                          William Randolph Royere III 
//#                          <william&royere.net>
//zarkov          2989/tcp   ZARKOV Intelligent Agent Communication
//zarkov          2989/udp   ZARKOV Intelligent Agent Communication
//#                          Robin Felix <zarkov_port&zarkov.com>
//boscap          2990/tcp   BOSCAP
//boscap          2990/udp   BOSCAP
//#                          Dirk Hillbrecht <dirk&hillbrecht.de>
//wkstn-mon       2991/tcp   WKSTN-MON
//wkstn-mon       2991/udp   WKSTN-MON
//#                          William David <william.david&lmco.com>
//itb301          2992/tcp   ITB301
//itb301          2992/udp   ITB301
//#                          Bodo Rueskamp <br&itchigo.com> 
//veritas-vis1    2993/tcp   VERITAS VIS1
//veritas-vis1    2993/udp   VERITAS VIS1
//veritas-vis2    2994/tcp   VERITAS VIS2
//veritas-vis2    2994/udp   VERITAS VIS2
//#                          Dinkar Chivaluri <dinkar&veritas.com>
//idrs            2995/tcp   IDRS
//idrs            2995/udp   IDRS
//#                          Jeff Eaton <jeaton&intermec.com>
//vsixml   	2996/tcp   vsixml
//vsixml  	2996/udp   vsixml
//#		           Rob Juergens <robj&vsi.com>
//rebol		2997/tcp   REBOL
//rebol           2997/udp   REBOL
//#                          Holger Kruse <holger&rebol.net>
//realsecure	2998/tcp   Real Secure
2998,//realsecure	2998/udp   Real Secure
//#		           Wes Wilson <wwilson&iss.net>
//remoteware-un	2999/tcp   RemoteWare Unassigned
//remoteware-un	2999/udp   RemoteWare Unassigned
//#			   Tim Farley <Tim.Farley&xcellenet.com>
3000,//hbci            3000/tcp   HBCI
//hbci            3000/udp   HBCI
//#                          Kurt Haubner <haubner&ibm.net>
//# The following entry records an unassigned but widespread use
//remoteware-cl   3000/tcp   RemoteWare Client
3000,//remoteware-cl   3000/udp   RemoteWare Client
//#                          Tim Farley <Tim.Farley&xcellenet.com>
//#		3001	   Unassigned (Removed 2006-05-25)
3002,//exlm-agent      3002/tcp   EXLM Agent
//exlm-agent      3002/udp   EXLM Agent
//#                          Randy Martin <exlmoc&clemson.edu>
//# The following entry records an unassigned but widespread use
//remoteware-srv  3002/tcp   RemoteWare Server
//remoteware-srv  3002/udp   RemoteWare Server
//#                          Tim Farley <Tim.Farley&xcellenet.com>
//cgms            3003/tcp   CGMS
//cgms            3003/udp   CGMS
//#                          Jim Mazzonna <jmazzonna&tiscom.uscg.mil>
//csoftragent     3004/tcp   Csoft Agent
//csoftragent     3004/udp   Csoft Agent
//#                          Nedelcho Stanev <decho&csoft.bg>
//geniuslm        3005/tcp   Genius License Manager
//geniuslm        3005/udp   Genius License Manager
//#                          Jakob Spies <Jakob.Spies&genius.de>
//ii-admin        3006/tcp   Instant Internet Admin
//ii-admin        3006/udp   Instant Internet Admin
//#                          Lewis Donzis <ldonzis&nortelnetworks.com>
//lotusmtap       3007/tcp   Lotus Mail Tracking Agent Protocol
//lotusmtap       3007/udp   Lotus Mail Tracking Agent Protocol
//#                          Ken Lin <klin&us.ibm.com>
//midnight-tech   3008/tcp   Midnight Technologies
//midnight-tech   3008/udp   Midnight Technologies
//#                          Kyle Unice <kyle&midnighttech.com>
//pxc-ntfy        3009/tcp   PXC-NTFY
//pxc-ntfy        3009/udp   PXC-NTFY
//#                          Takeshi Nishizawa <takeshi&cp10.es.xerox.com>
//gw              3010/tcp   Telerate Workstation
//ping-pong       3010/udp   Telerate Workstation
//#                          Timo Sivonen <timo.sivonen&ccmail.dowjones.com>
//trusted-web     3011/tcp   Trusted Web
//trusted-web     3011/udp   Trusted Web
//twsdss          3012/tcp   Trusted Web Client
//twsdss          3012/udp   Trusted Web Client
//#                          Alex Duncan <alex.duncan&sse.ie>
//gilatskysurfer  3013/tcp   Gilat Sky Surfer
//gilatskysurfer  3013/udp   Gilat Sky Surfer
//#                          Yossi Gal <yossi&gilat.com>
//broker_service  3014/tcp   Broker Service
//broker_service  3014/udp   Broker Service
//#                          Dale Bethers <dbethers&novell.com>
//nati-dstp       3015/tcp   NATI DSTP
//nati-dstp       3015/udp   NATI DSTP
//#                          Paul Austin <paul.austin&natinst.com>
//notify_srvr     3016/tcp   Notify Server
//notify_srvr     3016/udp   Notify Server
//#                          Hugo Parra <hparra&novell.com>
//event_listener  3017/tcp   Event Listener
//event_listener  3017/udp   Event Listener
//#                          Ted Tronson <ttronson&novell.com>
//srvc_registry   3018/tcp   Service Registry
//srvc_registry   3018/udp   Service Registry
//#                          Mark Killgore <MKillgore&novell.com>
//resource_mgr    3019/tcp   Resource Manager
//resource_mgr    3019/udp   Resource Manager
//#                          Gary Glover <gglover&novell.com>
//cifs            3020/tcp   CIFS
//cifs            3020/udp   CIFS
//#                          Paul Leach <paulle&microsoft.com>
//agriserver      3021/tcp   AGRI Server
//agriserver      3021/udp   AGRI Server
//#                          Frank Neulichedl <frank&websmile.com>
//csregagent      3022/tcp   CSREGAGENT
//csregagent      3022/udp   CSREGAGENT
//#                          Nedelcho Stanev <nstanev&csoft.bg>
//magicnotes      3023/tcp   magicnotes
//magicnotes      3023/udp   magicnotes
//#                          Karl Edwall <karl&magicnotes.com>	
//nds_sso	        3024/tcp   NDS_SSO
//nds_sso         3024/udp   NDS_SSO
//#                          Mel Oyler <mel&novell.com>
//arepa-raft      3025/tcp   Arepa Raft 
//arepa-raft      3025/udp   Arepa Raft 
//#                          Stuart Schaefer <sschaefer&softricity.com>
//agri-gateway    3026/tcp   AGRI Gateway
//agri-gateway    3026/udp   AGRI Gateway
//#                          Agri Datalog <contact&agri-datalog.com>
//LiebDevMgmt_C   3027/tcp   LiebDevMgmt_C
//LiebDevMgmt_C   3027/udp   LiebDevMgmt_C
//LiebDevMgmt_DM  3028/tcp   LiebDevMgmt_DM
//LiebDevMgmt_DM  3028/udp   LiebDevMgmt_DM
//LiebDevMgmt_A   3029/tcp   LiebDevMgmt_A
//LiebDevMgmt_A   3029/udp   LiebDevMgmt_A
//#                          Mike Velten <Mike_Velten&Liebert.com>
//arepa-cas       3030/tcp   Arepa Cas
//arepa-cas       3030/udp   Arepa Cas
//#                          Stuart Schaefer <sschaefer&softricity.com>
//eppc            3031/tcp   Remote AppleEvents/PPC Toolbox
//eppc            3031/udp   Remote AppleEvents/PPC Toolbox
//#                          Steve Zellers <zellers&apple.com>
//redwood-chat    3032/tcp   Redwood Chat
//redwood-chat    3032/udp   Redwood Chat
//#                          Songwon Chi <swchi&daou.co.kr>
//pdb             3033/tcp   PDB
//pdb             3033/udp   PDB
//#                          Don Bowman <don&pixstream.com>
//osmosis-aeea    3034/tcp   Osmosis / Helix (R) AEEA Port
//osmosis-aeea    3034/udp   Osmosis / Helix (R) AEEA Port
//#                          Larry Atkin <latkin&commongrnd.com>	
//fjsv-gssagt     3035/tcp   FJSV gssagt
//fjsv-gssagt     3035/udp   FJSV gssagt
//#                          Tomoji Koike <koike&ael.fujitsu.co.jp>	
//hagel-dump      3036/tcp   Hagel DUMP
//hagel-dump      3036/udp   Hagel DUMP
//#                          Haim Gelfenbeyn <haim&hageltech.com>
//hp-san-mgmt     3037/tcp   HP SAN Mgmt
//hp-san-mgmt     3037/udp   HP SAN Mgmt
//#                          Steve Britt <steve_britt&hp.com>
//santak-ups      3038/tcp   Santak UPS
//santak-ups      3038/udp   Santak UPS
//#                          Tom Liu <ssc&sc.stk.com.cn>
//cogitate        3039/tcp   Cogitate, Inc.
//cogitate        3039/udp   Cogitate, Inc.
//#                          Jim Harlan <jimh&infowest.com> 
//tomato-springs  3040/tcp   Tomato Springs
//tomato-springs  3040/udp   Tomato Springs
//#                          Jack Waller III <jack&tomatosprings.com>
//di-traceware    3041/tcp   di-traceware
//di-traceware    3041/udp   di-traceware
//#                          Carlos Hung <chung&digisle.net>
//journee         3042/tcp   journee
//journee         3042/udp   journee
//#                          Kevin Calman <postmaster&journee.com>	
//brp             3043/tcp   Broadcast Routing Protocol
//brp             3043/udp   Broadcast Routing Protocol
//#                          John Border <border&hns.com>
//epp             3044/tcp   EndPoint Protocol
//epp             3044/udp   EndPoint Protocol
//#                          Stephen Cipolli <scipolli&radvision.com> 
//responsenet     3045/tcp   ResponseNet
//responsenet     3045/udp   ResponseNet
//#                          Chul Yoon <cyoon&responsenetworks.com>
//di-ase          3046/tcp   di-ase
//di-ase          3046/udp   di-ase
//#                          Carlos Hung <chung&digisle.net>
//hlserver        3047/tcp   Fast Security HL Server
//hlserver        3047/udp   Fast Security HL Server
//#                          Michael Zunke <mzunke&fast-ag.de>
//pctrader        3048/tcp   Sierra Net PC Trader
//pctrader        3048/udp   Sierra Net PC Trader
//#                          Chris Hahn <chrish&sierra.net>
//nsws            3049/tcp   NSWS
//nsws            3049/udp   NSWS
//#                          Ray Gwinn <p00321&psilink.com>
//gds_db          3050/tcp   gds_db
//gds_db          3050/udp   gds_db
//#                          Madhukar N. Thakur <mthakur&interbase.com>	
//galaxy-server	3051/tcp   Galaxy Server
//galaxy-server	3051/udp   Galaxy Server
//#			   Michael Andre <mandre&gts-tkts.com>
//apc-3052        3052/tcp   APC 3052
//apc-3052        3052/udp   APC 3052
//#                          American Power Conversion <ports&apcc.com>
//dsom-server	3053/tcp   dsom-server
//dsom-server	3053/udp   dsom-server
//#			   Daniel Sisk <daniel.sisk&pnl.gov> 
//amt-cnf-prot	3054/tcp   AMT CNF PROT
//amt-cnf-prot	3054/udp   AMT CNF PROT
//#			   Marco Marcucci <mmarcucci.amtec&interbusiness.it>
//policyserver	3055/tcp   Policy Server
//policyserver	3055/udp   Policy Server
//#			   Mark Garti <mgarti&sonusnet.com>
//cdl-server	3056/tcp   CDL Server
//cdl-server	3056/udp   CDL Server
//#			   Paul Roberts <PaulRoberts&engineer.com>
//goahead-fldup	3057/tcp   GoAhead FldUp
//goahead-fldup	3057/udp   GoAhead FldUp
//#			   Alan Pickrell <alanp&goahead.com>
//videobeans	3058/tcp   videobeans
//videobeans	3058/udp   videobeans
//#			   Hiroyuki Takahashi <hiro.takahashi&eng.Sun.COM>
//qsoft		3059/tcp   qsoft
//qsoft		3059/udp   qsoft
//#			   James Kunz <jkunz&earlhaig.com>
//interserver	3060/tcp   interserver
//interserver	3060/udp   interserver
//#			   Madhukar N. Thakur <mthakur&interbase.com>
//cautcpd		3061/tcp   cautcpd
//cautcpd		3061/udp   cautcpd
//ncacn-ip-tcp	3062/tcp   ncacn-ip-tcp
//ncacn-ip-tcp	3062/udp   ncacn-ip-tcp
//ncadg-ip-udp	3063/tcp   ncadg-ip-udp
//ncadg-ip-udp    3063/udp   ncadg-ip-udp
//#			   Gabi Kalmar <kalga01&cai.com>
//rprt            3064/tcp   Remote Port Redirector
//rprt            3064/udp   Remote Port Redirector
//#                          Robin Johnston <robinj&learningtree.com>
//slinterbase	3065/tcp   slinterbase
//slinterbase	3065/udp   slinterbase
//#			   Bie Tie <stie&interbase.com>
//netattachsdmp   3066/tcp   NETATTACHSDMP
//netattachsdmp   3066/udp   NETATTACHSDMP
//#                          Mike Young <myong&netattach.com>
//fjhpjp          3067/tcp   FJHPJP
//fjhpjp          3067/udp   FJHPJP
//#                          Ryozo Furutani <furutani&np.lps.cs.fujitsu.co.jp>
//ls3bcast     	3068/tcp   ls3 Broadcast
//ls3bcast	3068/udp   ls3 Broadcast
//ls3  		3069/tcp   ls3
//ls3  		3069/udp   ls3
//#                          Jim Thompson <jim.thompson&powerware.com> 
//mgxswitch       3070/tcp   MGXSWITCH
//mgxswitch       3070/udp   MGXSWITCH
//#                          George Walter <george.walter&ascentialsoftware.com>
//csd-mgmt-port	3071/tcp   ContinuStor Manager Port
//csd-mgmt-port   3071/udp   ContinuStor Manager Port
//csd-monitor     3072/tcp   ContinuStor Monitor Port
//csd-monitor     3072/udp   ContinuStor Monitor Port
//#                          Ray Jantz <ray.jantz&lsil.com>
//vcrp            3073/tcp   Very simple chatroom prot
//vcrp            3073/udp   Very simple chatroom prot
//#                          Andreas Wurf <a.wurf&mediaTools.de> 
//xbox            3074/tcp   Xbox game port
//xbox            3074/udp   Xbox game port
//#                          Damon Danieli <damond&microsoft.com>
//orbix-locator   3075/tcp   Orbix 2000 Locator
//orbix-locator   3075/udp   Orbix 2000 Locator
//orbix-config    3076/tcp   Orbix 2000 Config
//orbix-config    3076/udp   Orbix 2000 Config
//orbix-loc-ssl   3077/tcp   Orbix 2000 Locator SSL
//orbix-loc-ssl   3077/udp   Orbix 2000 Locator SSL
//orbix-cfg-ssl   3078/tcp   Orbix 2000 Locator SSL
//orbix-cfg-ssl   3078/udp   Orbix 2000 Locator SSL
//#                          Eric Newcomer <eric.newcomer&iona.com>
//lv-frontpanel   3079/tcp   LV Front Panel
//lv-frontpanel   3079/udp   LV Front Panel
//#                          Darshan Shah <darshan.shah&ni.com>
//stm_pproc	3080/tcp   stm_pproc
//stm_pproc	3080/udp   stm_pproc
//#			   Paul McGinnis <pmcginnis&server.stmi.com>
//tl1-lv		3081/tcp   TL1-LV
//tl1-lv		3081/udp   TL1-LV
//tl1-raw		3082/tcp   TL1-RAW
//tl1-raw		3082/udp   TL1-RAW
//tl1-telnet	3083/tcp   TL1-TELNET
//tl1-telnet	3083/udp   TL1-TELNET
//#			   SONET Internetworking Forum (SIF)
//#			   <bwarijsman&lucent.com> - SONET Contact
//itm-mccs        3084/tcp   ITM-MCCS
//itm-mccs        3084/udp   ITM-MCCS
//#                          Portnoy Boxman <portnoy_boxman&bmc.com>
//pcihreq         3085/tcp   PCIHReq
//pcihreq         3085/udp   PCIHReq
//#                          Paul Sanders <p.sanders&dial.pipex.com>
//jdl-dbkitchen   3086/tcp   JDL-DBKitchen
//jdl-dbkitchen   3086/udp   JDL-DBKitchen
//#                          Hideo Wakabayashi <hiwaka&alles.or.jp>
//asoki-sma	3087/tcp   Asoki SMA
//asoki-sma       3087/udp   Asoki SMA
//#                          Andrew Mossberg <amossberg&asoki.net>     
//xdtp            3088/tcp   eXtensible Data Transfer Protocol
//xdtp            3088/udp   eXtensible Data Transfer Protocol
//#                          Michael Shearson <mshearson&peerglobal.com>    
//ptk-alink       3089/tcp   ParaTek Agent Linking
//ptk-alink       3089/udp   ParaTek Agent Linking
//#                          Robert Hodgson <robert&paratek.co.uk> 
//stss            3090/tcp   Senforce Session Services
//stss            3090/udp   Senforce Session Services
//#                          Peter Boucher <pboucher&senforce.com>
//1ci-smcs        3091/tcp   1Ci Server Management
3091,//1ci-smcs        3091/udp   1Ci Server Management
//#                          Ralf Bensmann <iana&1ci.de>
//#               3092       Unassigned (Returned 2008-04-22)
3093,//rapidmq-center  3093/tcp   Jiiva RapidMQ Center
//rapidmq-center  3093/udp   Jiiva RapidMQ Center
//rapidmq-reg     3094/tcp   Jiiva RapidMQ Registry
//rapidmq-reg     3094/udp   Jiiva RapidMQ Registry
//#                          Mark Ericksen <mark&jiiva.com>
//panasas         3095/tcp   Panasas rendevous port
//panasas         3095/udp   Panasas rendevous port
//#                          Peter Berger <peterb&panasas.com>
//ndl-aps         3096/tcp   Active Print Server Port
//ndl-aps         3096/udp   Active Print Server Port
//#                          Martin Norman <martin&ndl.co.uk> 
//#               3097/tcp   Reserved
//#               3097/udp   Reserved
//itu-bicc-stc    3097/sctp  ITU-T Q.1902.1/Q.2150.3
//#                          Greg Sidebottom <gregside&home.com>
//umm-port        3098/tcp   Universal Message Manager
//umm-port        3098/udp   Universal Message Manager
//#                          Phil Braham <phil&braham.net>
//chmd            3099/tcp   CHIPSY Machine Daemon
//chmd            3099/udp   CHIPSY Machine Daemon
//#			   Trond B�rsting <Trond.Borsting&snota.no>
//opcon-xps       3100/tcp   OpCon/xps
//opcon-xps       3100/udp   OpCon/xps
//#                          David Bourland <DBourland&smausa.com> 
//hp-pxpib        3101/tcp   HP PolicyXpert PIB Server
//hp-pxpib        3101/udp   HP PolicyXpert PIB Server
//#                          Brian O'Keefe <bokeefe&cnd.hp.com>
//slslavemon      3102/tcp   SoftlinK Slave Mon Port
//slslavemon      3102/udp   SoftlinK Slave Mon Port
//#                          Moshe Livne <moshe&softlinkusa.com>
//autocuesmi      3103/tcp   Autocue SMI Protocol
//autocuesmi      3103/udp   Autocue SMI Protocol
//autocuelog      3104/tcp   Autocue Logger Protocol
//autocuetime     3104/udp   Autocue Time Service
//#                          Geoff Back <geoff&autocue.co.uk>
//cardbox		3105/tcp   Cardbox
//cardbox		3105/udp   Cardbox
//cardbox-http	3106/tcp   Cardbox HTTP
//cardbox-http	3106/udp   Cardbox HTTP
//#			   Martin Kochanski <martin&cardbox.co.uk>
//business    	3107/tcp   Business protocol
//business    	3107/udp   Business protocol
//geolocate   	3108/tcp   Geolocate protocol
//geolocate   	3108/udp   Geolocate protocol
//personnel   	3109/tcp   Personnel protocol
//personnel   	3109/udp   Personnel protocol
//#                          William Randolph Royere III 
//#                          <william&royere.net>
//sim-control     3110/tcp   simulator control port
//sim-control     3110/udp   simulator control port
//#                          Ian Bell <ianb&arca-technologies.com>
//wsynch          3111/tcp   Web Synchronous Services
//wsynch          3111/udp   Web Synchronous Services
//#                          Valery Fremaux <vf&eisti.fr>
//ksysguard       3112/tcp   KDE System Guard
//ksysguard       3112/udp   KDE System Guard
//#                          Chris Schlaeger <cs&kde.org>
//cs-auth-svr     3113/tcp   CS-Authenticate Svr Port
//cs-auth-svr     3113/udp   CS-Authenticate Svr Port
//#                          Cliff Diamond <cdiamond&crypto-solutions.co.uk>
//#                          Andy Georgiou <ageorgiou&crypto-solutions.co.uk>
//ccmad           3114/tcp   CCM AutoDiscover
//ccmad           3114/udp   CCM AutoDiscover
//#                          Ram Sudama <rsudama&on.com> 
//mctet-master    3115/tcp   MCTET Master
//mctet-master    3115/udp   MCTET Master
//mctet-gateway   3116/tcp   MCTET Gateway
//mctet-gateway   3116/udp   MCTET Gateway
//mctet-jserv     3117/tcp   MCTET Jserv
//mctet-jserv     3117/udp   MCTET Jserv
//#                          Portnoy Boxman <portnoy_boxman&bmc.com> 
//pkagent         3118/tcp   PKAgent
//pkagent         3118/udp   PKAgent
//#                          Michael Douglass <mikedoug&datafoundry.net>
//d2000kernel     3119/tcp   D2000 Kernel Port
//d2000kernel     3119/udp   D2000 Kernel Port
//d2000webserver  3120/tcp   D2000 Webserver Port 
3120,//d2000webserver  3120/udp   D2000 Webserver Port
//#                          Tomas Rajcan <trajcan&ipesoft.sk>
//#               3121       Unassigned (Removed 2003-09-17)
3122,//vtr-emulator    3122/tcp   MTI VTR Emulator port
//vtr-emulator    3122/udp   MTI VTR Emulator port
//#                          John Mertus <mertus&mathtech.com>
//edix            3123/tcp   EDI Translation Protocol
//edix            3123/udp   EDI Translation Protocol
//#                          William Randolph Royere III <william&royere.net>
//beacon-port     3124/tcp   Beacon Port
//beacon-port     3124/udp   Beacon Port
//#                          James Paul Duncan <pduncan&beaconcrm.com>
//a13-an          3125/tcp   A13-AN Interface
3125,//a13-an          3125/udp   A13-AN Interface
//#                          Douglas Knisely <dnk&lucent.com>
//#		3126       Unassigned (Removed 2007-10-04)
3127,//ctx-bridge      3127/tcp   CTX Bridge Port
//ctx-bridge      3127/udp   CTX Bridge Port
//#                          Alexander Dubrovsky <dubrovsky_alex&emc.com>
//ndl-aas         3128/tcp   Active API Server Port
//ndl-aas         3128/udp   Active API Server Port
//#                          Martin Norman <martin&ndl.co.uk>
//netport-id      3129/tcp   NetPort Discovery Port
//netport-id      3129/udp   NetPort Discovery Port
//#                          P.T.K. Farrar <farrarp&teccon.co.uk>
//icpv2		3130/tcp   ICPv2
//icpv2		3130/udp   ICPv2
//#			   Duane Wessels <wessels&nlanr.net>
//netbookmark	3131/tcp   Net Book Mark
//netbookmark	3131/udp   Net Book Mark
//#			   Yiftach Ravid <yiftach&haifa.vnet.ibm.com>
//ms-rule-engine  3132/tcp   Microsoft Business Rule Engine Update Service
//ms-rule-engine  3132/udp   Microsoft Business Rule Engine Update Service
//#                          Anush Kumar <anushk&microsoft.com>
//prism-deploy    3133/tcp   Prism Deploy User Port
//prism-deploy    3133/udp   Prism Deploy User Port
//#                          Joan Linck <jlinck&lanovation.com>
//ecp             3134/tcp   Extensible Code Protocol
//ecp             3134/udp   Extensible Code Protocol
//#                          Jim Trek <jtrek&rochester.rr.com>
//#                          Mark Bocko <bocko&ece.rochester.edu>
//peerbook-port   3135/tcp   PeerBook Port
//peerbook-port   3135/udp   PeerBook Port
//#                          John Flowers <jf&gigamediaaccess.com>
//grubd           3136/tcp   Grub Server Port
//grubd           3136/udp   Grub Server Port
//#                          Kord Campbell <kord&grub.org>
//rtnt-1          3137/tcp   rtnt-1 data packets
//rtnt-1          3137/udp   rtnt-1 data packets
//rtnt-2          3138/tcp   rtnt-2 data packets
//rtnt-2          3138/udp   rtnt-2 data packets
//#                          Ron Muellerschoen <rjm&cobra.jpl.nasa.gov>
//incognitorv     3139/tcp   Incognito Rendez-Vous
//incognitorv     3139/udp   Incognito Rendez-Vous
//#                          Stephane Bourque <stephb&incognito.com>
//ariliamulti     3140/tcp   Arilia Multiplexor
//ariliamulti     3140/udp   Arilia Multiplexor
//#                          Stephane Bourque <sbourque&arilia.com>
//vmodem          3141/tcp   VMODEM
//vmodem          3141/udp   VMODEM
//#                          Ray Gwinn <p00321&psilink.com>
//rdc-wh-eos	3142/tcp   RDC WH EOS
//rdc-wh-eos	3142/udp   RDC WH EOS
//#			   Udi Nir <udi_nir&ncc.co.il>
//seaview		3143/tcp   Sea View
//seaview		3143/udp   Sea View
//#			   Jim Flaherty <jim_e_flaherty&notes.seagate.com>
//tarantella	3144/tcp   Tarantella
//tarantella	3144/udp   Tarantella
//#			   Roger Binns <rogerb&sco.com>
//csi-lfap	3145/tcp   CSI-LFAP
//csi-lfap	3145/udp   CSI-LFAP
//#			   Paul Amsden <amsden@.ctron.com>
//bears-02        3146/tcp   bears-02
//bears-02        3146/udp   bears-02
//#                          Bruce McKinnon <brucemck&bearsolutions.com.au>
//rfio		3147/tcp   RFIO
//rfio		3147/udp   RFIO
//#			   Frederic Hemmer <Frederic.Hemmer&cern.ch>
//nm-game-admin	3148/tcp   NetMike Game Administrator
//nm-game-admin	3148/udp   NetMike Game Administrator
//nm-game-server	3149/tcp   NetMike Game Server
//nm-game-server	3149/udp   NetMike Game Server
//nm-asses-admin	3150/tcp   NetMike Assessor Administrator
//nm-asses-admin	3150/udp   NetMike Assessor Administrator
//nm-assessor	3151/tcp   NetMike Assessor
//nm-assessor	3151/udp   NetMike Assessor
//#			   Andrew Sharpe <help&smartsims.com>
//feitianrockey   3152/tcp   FeiTian Port
//feitianrockey   3152/udp   FeiTian Port
//#                          Huang Yu <llw&ftsafe.com>
//s8-client-port  3153/tcp   S8Cargo Client Port
//s8-client-port  3153/udp   S8Cargo Client Port
//#                          Jon S. Kyle <JKyle&SpeedwaySoftware.com>
//ccmrmi          3154/tcp   ON RMI Registry
//ccmrmi		3154/udp   ON RMI Registry
//#                          Ram Sudama <rsudama&on.com>
//jpegmpeg        3155/tcp   JpegMpeg Port
//jpegmpeg        3155/udp   JpegMpeg Port
//#                          Richard Bassous <rbassous&yahoo.com>
//indura          3156/tcp   Indura Collector
//indura          3156/udp   Indura Collector
//#                          Bruce Kosbab <bruce.kosbab&indurasoft.com>
//e3consultants   3157/tcp   CCC Listener Port
//e3consultants   3157/udp   CCC Listener Port
//#                          Brian Carnell <brian&e3consultants.com>
//stvp            3158/tcp   SmashTV Protocol
//stvp            3158/udp   SmashTV Protocol
//#                          Christian Wolff <stvp&smash.tv>
//navegaweb-port  3159/tcp   NavegaWeb Tarification
//navegaweb-port  3159/udp   NavegaWeb Tarification
//#                          Miguel Angel Fernandez <mafg&tid.es>
//tip-app-server  3160/tcp   TIP Application Server
//tip-app-server  3160/udp   TIP Application Server
//#                          Olivier Mascia <om&tipgroup.com>
//doc1lm          3161/tcp   DOC1 License Manager
//doc1lm          3161/udp   DOC1 License Manager
//#                          Greg Goodson <ggoodson&group1software.co.uk>
//sflm            3162/tcp   SFLM
//sflm            3162/udp   SFLM
//#                          System Administrator <sysadmin&silvaco.com>
//res-sap		3163/tcp   RES-SAP
//res-sap         3163/udp   RES-SAP
//#                          Bob Janssen <bob&res.nl>
//imprs		3164/tcp   IMPRS
//imprs           3164/udp   IMPRS
//#                          Lars Bohn <Lars.Bohn&nokia.com>
//newgenpay       3165/tcp   Newgenpay Engine Service
//newgenpay       3165/udp   Newgenpay Engine Service
//#                          Ilan Zisser <ilan&newgenpay.com>
//sossecollector  3166/tcp   Quest Spotlight Out-Of-Process Collector
//sossecollector  3166/udp   Quest Spotlight Out-Of-Process Collector
//#                          Previous contact: Fred Surr <quest_iana&oz.quest.com>
//#                          Current contact: Greg Cottman <greg.cottman&quest.com> 23 October 2008
//nowcontact	3167/tcp   Now Contact Public Server
//nowcontact	3167/udp   Now Contact Public Server
//poweronnud      3168/tcp   Now Up-to-Date Public Server
//poweronnud      3168/udp   Now Up-to-Date Public Server
//#                          John Wallace <john&nowsoftware.com> 
//serverview-as	3169/tcp   SERVERVIEW-AS
//serverview-as   3169/udp   SERVERVIEW-AS
//serverview-asn  3170/tcp   SERVERVIEW-ASN
//serverview-asn  3170/udp   SERVERVIEW-ASN
//serverview-gf   3171/tcp   SERVERVIEW-GF
//serverview-gf   3171/udp   SERVERVIEW-GF
//serverview-rm   3172/tcp   SERVERVIEW-RM
//serverview-rm   3172/udp   SERVERVIEW-RM
//serverview-icc  3173/tcp   SERVERVIEW-ICC
//serverview-icc  3173/udp   SERVERVIEW-ICC
//#                          Detlef Rothe <detlef.rothe&ts.fujitsu.com> 15 May 2009
//armi-server     3174/tcp   ARMI Server
//armi-server     3174/udp   ARMI Server
//#                          Bobby Martin <bobbymartin&hotmail.com>
//t1-e1-over-ip   3175/tcp   T1_E1_Over_IP
//t1-e1-over-ip   3175/udp   T1_E1_Over_IP
//#                          Mark Doyle <mark&engagecom.com>
//ars-master      3176/tcp   ARS Master
//ars-master      3176/udp   ARS Master
//#                          Portnoy Boxman <portnoy_boxman&bmc.com>
//phonex-port     3177/tcp   Phonex Protocol
//phonex-port     3177/udp   Phonex Protocol
//#                          Doug Grover <dgrover&phonex.com>
//radclientport   3178/tcp   Radiance UltraEdge Port
//radclientport   3178/udp   Radiance UltraEdge Port
//#                          Sri Subramaniam <sri&radiance.com>
//h2gf-w-2m       3179/tcp   H2GF W.2m Handover prot.
//h2gf-w-2m       3179/udp   H2GF W.2m Handover prot.
//#                          Arne Norefors <Arne.Norefors&ericsson.com>
//mc-brk-srv	3180/tcp   Millicent Broker Server
//mc-brk-srv	3180/udp   Millicent Broker Server
//#			   Steve Glassman <steveg&pa.dec.com>
//bmcpatrolagent	3181/tcp   BMC Patrol Agent
//bmcpatrolagent  3181/udp   BMC Patrol Agent
//bmcpatrolrnvu	3182/tcp   BMC Patrol Rendezvous
//bmcpatrolrnvu   3182/udp   BMC Patrol Rendezvous
//#			   Portnoy Boxman <portnoy_boxman&bmc.com>
//cops-tls        3183/tcp   COPS/TLS
//cops-tls        3183/udp   COPS/TLS
//#                          Mark Stevens <mstevens&ellacoya.com>
//apogeex-port    3184/tcp   ApogeeX Port
//apogeex-port    3184/udp   ApogeeX Port
//#                          Tom Nys <tom.nys.tn&belgium.agfa.com>
//smpppd          3185/tcp   SuSE Meta PPPD
//smpppd          3185/udp   SuSE Meta PPPD
//#                          Arvin Schnell <arvin&suse.de>
//iiw-port        3186/tcp   IIW Monitor User Port
//iiw-port        3186/udp   IIW Monitor User Port
//#                          Corey Burnett <corey.burnett&biopop.com>
//odi-port        3187/tcp   Open Design Listen Port
//odi-port        3187/udp   Open Design Listen Port
//#                          Phivos Aristides <phivos&opendesign.com>
//brcm-comm-port  3188/tcp   Broadcom Port
//brcm-comm-port  3188/udp   Broadcom Port
//#                          Thomas L. Johnson <tjohnson&broadcom.com>
//pcle-infex      3189/tcp   Pinnacle Sys InfEx Port
//pcle-infex      3189/udp   Pinnacle Sys InfEx Port
//#                          Anthon van der Neut <anthon&mnt.org>
//csvr-proxy      3190/tcp   ConServR Proxy
//csvr-proxy      3190/udp   ConServR Proxy
//csvr-sslproxy   3191/tcp   ConServR SSL Proxy
//csvr-sslproxy   3191/udp   ConServR SSL Proxy
//#                          Mikhail Kruk <mkruk&biscom.com>
//firemonrcc      3192/tcp   FireMon Revision Control
//firemonrcc      3192/udp   FireMon Revision Control
//#                          Michael Bishop <mbishop&fishnetsecurity.com>
//spandataport    3193/tcp   SpanDataPort
//spandataport    3193/udp   SpanDataPort
//#                          Jesse McKay <jesse&spandata.com>
//magbind         3194/tcp   Rockstorm MAG protocol
//magbind         3194/udp   Rockstorm MAG protocol
//#                          Jens Nilsson <jens&rockstorm.se>
//ncu-1           3195/tcp   Network Control Unit
//ncu-1           3195/udp   Network Control Unit
//ncu-2           3196/tcp   Network Control Unit
//ncu-2           3196/udp   Network Control Unit
//#                          Charlie Hundre <charlie&rdsrv.reco.com.tw>
//embrace-dp-s    3197/tcp   Embrace Device Protocol Server
//embrace-dp-s    3197/udp   Embrace Device Protocol Server
//embrace-dp-c    3198/tcp   Embrace Device Protocol Client
//embrace-dp-c    3198/udp   Embrace Device Protocol Client
//#                          Elliot Schwartz <elliot&mit.edu>
//dmod-workspace  3199/tcp   DMOD WorkSpace
//dmod-workspace  3199/udp   DMOD WorkSpace
//#                          Nick Plante <nplante&dmod.com>
//tick-port       3200/tcp   Press-sense Tick Port
//tick-port       3200/udp   Press-sense Tick Port
//#                          Boris Svetlitsky <boris&press-sense.com>
//cpq-tasksmart   3201/tcp   CPQ-TaskSmart
//cpq-tasksmart   3201/udp   CPQ-TaskSmart
//#                          Jackie Lau <jackie.lau&compaq.com>
//intraintra      3202/tcp   IntraIntra
//intraintra      3202/udp   IntraIntra
//#                          Matthew Asham <matthewa&bcwireless.net>
//netwatcher-mon  3203/tcp   Network Watcher Monitor
//netwatcher-mon  3203/udp   Network Watcher Monitor
//netwatcher-db   3204/tcp   Network Watcher DB Access
//netwatcher-db   3204/udp   Network Watcher DB Access
//#                          Hirokazu Fujisawa <fujisawa&pfu.fujitsu.com>
//isns            3205/tcp   iSNS Server Port
//isns            3205/udp   iSNS Server Port
//#                          [RFC4171]
//ironmail        3206/tcp   IronMail POP Proxy
//ironmail        3206/udp   IronMail POP Proxy
//#                          Mike Hudack <mike&mhudack.com>
//vx-auth-port    3207/tcp   Veritas Authentication Port
//vx-auth-port    3207/udp   Veritas Authentication Port
//#                          Senthil Ponnuswamy <senthil&veritas.com>
//pfu-prcallback  3208/tcp   PFU PR Callback
//pfu-prcallback  3208/udp   PFU PR Callback
//#                          Tetsuharu Hanada <hanada&pfu.fujitsu.com>
//netwkpathengine 3209/tcp   HP OpenView Network Path Engine Server
//netwkpathengine 3209/udp   HP OpenView Network Path Engine Server
//#                          Anthony Walker <anthony_walker&hp.com>
//flamenco-proxy  3210/tcp   Flamenco Networks Proxy
//flamenco-proxy  3210/udp   Flamenco Networks Proxy
//#                          Corey Corrick <corey.corrick&flamenconetworks.com>
//avsecuremgmt    3211/tcp   Avocent Secure Management
//avsecuremgmt    3211/udp   Avocent Secure Management
//#                          Brian S. Stewart <Brian.Stewart&Avocent.com>
//surveyinst      3212/tcp   Survey Instrument
//surveyinst      3212/udp   Survey Instrument
//#                          Al Amet <aamet&point-inc.com>
//neon24x7        3213/tcp   NEON 24X7 Mission Control
//neon24x7        3213/udp   NEON 24X7 Mission Control
//#                          Tony Lubrano <tlubrano&neonsys.com>
//jmq-daemon-1    3214/tcp   JMQ Daemon Port 1
//jmq-daemon-1    3214/udp   JMQ Daemon Port 1
//jmq-daemon-2    3215/tcp   JMQ Daemon Port 2
//jmq-daemon-2    3215/udp   JMQ Daemon Port 2
//#                          Martin West <Martin.West&spirit-soft.com>
//ferrari-foam    3216/tcp   Ferrari electronic FOAM
//ferrari-foam    3216/udp   Ferrari electronic FOAM
//#                          Johann Deutinger <deutinger&ferrari-electronic.de>
//unite           3217/tcp   Unified IP & Telecom Environment
//unite           3217/udp   Unified IP & Telecom Environment
//#                          Previous contact: Christer Gunnarsson  <christer.gunnarsson&ascomtateco.se>
//#                          Current contact: Christer Gunnarsson <christer.gunnarsson&ascom.se> 26 March 2009
//smartpackets    3218/tcp   EMC SmartPackets
//smartpackets    3218/udp   EMC SmartPackets
//#                          Steve Spataro <spataro_steve&emc.com>
//wms-messenger   3219/tcp   WMS Messenger
//wms-messenger   3219/udp   WMS Messenger
//#                          Michael Monasterio <michael&wmsoftware.com>
//xnm-ssl         3220/tcp   XML NM over SSL
//xnm-ssl         3220/udp   XML NM over SSL
//xnm-clear-text  3221/tcp   XML NM over TCP
//xnm-clear-text  3221/udp   XML NM over TCP
//#                          Mark Trostler <trostler&juniper.net>
//glbp            3222/tcp   Gateway Load Balancing Pr
//glbp            3222/udp   Gateway Load Balancing Pr
//#                          Douglas McLaggan <glbp-info&cisco.com>
//digivote        3223/tcp   DIGIVOTE (R) Vote-Server
//digivote        3223/udp   DIGIVOTE (R) Vote-Server
//#                          Christian Treczoks <ct&braehler.com>
//aes-discovery   3224/tcp   AES Discovery Port
//aes-discovery   3224/udp   AES Discovery Port
//#                          Ken Richard <kenr&aeseducation.com>              
//fcip-port       3225/tcp   FCIP
//fcip-port       3225/udp   FCIP
//#                          RFC 3821
//isi-irp         3226/tcp   ISI Industry Software IRP
//isi-irp         3226/udp   ISI Industry Software IRP
//#                          Peter Sandstrom <peter.sandstrom&tassen.fi>
//dwnmshttp       3227/tcp   DiamondWave NMS Server
//dwnmshttp       3227/udp   DiamondWave NMS Server
//dwmsgserver     3228/tcp   DiamondWave MSG Server
//dwmsgserver     3228/udp   DiamondWave MSG Server
//#                          Varma Bhupatiraju <varma&calient.net>
//global-cd-port  3229/tcp   Global CD Port
//global-cd-port  3229/udp   Global CD Port
//#                          Vitaly Revsin <vitaly&netapp.com>
//sftdst-port     3230/tcp   Software Distributor Port
//sftdst-port     3230/udp   Software Distributor Port
//#                          Andrea Lanza <andrea.lanza&frameweb.it>
//dsnl            3231/tcp   Delta Solutions Direct
//dsnl            3231/udp   Delta Solutions Direct
//#                          Peter Ijkhout <peter&deltasolutions.nl>
//mdtp            3232/tcp   MDT port
//mdtp            3232/udp   MDT port
//#                          IJsbrand Wijnands <ice&cisco.com>
//whisker         3233/tcp   WhiskerControl main port
//whisker         3233/udp   WhiskerControl main port
//#                          Rudolf Cardinal <rudolf&pobox.com> February 2002
//alchemy         3234/tcp   Alchemy Server 
//alchemy         3234/udp   Alchemy Server
//#                          Mikhail Belov <mikhail&imrgold.com> February 2002
//mdap-port       3235/tcp   MDAP port
//mdap-port       3235/udp   MDAP Port
//#                          Johan Deleu <johan.deleu&alcatel.be> February 2002
//apparenet-ts    3236/tcp   appareNet Test Server
//apparenet-ts    3236/udp   appareNet Test Server
//apparenet-tps   3237/tcp   appareNet Test Packet Sequencer
//apparenet-tps   3237/udp   appareNet Test Packet Sequencer
//apparenet-as    3238/tcp   appareNet Analysis Server
//apparenet-as    3238/udp   appareNet Analysis Server
//apparenet-ui    3239/tcp   appareNet User Interface
//apparenet-ui    3239/udp   appareNet User Interface
//#                          Fred Klassen <fklassen&jaalam.com> February 2002
//triomotion      3240/tcp   Trio Motion Control Port
//triomotion      3240/udp   Trio Motion Control Port
//#                          Tony Matthews <tmatthews&triomotion.com> February 2002
//sysorb          3241/tcp   SysOrb Monitoring Server
//sysorb          3241/udp   SysOrb Monitoring Server
//#                          Jakob Oestergaard <joe&sysorb.com> February 2002
//sdp-id-port     3242/tcp   Session Description ID
//sdp-id-port     3242/udp   Session Description ID
//#                          Greg Rose <ggr&qualcomm.com> February 2002
//timelot         3243/tcp   Timelot Port
//timelot         3243/udp   Timelot Port
//#                          David Ferguson <dferguson&xtralot.com> February 2002
//onesaf          3244/tcp   OneSAF
//onesaf          3244/udp   OneSAF
//#                          Gene McCulley <mcculley&cuspy.com> February 2002
//vieo-fe         3245/tcp   VIEO Fabric Executive
//vieo-fe         3245/udp   VIEO Fabric Executive
//#                          James Cox <jocox&view.com> February 2002
//dvt-system      3246/tcp   DVT SYSTEM PORT
//dvt-system      3246/udp   DVT SYSTEM PORT
//dvt-data        3247/tcp   DVT DATA LINK
//dvt-data        3247/udp   DVT DATA LINK
//#                          Phillip Heil <phil.heil&dvtsensors.com> February 2002
//procos-lm       3248/tcp   PROCOS LM
//procos-lm       3248/udp   PROCOS LM
//#                          Torsten Rendelmann
//#                          <torsten.rendelmann&procos.com> February 2002
//ssp             3249/tcp   State Sync Protocol
//ssp             3249/udp   State Sync Protocol
//#                          Stephane Beaulieu <stephane&cisco.com> February 2002
//hicp            3250/tcp   HMS hicp port
//hicp            3250/udp   HMS hicp port
//#                          Joel Palsson, HMS Industrial Networks AB
//#                          <ianacontact&hms.se> February 2002
//sysscanner      3251/tcp   Sys Scanner
//sysscanner      3251/udp   Sys Scanner
//#                          Dick Georges <georges&monaco.net> February 2002
//dhe             3252/tcp   DHE port
//dhe             3252/udp   DHE port
//#                          Fabrizio Massimo Ferrara <fmf&gesi.it> February 2002
//pda-data        3253/tcp   PDA Data
//pda-data        3253/udp   PDA Data
//pda-sys         3254/tcp   PDA System
//pda-sys         3254/udp   PDA System
//#                          Jian Fan <fjian&dmfsys.com> February 2002
//semaphore       3255/tcp   Semaphore Connection Port
//semaphore       3255/udp   Semaphore Connection Port
//#                          Jay Eckles <ecklesweb&yahoo.com> February 2002
//cpqrpm-agent    3256/tcp   Compaq RPM Agent Port
//cpqrpm-agent    3256/udp   Compaq RPM Agent Port
//cpqrpm-server   3257/tcp   Compaq RPM Server Port
//cpqrpm-server   3257/udp   Compaq RPM Server Port
//#                          Royal King <royal.king&compaq.com> February 2002
//ivecon-port     3258/tcp   Ivecon Server Port
//ivecon-port     3258/udp   Ivecon Server Port
//#                          Serguei Tevs <STevs&ivecon.com> February 2002
//epncdp2         3259/tcp   Epson Network Common Devi
//epncdp2         3259/udp   Epson Network Common Devi
//#                          SEIKO EPSON Corporation - Oishi Toshiaki
//#                          <Oishi.Toshiaki&exc.epson.co.jp> February 2002
//iscsi-target    3260/tcp   iSCSI port
//iscsi-target    3260/udp   iSCSI port
//#                          Julian Satran <Julian_Satran&il.ibm.com>
//winshadow       3261/tcp   winShadow
//winshadow       3261/udp   winShadow
//#                          Colin Barry <cbarry&gbahn.com>
//necp            3262/tcp   NECP
//necp            3262/udp   NECP
//#                          Alberto Cerpa <cerpa&isi.edu>
//ecolor-imager   3263/tcp   E-Color Enterprise Imager
//ecolor-imager   3263/udp   E-Color Enterprise Imager
//#                          Tamara Baker <tbaker&ecolor.com>
//ccmail          3264/tcp   cc:mail/lotus
//ccmail          3264/udp   cc:mail/lotus
//#                          <brockman&ccmail.com>
//altav-tunnel    3265/tcp   Altav Tunnel
//altav-tunnel    3265/udp   Altav Tunnel
//#                          Gary M. Allen <gallen&symantec.com>
//ns-cfg-server   3266/tcp   NS CFG Server
//ns-cfg-server   3266/udp   NS CFG Server
//#                          Aivi Lie <LIEA&netsoft.com>
//ibm-dial-out    3267/tcp   IBM Dial Out
//ibm-dial-out    3267/udp   IBM Dial Out
//#                          Skip Booth <sbooth&VNET.IBM.COM>
//msft-gc         3268/tcp   Microsoft Global Catalog
//msft-gc         3268/udp   Microsoft Global Catalog
//msft-gc-ssl     3269/tcp   Microsoft Global Catalog with LDAP/SSL
//msft-gc-ssl     3269/udp   Microsoft Global Catalog with LDAP/SSL
//#                          Asaf Kashi <asafk&microsoft.com>
//verismart       3270/tcp   Verismart
//verismart       3270/udp   Verismart
//#                          Jay Weber <weber&vfi.com>
//csoft-prev      3271/tcp   CSoft Prev Port
//csoft-prev      3271/udp   CSoft Prev Port
//#                          Nedelcho Stanev <decho&iname.com>
//user-manager    3272/tcp   Fujitsu User Manager
//user-manager    3272/udp   Fujitsu User Manager
//#                          Yukihiko Sakurai <y-sakurai&ael.fujitsu.co.jp>
//sxmp            3273/tcp   Simple Extensible Multiplexed Protocol
//sxmp            3273/udp   Simple Extensible Multiplexed Protocol
//#                          admin <iana&sightlinesystems.com> 
//ordinox-server  3274/tcp   Ordinox Server
//ordinox-server  3274/udp   Ordinox Server
//#                          Denis Ducharme <dducharme&softek.com>
//samd            3275/tcp   SAMD
//samd            3275/udp   SAMD
//#                          Edgar Circenis <ec&fc.hp.com>
//maxim-asics  	3276/tcp   Maxim ASICs
//maxim-asics	3276/udp   Maxim ASICs
//#		           Dave Inman <davei&mxim.com>
//awg-proxy	3277/tcp   AWG Proxy
//awg-proxy	3277/udp   AWG Proxy
//#		           Alex McDonald <alexm&an.hp.com>
//lkcmserver	3278/tcp   LKCM Server
//lkcmserver	3278/udp   LKCM Server
//#		           Javier Jimenez
//admind		3279/tcp   admind
//admind		3279/udp   admind
//#		           Jeff Haynes <haynes&chistech.com>
//vs-server	3280/tcp   VS Server
//vs-server	3280/udp   VS Server
//#		           Scott Godlew <Scott&godlew.com>
//sysopt		3281/tcp   SYSOPT
//sysopt 		3281/udp   SYSOPT
//#		           Tony Hoffman <ajh&unx.dec.com>
//datusorb	3282/tcp   Datusorb
//datusorb	3282/udp   Datusorb
//#			   Thomas Martin <thomas&datus-usa.com>
//net-assistant	3283/tcp   Net Assistant
//net-assistant	3283/udp   Net Assistant
//#			   Michael Stein <mvs&apple.com>
//4talk		3284/tcp   4Talk
//4talk		3284/udp   4Talk
//#			   Tony Bushnell <tony_bushnell&four-sight.co.uk>
//plato		3285/tcp   Plato
//plato		3285/udp   Plato
//#			   Jim Battin <battin&tro.com>
//e-net		3286/tcp   E-Net
//e-net		3286/udp   E-Net
//#			   Steven Grigsby <sgrigsby&austin.eent.com>
//directvdata	3287/tcp   DIRECTVDATA
//directvdata	3287/udp   DIRECTVDATA
//#			   Michael Friedman <mfr1&worldnet.att.net>
//cops		3288/tcp   COPS
//cops 		3288/udp   COPS
//#			   Shai Herzog <herzog&iphighway.com>
//enpc		3289/tcp   ENPC
//enpc		3289/udp   ENPC
//#			   SEIKO EPSON <Ishida.Hitoshi&exc.epson.co.jp>
//caps-lm		3290/tcp   CAPS LOGISTICS TOOLKIT - LM
//caps-lm		3290/udp   CAPS LOGISTICS TOOLKIT - LM
//#			   Joseph Krebs <joek&caps.com>
//sah-lm		3291/tcp   S A Holditch & Associates - LM
//sah-lm		3291/udp   S A Holditch & Associates - LM
//#			   Randy Hudgens <rhh&nmail.holditch.com>
//cart-o-rama	3292/tcp   Cart O Rama
//cart-o-rama	3292/udp   Cart O Rama
//#			   Phillip Dillinger <Phillip.Dillinger&sealabs.com>
//fg-fps		3293/tcp   fg-fps
//fg-fps		3293/udp   fg-fps
//fg-gip		3294/tcp   fg-gip
//fg-gip		3294/udp   fg-gip
//#			   Jean-Marc Frailong <jmf&freegate.net>
//dyniplookup	3295/tcp   Dynamic IP Lookup
//dyniplookup	3295/udp   Dynamic IP Lookup
//#			   Eugene Osovetsky <eugeneo&geocities.com>
//rib-slm		3296/tcp   Rib License Manager
//rib-slm		3296/udp   Rib License Manager
//#			   Kristean Heisler <kh&rib.de>
//cytel-lm	3297/tcp   Cytel License Manager
//cytel-lm	3297/udp   Cytel License Manager
//#			   Yogesh P. Gajjar <yogesh&cytel.com>
//deskview        3298/tcp   DeskView
//deskview        3298/udp   DeskView
//#                          Manfred Randelzofer 
//#                          <manfred.randelzofer&fujitsu-siemens.com>
//pdrncs		3299/tcp   pdrncs
//pdrncs		3299/udp   pdrncs
//#			   Paul Wissenbach <paulwi&vnd.tek.com>
//###########	3300-3301  Unauthorized Use by SAP R/3   ######
//mcs-fastmail	3302/tcp   MCS Fastmail
//mcs-fastmail	3302/udp   MCS Fastmail
//#			   Patti Jo Newsom <pjn&mcsdallas.com>
//opsession-clnt	3303/tcp   OP Session Client
//opsession-clnt  3303/udp   OP Session Client
//opsession-srvr  3304/tcp   OP Session Server
//opsession-srvr  3304/udp   OP Session Server
//#			   Amir Blich <amir&netmanage.co.il>
//odette-ftp	3305/tcp   ODETTE-FTP
//odette-ftp	3305/udp   ODETTE-FTP
//#			   David Nash <dnash&ford.com>
//mysql		3306/tcp   MySQL
//mysql		3306/udp   MySQL
//#			   Monty <monty&analytikerna.se>
//opsession-prxy	3307/tcp   OP Session Proxy
//opsession-prxy	3307/udp   OP Session Proxy
//#			   Amir Blich <amir&netmanage.co.il>
//tns-server	3308/tcp   TNS Server
//tns-server	3308/udp   TNS Server
//tns-adv		3309/tcp   TNS ADV
//tns-adv		3309/udp   TNS ADV
//#			   Jerome Albin <albin&taec.enet.dec.com>
//dyna-access	3310/tcp   Dyna Access
//dyna-access	3310/udp   Dyna Access
//#			   Dave Belliveau
//#			   <DaveBelliveau&cornerstonesoftware.com>
//mcns-tel-ret	3311/tcp   MCNS Tel Ret
//mcns-tel-ret	3311/udp   MCNS Tel Ret
//#			   Randall Atkinson <rja&home.net>
//appman-server   3312/tcp   Application Management Server
//appman-server   3312/udp   Application Management Server
//uorb            3313/tcp   Unify Object Broker
//uorb            3313/udp   Unify Object Broker
//uohost          3314/tcp   Unify Object Host
//uohost          3314/udp   Unify Object Host
//#                          Duane Gibson <ianaportmaster&unify.com>
//cdid		3315/tcp   CDID
//cdid		3315/udp   CDID
//#			   Andrew Borisov <hdr&chat.ru>
//aicc-cmi	3316/tcp   AICC/CMI
//aicc-cmi	3316/udp   AICC/CMI
//#			   William McDonald <billmc&atc.boeing.com>
//vsaiport	3317/tcp   VSAI PORT
//vsaiport	3317/udp   VSAI PORT
//#			   Rieko Asai <asai&isl.mei.co.jp>
//ssrip		3318/tcp   Swith to Swith Routing Information Protocol
//ssrip		3318/udp   Swith to Swith Routing Information Protocol
//#			   Baba Hidekazu <baba&flare.nd.net.fujitsu.co.jp>
//sdt-lmd		3319/tcp   SDT License Manager
//sdt-lmd		3319/udp   SDT License Manager
//#			   Salvo Nassisi <sdtech&tin.it>
//officelink2000	3320/tcp   Office Link 2000
//officelink2000	3320/udp   Office Link 2000
//#			   Mike Balch <mbalch&teltone.com>
//vnsstr		3321/tcp   VNSSTR
//vnsstr		3321/udp   VNSSTR
//#			   Takeshi Ohmura <ohmura&isl.mei.co.jp>
//active-net	3322-3325  Active Networks
//#			   Bob Braden <braden&isi.edu>
//sftu		3326/tcp   SFTU
//sftu		3326/udp   SFTU
//#		           Eduardo Rosenberg de Moura <eduardor&spacenet.com.br>
//bbars		3327/tcp   BBARS
//bbars		3327/udp   BBARS
//#			   Lou Harris <lharris&outlx.bandl.com>
//egptlm		3328/tcp   Eaglepoint License Manager
//egptlm		3328/udp   Eaglepoint License Manager
//#			   Dave Benton <dave.benton&eaglepoint.com>
//hp-device-disc  3329/tcp   HP Device Disc
//hp-device-disc  3329/udp   HP Device Disc
//#			   Shivaun Albright <shivaun_albright&hp.com>
//mcs-calypsoicf  3330/tcp   MCS Calypso ICF
//mcs-calypsoicf  3330/udp   MCS Calypso ICF
//mcs-messaging	3331/tcp   MCS Messaging
//mcs-messaging	3331/udp   MCS Messaging
//mcs-mailsvr	3332/tcp   MCS Mail Server
//mcs-mailsvr	3332/udp   MCS Mail Server
//#			   Patti Jo Newsom <pjn&mcsdallas.com>
//dec-notes       3333/tcp   DEC Notes
//dec-notes       3333/udp   DEC Notes
//#                          Kim Moraros <moraros&via.enet.dec.com>
//directv-web	3334/tcp   Direct TV Webcasting
//directv-web	3334/udp   Direct TV Webcasting
//directv-soft	3335/tcp   Direct TV Software Updates
//directv-soft	3335/udp   Direct TV Software Updates
//directv-tick	3336/tcp   Direct TV Tickers
//directv-tick	3336/udp   Direct TV Tickers
//directv-catlg	3337/tcp   Direct TV Data Catalog
//directv-catlg	3337/udp   Direct TV Data Catalog
//#			   Michael Friedman <mfr1&worldnet.att.net>
//anet-b		3338/tcp   OMF data b
//anet-b		3338/udp   OMF data b
//anet-l		3339/tcp   OMF data l
//anet-l		3339/udp   OMF data l
//anet-m		3340/tcp   OMF data m
//anet-m		3340/udp   OMF data m
//anet-h		3341/tcp   OMF data h
//anet-h		3341/udp   OMF data h
//#			   Per Sahlqvist <psahlqvi&sw.seisy.abb.se>
//webtie		3342/tcp   WebTIE
//webtie		3342/udp   WebTIE
//#			   Kevin Frender <kbf&ngdc.noaa.gov>
//ms-cluster-net  3343/tcp   MS Cluster Net
//ms-cluster-net  3343/udp   MS Cluster Net
//#                          Previous contact: Mike Massa <mikemas&microsoft.com>
//#                          Current contact: David Dion <David.Dion&microsoft.com> 12 February 2009
//bnt-manager     3344/tcp   BNT Manager
//bnt-manager     3344/udp   BNT Manager
//#                          Engineering Dept. <domains&badgernt.com>
//influence       3345/tcp   Influence
//influence       3345/udp   Influence
//#			   Russ Ferriday <russf&topia.com>
//trnsprntproxy	3346/tcp   Trnsprnt Proxy
//trnsprntproxy   3346/udp   Trnsprnt Proxy
//#			   Grant Kirby <grant_kirby&ccm.al.intel.com>
//phoenix-rpc	3347/tcp   Phoenix RPC
//phoenix-rpc	3347/udp   Phoenix RPC
//#			   Ian Anderson <ian_anderson&phoenix.com>
//pangolin-laser	3348/tcp   Pangolin Laser
//pangolin-laser	3348/udp   Pangolin Laser
//#			   William Benner <William_Benner&msn.com>
//chevinservices	3349/tcp   Chevin Services
//chevinservices  3349/udp   Chevin Services
//#			   Gus McNaughton <gus&chevin.com>
//findviatv	3350/tcp   FINDVIATV
//findviatv	3350/udp   FINDVIATV
//#			   Oran Davis <oran&8x8.com>
//btrieve         3351/tcp   Btrieve port
//btrieve         3351/udp   Btrieve port
//ssql            3352/tcp   Scalable SQL
//ssql            3352/udp   Scalable SQL
//#                          Chuck Talk <ctalk&pervasive.com>
//fatpipe		3353/tcp   FATPIPE
//fatpipe		3353/udp   FATPIPE
//#			   Sanchaita Datta <sdatta&ragula.com>
//suitjd		3354/tcp   SUITJD
//suitjd		3354/udp   SUITJD
//#			   Todd Moyer <tsm&unx.dec.com>
//ordinox-dbase	3355/tcp   Ordinox Dbase
//ordinox-dbase	3355/udp   Ordinox Dbase
//#                          Denis Ducharme <dducharme&softek.com>
//upnotifyps	3356/tcp   UPNOTIFYPS
//upnotifyps	3356/udp   UPNOTIFYPS
//#			   Mark Fox <markf&uplanet.com>
//adtech-test	3357/tcp   Adtech Test IP
//adtech-test	3357/udp   Adtech Test IP
//#			   Robin Uyeshiro <robin_u&adtech-inc.com>
//mpsysrmsvr	3358/tcp   Mp Sys Rmsvr
//mpsysrmsvr	3358/udp   Mp Sys Rmsvr
//#			   Hiroyuki Kawabuchi <buchi&ael.fujitsu.co.jp>   
//wg-netforce	3359/tcp   WG NetForce
//wg-netforce	3359/udp   WG NetForce
//#			   Lee Wheat <wheat&wg.com>
//kv-server	3360/tcp   KV Server
//kv-server	3360/udp   KV Server
//kv-agent	3361/tcp   KV Agent 
//kv-agent	3361/udp   KV Agent
//#			   Thomas Soranno <tom_soranno&cipartners.com>
//dj-ilm		3362/tcp   DJ ILM
//dj-ilm		3362/udp   DJ ILM
//#			   Don Tyson
//nati-vi-server	3363/tcp   NATI Vi Server
//nati-vi-server	3363/udp   NATI Vi Server
//#			   Robert Dye <rob&natinst.com>
//creativeserver	3364/tcp   Creative Server
//creativeserver	3364/udp   Creative Server
//contentserver	3365/tcp   Content Server
//contentserver	3365/udp   Content Server
//creativepartnr	3366/tcp   Creative Partner
//creativepartnr	3366/udp   Creative Partner
//#			   Jesus Ortiz <Jesus_A._Ortiz&notes.emotion.com>
//satvid-datalnk	3367-3371  Satellite Video Data Link
//#			   Scott Engel <ScottX_Engel&ccm.jf.intel.com>
//tip2		3372/tcp   TIP 2
//tip2		3372/udp   TIP 2
//#			   Keith Evans <keith&loc252.tandem.com>
//lavenir-lm	3373/tcp   Lavenir License Manager
//lavenir-lm	3373/udp   Lavenir License Manager
//#			   Marius Matioc <marius&lavenir.com>
//cluster-disc	3374/tcp   Cluster Disc
//cluster-disc	3374/udp   Cluster Disc
//#			   Jeff Hughes <Jeff.Hughes&columbiasc.ncr.com>
//vsnm-agent	3375/tcp   VSNM Agent
//vsnm-agent      3375/udp   VSNM Agent
//#			   Venkat Rangan <venkatr&vitalsigns.com>
//cdbroker	3376/tcp   CD Broker
//cdbroker	3376/udp   CD Broker
//#			   Moon Ho Chung <mchung&esps.com>
//cogsys-lm	3377/tcp   Cogsys Network License Manager
//cogsys-lm	3377/udp   Cogsys Network License Manager
//#			   Simon Chinnick <support&cogsys.co.uk>
//wsicopy		3378/tcp   WSICOPY
//wsicopy		3378/udp   WSICOPY
//#			   James Overby
//socorfs		3379/tcp   SOCORFS
//socorfs		3379/udp   SOCORFS
//#			   Hugo Charbonneau
//sns-channels	3380/tcp   SNS Channels
//sns-channels	3380/udp   SNS Channels
//#			   Shekar Pasumarthi <shekarp&firstfloor.com>
//geneous		3381/tcp   Geneous
//geneous		3381/udp   Geneous
//#			   Nick de Smith <nick&desmith.net>
//fujitsu-neat	3382/tcp   Fujitsu Network Enhanced Antitheft function
//fujitsu-neat	3382/udp   Fujitsu Network Enhanced Antitheft function
//#			   Markku Viima <markku.viima&team.icl.se>
//esp-lm		3383/tcp   Enterprise Software Products License Manager
//esp-lm		3383/udp   Enterprise Software Products License Manager
//#			   George Rudy <george&entsoft.com>
//hp-clic		3384/tcp   Cluster Management Services
//hp-clic 	3384/udp   Hardware Management
//#			   Rajesh Srinivasaraghavan <srajesh&cup.hp.com>
//qnxnetman	3385/tcp   qnxnetman
//qnxnetman	3385/udp   qnxnetman
//#			   Michael Hunter <mphunter&qnx.com>
//gprs-data	3386/tcp   GPRS Data
//gprs-sig	3386/udp   GPRS SIG
//#			   Ansgar Bergmann <Ansgar.Bergmann&etsi.fr>
//backroomnet	3387/tcp   Back Room Net
//backroomnet	3387/udp   Back Room Net
//#			   Clayton Wilkinson <cwilkinson&carreker.com>
//cbserver	3388/tcp   CB Server
//cbserver	3388/udp   CB Server
//#			   Allen Wei <Allen_Wei&arborsoft.com>
//ms-wbt-server	3389/tcp   MS WBT Server
//ms-wbt-server	3389/udp   MS WBT Server
//#			   Ritu Bahl <ritub&microsoft.com>
//dsc		3390/tcp   Distributed Service Coordinator
//dsc		3390/udp   Distributed Service Coordinator
//#			   Charles Honton <chas&honton.org>
//savant		3391/tcp   SAVANT
//savant		3391/udp   SAVANT
//#			   Andy Bruce <franklin_yah&yahoo.com>
//efi-lm		3392/tcp   EFI License Management
//efi-lm		3392/udp   EFI License Management
//#			   Ross E. Greinke <greinker&execpc.com>
//d2k-tapestry1	3393/tcp   D2K Tapestry Client to Server
//d2k-tapestry1	3393/udp   D2K Tapestry Client to Server
//d2k-tapestry2	3394/tcp   D2K Tapestry Server to Server
//d2k-tapestry2	3394/udp   D2K Tapestry Server to Server
//#			   Eric Lan <elan&d2k.com>
//dyna-lm		3395/tcp   Dyna License Manager (Elam)
//dyna-lm		3395/udp   Dyna License Manager (Elam)
//#			   Anjana Iyer <anjana&dyna.com>
//printer_agent	3396/tcp   Printer Agent
//printer_agent	3396/udp   Printer Agent
//#			   Devon Taylor <dtaylor&novell.com>
//cloanto-lm	3397/tcp   Cloanto License Manager
//cloanto-lm	3397/udp   Cloanto License Manager 
//#		    	   Takeo Sato <takeo_sato-iana&cloanto.com>
//mercantile	3398/tcp   Mercantile
//mercantile	3398/udp   Mercantile
//#			   Erik Kragh Jensen <kragh&inet.uni2.dk>
//csms		3399/tcp   CSMS
//csms		3399/udp   CSMS
//csms2		3400/tcp   CSMS2
//csms2		3400/udp   CSMS2
//#			   Markus Michels <mmi&cedros.com>
//filecast        3401/tcp   filecast
//filecast        3401/udp   filecast
//#                          Eden Sherry <eden&pair.com>
//fxaengine-net   3402/tcp   FXa Engine Network Port
//fxaengine-net   3402/udp   FXa Engine Network Port
//#                          Lucas Alonso <luke&demiurgestudios.com> February 2002
//#               3403       De-registered on 2006-10-27
//#               3404       Removed (2002-05-01)
//nokia-ann-ch1   3405/tcp   Nokia Announcement ch 1
//nokia-ann-ch1   3405/udp   Nokia Announcement ch 1
//nokia-ann-ch2   3406/tcp   Nokia Announcement ch 2
//nokia-ann-ch2   3406/udp   Nokia Announcement ch 2
//#                          Morteza Kalhour <Morteza.Kalhour&Nokia.com> February 2002
//ldap-admin      3407/tcp   LDAP admin server port
//ldap-admin      3407/udp   LDAP admin server port
//#                          Stephen Tsun <stsun&calient.net> February 2002
//BESApi          3408/tcp   BES Api Port
//BESApi          3408/udp   BES Api Port
//#                          Colin Griffiths <colin.griffiths&interlinksoftware.com> February 2002
//networklens     3409/tcp   NetworkLens Event Port
//networklens     3409/udp   NetworkLens Event Port
//networklenss    3410/tcp   NetworkLens SSL Event
//networklenss    3410/udp   NetworkLens SSL Event
//#                          Greg Bailey <gbailey&lxpro.com> February 2002
//biolink-auth    3411/tcp   BioLink Authenteon server
//biolink-auth    3411/udp   BioLink Authenteon server
//#                          BioLink Support <reginfo&biolinkusa.com> February 2002
//xmlblaster      3412/tcp   xmlBlaster
//xmlblaster      3412/udp   xmlBlaster
//#                          Marcel Ruff <mr&marcelruff.info> February 2002
//svnet           3413/tcp   SpecView Networking
//svnet           3413/udp   SpecView Networking
//#                          Richard Dickins <rad&specview.com> February 2002
//wip-port        3414/tcp   BroadCloud WIP Port
//wip-port        3414/udp   BroadCloud WIP Port
//bcinameservice  3415/tcp   BCI Name Service
//bcinameservice  3415/udp   BCI Name Service
//#                          Dennis Parker <dparker&broadcloud.com> February 2002
//commandport     3416/tcp   AirMobile IS Command Port
//commandport     3416/udp   AirMobile IS Command Port
//#                          Mike Klein <m.klein&motorla.com> February 2002
//csvr            3417/tcp   ConServR file translation
//csvr            3417/udp   ConServR file translation
//#                          Albert Leung <aleung&biscom.com> February 2002
//rnmap           3418/tcp   Remote nmap
//rnmap           3418/udp   Remote nmap
//#                          Tuomo Makinen <tmakinen&pp.htv.fi> February 2002
//softaudit       3419/tcp   Isogon SoftAudit
//softaudit       3419/udp   ISogon SoftAudit
//#                          Per Hellberg <phellberg&isogon.com> February 2002
//ifcp-port       3420/tcp   iFCP User Port
//ifcp-port       3420/udp   iFCP User Port
//#                          RFC 4172 - September 2005
//bmap            3421/tcp   Bull Apprise portmapper
//bmap            3421/udp   Bull Apprise portmapper
//#                          Jeremy Gilbert <J.Gilbert&ma30.bull.com>
//rusb-sys-port   3422/tcp   Remote USB System Port
//rusb-sys-port   3422/udp   Remote USB System Port
//#                          Steven Klein <stevek&ionetworks.com> February 2002
//xtrm            3423/tcp   xTrade Reliable Messaging
//xtrm            3423/udp   xTrade Reliable Messaging
//xtrms           3424/tcp   xTrade over TLS/SSL
//xtrms           3424/udp   xTrade over TLS/SSL
//#                          Mats Nilsson <mats.nilsson&xware.se> February 2002
//agps-port       3425/tcp   AGPS Access Port
//agps-port       3425/udp   AGPS Access Port
//#                          Kristoffer Nilsson
//#                          <kristoffer.nilsson&hutchison3g.com> February 2002
//arkivio         3426/tcp   Arkivio Storage Protocol
//arkivio         3426/udp   Arkivio Storage Protocol
//#                          Bruce Greenblatt <bruce&arkivio.com> February 2002
//websphere-snmp  3427/tcp   WebSphere SNMP
//websphere-snmp  3427/udp   WebSphere SNMP
//#                          Richard Mills <ramills&us.ibm.com> February 2002
//twcss           3428/tcp   2Wire CSS
//twcss           3428/udp   2Wire CSS
//#                          2Wire IANA Contact <iana&2wire.com> February 2002
//gcsp            3429/tcp   GCSP user port
//gcsp            3429/udp   GCSP user port
//#                          Anirban Majumder <majumderanirban&lycos.com> March 2002
//ssdispatch      3430/tcp   Scott Studios Dispatch
//ssdispatch      3430/udp   Scott Studios Dispatch
//#                          Michael Settles <michael.settles&verizon.net> March 2002
//ndl-als         3431/tcp   Active License Server Port
//ndl-als         3431/udp   Active License Server Port
//#                          Quentin Brown <ndldev&ndl.co.uk> March 2002
//osdcp           3432/tcp   Secure Device Protocol
//osdcp           3432/udp   Secure Device Protocol
//#                          Peter Fernandez <fernandez&omnisec.ch> March 2002
//alta-smp        3433/tcp   Altaworks Service Management Platform
//alta-smp        3433/udp   Altaworks Service Management Platform
//#                          Ted Macomber <TedM&Altaworks.com> March 2002
//opencm          3434/tcp   OpenCM Server
//opencm          3434/udp   OpenCM Server
//#                          Jonathan S. Shapiro <registrar&eros-os.org> March 2002
//pacom           3435/tcp   Pacom Security User Port
//pacom           3435/udp   Pacom Security User Port
//#                          Steve Barton <steveb&pacom.com> March 2002
//gc-config       3436/tcp   GuardControl Exchange Protocol
//gc-config       3436/udp   GuardControl Exchange Protocol
//#                          Andreas Schwarz <andi&trancefield.de> March 2002
//autocueds       3437/tcp   Autocue Directory Service
//autocueds       3437/udp   Autocue Directory Service
//#                          Geoff Back <geoff&autocue.co.uk> March 2002
//spiral-admin    3438/tcp   Spiralcraft Admin
//spiral-admin    3438/udp   Spiralcraft Admin
//#                          Michael Toth <iana&spiralcraft.com> March 2002
//hri-port        3439/tcp   HRI Interface Port
//hri-port        3439/udp   HRI Interface Port
//#                          John Fayos <john.fayos&criticallink.com> March 2002
//ans-console     3440/tcp   Net Steward Mgmt Console
//ans-console     3440/udp   Net Steward Mgmt Console
//#                          John Richmond <developers&securitydesigners.com> March 2002
//connect-client  3441/tcp   OC Connect Client
//connect-client  3441/udp   OC Connect Client
//connect-server  3442/tcp   OC Connect Server
//connect-server  3442/udp   OC Connect Server
//#                          Mike Velten <mike.Velten&liebert.com> March 2002
//ov-nnm-websrv   3443/tcp   OpenView Network Node Manager WEB Server
//ov-nnm-websrv   3443/udp   OpenView Network Node Manager WEB Server
//#                          Anthony Walker <anthony_walker&hp.com> March 2002
//denali-server   3444/tcp   Denali Server
//denali-server   3444/udp   Denali Server
//#                          Joe Devlin <Joe.Devlin&rocketsoftware.com> March 2002
//monp            3445/tcp   Media Object Network
//monp            3445/udp   Media Object Network
//#                          Ron Herardian <rherardi&gssnet.com> March 2002
//3comfaxrpc      3446/tcp   3Com FAX RPC port
//3comfaxrpc      3446/udp   3Com FAX RPC port
//#                          Christopher Wells <christopher_wells&3com.com> April 2002
//directnet	3447/tcp   DirectNet IM System
//directnet	3447/udp   DirectNet IM System
//#                          Gregory Richards <Richards&codu.org> April 2002
//dnc-port        3448/tcp   Discovery and Net Config
//dnc-port        3448/udp   Discovery and Net Config
//#                          Chi Chen <chichen&us.ibm.com> April 2002
//hotu-chat       3449/tcp   HotU Chat
//hotu-chat       3449/udp   HotU Chat
//#                          Tim Burgess <tim&hotu.com> April 2002
//castorproxy     3450/tcp   CAStorProxy
//castorproxy     3450/udp   CAStorProxy
//#                          Raymond J. Young <Raymond.Young&ca.com> April 2002
//asam            3451/tcp   ASAM Services
//asam            3451/udp   ASAM Services
//#                          Mike Gossett <mike&omnibond.com> April 2002
//sabp-signal     3452/tcp   SABP-Signalling Protocol
//sabp-signal     3452/udp   SABP-Signalling Protocol
//#                          Brendan McWilliams <brendan.mcwilliams&vf.vodafone.co.uk> April 2002
//pscupd          3453/tcp   PSC Update Port
//pscupd          3453/udp   PSC Update Port
//#                          Reid B. Ligon <reid.ligon&pscnet.com>
//mira            3454/tcp   Apple Remote Access Protocol
//#                          Mike Alexander <mta&um.cc.umich.edu>
//prsvp           3455/tcp   RSVP Port
//prsvp           3455/udp   RSVP Port
//#                          Bob Braden <Braden&isi.edu>
//vat             3456/tcp   VAT default data
//vat             3456/udp   VAT default data
//#                          Van Jacobson <van&ee.lbl.gov>
//vat-control     3457/tcp   VAT default control
//vat-control     3457/udp   VAT default control
//#                          Van Jacobson <van&ee.lbl.gov>
//d3winosfi       3458/tcp   D3WinOSFI
//d3winosfi       3458/udp   D3WinOSFI
//#                          Brad Hamilton <bh&picksys.com>
//integral        3459/tcp   TIP Integral
//integral        3459/udp   TIP Integral
//#                          Olivier Mascia <om&tipgroup.com>
//edm-manager     3460/tcp   EDM Manger
//edm-manager     3460/udp   EDM Manger
//edm-stager      3461/tcp   EDM Stager
//edm-stager      3461/udp   EDM Stager
//edm-std-notify  3462/tcp   EDM STD Notify
//edm-std-notify  3462/udp   EDM STD Notify
//edm-adm-notify  3463/tcp   EDM ADM Notify
//edm-adm-notify  3463/udp   EDM ADM Notify
//edm-mgr-sync    3464/tcp   EDM MGR Sync
//edm-mgr-sync    3464/udp   EDM MGR Sync
//edm-mgr-cntrl   3465/tcp   EDM MGR Cntrl
//edm-mgr-cntrl   3465/udp   EDM MGR Cntrl
//#                          Tom Hennessy <thenn&novadigm.com>
//workflow        3466/tcp   WORKFLOW
//workflow        3466/udp   WORKFLOW
//#                          Robert Hufsky <rhufsky&csesys.co.at>
//rcst            3467/tcp   RCST
//rcst            3467/udp   RCST
//#                          Kit Sturgeon <Kit&remotecontrolsextoys.com>
//ttcmremotectrl  3468/tcp   TTCM Remote Controll
//ttcmremotectrl  3468/udp   TTCM Remote Controll
//#                          Yossi Cohen-Shahar <yossi&proxy.co.il>
//pluribus        3469/tcp   Pluribus
//pluribus        3469/udp   Pluribus
//#                          Mark Miller <markm&caplet.com>
//jt400           3470/tcp   jt400
//jt400           3470/udp   jt400
//jt400-ssl       3471/tcp   jt400-ssl
//jt400-ssl       3471/udp   jt400-ssl
//#                          Clifton Nock <cnock&us.ibm.com>
//jaugsremotec-1  3472/tcp   JAUGS N-G Remotec 1
//jaugsremotec-1  3472/udp   JAUGS N-G Remotec 1
//jaugsremotec-2  3473/tcp   JAUGS N-G Remotec 2
//jaugsremotec-2  3473/udp   JAUGS N-G Remotec 2
//#                          Steven B. Cliff <scliff&remotec-andros.com> April 2002
//ttntspauto      3474/tcp   TSP Automation
//ttntspauto      3474/udp   TSP Automation
//#                          Arnie Koster <akoster&teltone.com> April 2002
//genisar-port    3475/tcp   Genisar Comm Port
//genisar-port    3475/udp   Genisar Comm Port
//#                          Candace Niccolson <cniccolson&genisar.com> April 2002
//nppmp           3476/tcp   NVIDIA Mgmt Protocol
//nppmp           3476/udp   NVIDIA Mgmt Protocol
//#                          Gilbert Yeung <gyeung&nvidia.com> April 2002
//ecomm           3477/tcp   eComm link port
//ecomm           3477/udp   eComm link port
//#                          Thomas Soerensen <thomassoerensen&stofanet.dk> April 2002
//stun            3478/tcp   Session Traversal Utilities for NAT (STUN) port
//stun            3478/udp   Session Traversal Utilities for NAT (STUN) port
//#                          [RFC5389]
//twrpc           3479/tcp   2Wire RPC
//twrpc           3479/udp   2Wire RPC
//#                          2Wire IANA Contact <iana&2wire.com> April 2002
//plethora        3480/tcp   Secure Virtual Workspace
//plethora        3480/udp   Secure Virtual Workspace
//#                          Tim Simms <tsimms&plethoratech.com> April 2002
//cleanerliverc   3481/tcp   CleanerLive remote ctrl
//cleanerliverc   3481/udp   CleanerLive remote ctrl
//#                          David Mojdehi <david.mojdehi&autodesk.com> April 2002
//vulture         3482/tcp   Vulture Monitoring System
//vulture         3482/udp   Vulture Monitoring System
//#                          Jason Santos <jason.santos&megaslow.net> April 2002
//slim-devices    3483/tcp   Slim Devices Protocol
//slim-devices    3483/udp   Slim Devices Protocol
//#                          Sean Adams <sean&slimdevices.com> May 2002
//gbs-stp         3484/tcp   GBS SnapTalk Protocol
//gbs-stp         3484/udp   GBS SnapTalk Protocol
//#                          Eric Harris-Braun <eric&glassbead.com> May 2002
//celatalk        3485/tcp   CelaTalk
//celatalk        3485/udp   CelaTalk
//#                          Carl Blundell <cblundell&celador.co.uk> May 2002
//ifsf-hb-port    3486/tcp   IFSF Heartbeat Port
//ifsf-hb-port    3486/udp   IFSF Heartbeat Port
//#                          IFSF Secretary <secretary&ifsf.org> May 2002
//ltctcp          3487/tcp   LISA TCP Transfer Channel
//ltcudp          3487/udp   LISA UDP Transfer Channel
//#                          Pit Vetterick <pit&3dgo.com> May 2002
//fs-rh-srv       3488/tcp   FS Remote Host Server
//fs-rh-srv       3488/udp   FS Remote Host Server
//#                          Brian Nickles <ThingSpear91&hotmail.com> May 2002
//dtp-dia         3489/tcp   DTP/DIA
//dtp-dia         3489/udp   DTP/DIA
//#                          Alexei V. Soloviev <avsolov&lab127.karelia.ru> May 2002
//colubris        3490/tcp   Colubris Management Port
//colubris        3490/udp   Colubris Management Port
//#                          Gilbert Moineau <gilbert.moineau&colubris.com> May 2002
//swr-port        3491/tcp   SWR Port
//swr-port        3491/udp   SWR Port 
//#                          Ian Manning <imanning&dtsuk.com> May 2002
//tvdumtray-port  3492/tcp   TVDUM Tray Port
//tvdumtray-port  3492/udp   TVDUM Tray Port
//#                          Peter Boers <boers&isisglobal.nl> May 2002 
//nut             3493/tcp   Network UPS Tools
//nut             3493/udp   Network UPS Tools
//#                          Russell Kroll <nut-iana&exploits.org> May 2002
//ibm3494         3494/tcp   IBM 3494
//ibm3494         3494/udp   IBM 3494
//#                          Jeffrey Pilch <jpilch&us.ibm.com>
//seclayer-tcp    3495/tcp   securitylayer over tcp
//seclayer-tcp    3495/udp   securitylayer over tcp
//seclayer-tls    3496/tcp   securitylayer over tls
//seclayer-tls    3496/udp   securitylayer over tls
//#                          Arno Hollosi <arno.hollosi&cio.gv.at> March 2002
//ipether232port  3497/tcp   ipEther232Port
//ipether232port  3497/udp   ipEther232Port
//#                          Marcus Leufgen <leufgen&ipcas.de> May 2002
//dashpas-port    3498/tcp   DASHPAS user port
//dashpas-port    3498/udp   DASHPAS user port
//#                          Albrecht Mayer <albrecht.mayer&infineon.com> May 2002
//sccip-media     3499/tcp   SccIP Media
//sccip-media     3499/udp   SccIP Media
//#                          David Yon <dyon&dialout.net> May 2002
//rtmp-port       3500/tcp   RTMP Port
//rtmp-port       3500/udp   RTMP Port
//#                          Miriam Wohlgelernter <miriamw&adirtech.com>
//isoft-p2p       3501/tcp   iSoft-P2P
//isoft-p2p       3501/udp   iSoft-P2P
//#                          David Walling <dwalling&isoft.com>
//avinstalldisc   3502/tcp   Avocent Install Discovery
//avinstalldisc   3502/udp   Avocent Install Discovery
//#                          Brian S. Stewart <Brian.Stewart&Avovent.com>
//lsp-ping        3503/tcp   MPLS LSP-echo Port
//lsp-ping        3503/udp   MPLS LSP-echo Port
//#                          [RFC4379]
//ironstorm       3504/tcp   IronStorm game server
//ironstorm       3504/udp   IronStorm game server
//#                          Arnaud Clermonte <clermonte&4xtechnologies.com>
//ccmcomm         3505/tcp   CCM communications port
//ccmcomm         3505/udp   CCM communications port
//#                          Tom Bougan <tomb&apptechsys.com>
//apc-3506        3506/tcp   APC 3506
//apc-3506        3506/udp   APC 3506
//#                          American Power Conversion <ports&apcc.com>
//nesh-broker     3507/tcp   Nesh Broker Port
//nesh-broker     3507/udp   Nesh Broker Port
//#                          Jeremy Maiden <jeremy&komarr.demon.co.uk>
//interactionweb  3508/tcp   Interaction Web
//interactionweb  3508/udp   Interaction Web
//#                          Mike Gagle <mikeg&inin.com>
//vt-ssl          3509/tcp   Virtual Token SSL Port
//vt-ssl          3509/udp   Virtual Token SSL Port
//#                          Libor Sykora <libor.sykora&st.com> May 2002
//xss-port        3510/tcp   XSS Port
//xss-port        3510/udp   XSS Port
//#                          Joe Purcell <jpurcell&ensuretech.com> May 2002
//webmail-2       3511/tcp   WebMail/2
//webmail-2       3511/udp   WebMail/2
//#                          Dimitris Michelinakis <dimitris&michelinakis.gr> May 2002
//aztec           3512/tcp   Aztec Distribution Port
//aztec           3512/udp   Aztec Distribution Port
//#                          Alan Francis <AlanF&zonal.co.uk> May 2002
//arcpd           3513/tcp   Adaptec Remote Protocol
//arcpd           3513/udp   Adaptec Remote Protocol
//#                          Hardy Doelfel <hardy_doelfel&adaptec.com> May 2002
//must-p2p        3514/tcp   MUST Peer to Peer
//must-p2p        3514/udp   MUST Peer to Peer
//must-backplane  3515/tcp   MUST Backplane
//must-backplane  3515/udp   MUST Backplane
//#                          Rick Stefanik <r.stefanik&gatelinx.com> May 2002
//smartcard-port  3516/tcp   Smartcard Port
//smartcard-port  3516/udp   Smartcard Port 
//#                          Scott Guthery <sguthery&mobile-mind.com> May 2002
//802-11-iapp     3517/tcp   IEEE 802.11 WLANs WG IAPP
//802-11-iapp     3517/udp   IEEE 802.11 WLANs WG IAPP
//#                          Stuart J. Kerry (Chair IEEE 802.11 WG)
//#                          <stuart&ok-brit.com> May 2002
//artifact-msg    3518/tcp   Artifact Message Server
//artifact-msg    3518/udp   Artifact Message Server
//#                          Ron Capwell <ron&artifactsoftware.com> June 2002
//nvmsgd          3519/tcp   Netvion Messenger Port
//galileo         3519/udp   Netvion Galileo Port
//galileolog      3520/tcp   Netvion Galileo Log Port
//galileolog      3520/udp   Netvion Galileo Log Port
//#                          Ray Caruso <ray.caruso&netvion.com> June 2002
//mc3ss           3521/tcp   Telequip Labs MC3SS
//mc3ss           3521/udp   Telequip Labs MC3SS
//#                          Michael Sparks <msparks&telequiplabs.com> June 2002
//nssocketport    3522/tcp   DO over NSSocketPort
//nssocketport    3522/udp   DO over NSSocketPort
//#                          Douglas Davidson <drd&apple.com> June 2002
//odeumservlink   3523/tcp   Odeum Serverlink 
//odeumservlink   3523/udp   Odeum Serverlink
//#                          Mads Peter Back <iana-contact&webhouse.dk> June 2002
//ecmport         3524/tcp   ECM Server port
//ecmport         3524/udp   ECM Server port
//eisport         3525/tcp   EIS Server port
//eisport         3525/udp   EIS Server port
//#                          Paul Kraus <paul.kraus&veritas.com> June 2002
//starquiz-port   3526/tcp   starQuiz Port
//starquiz-port   3526/udp   starQuiz Port
//#                          Adam Ernst <contact&cosmicsoft.net> June 2002
//beserver-msg-q  3527/tcp   VERITAS Backup Exec Server
//beserver-msg-q  3527/udp   VERITAS Backup Exec Server
//#                          Katherine Wattwood <katherine.wattwood&veritas.com> June 2002
//jboss-iiop      3528/tcp   JBoss IIOP
//jboss-iiop      3528/udp   JBoss IIOP
//jboss-iiop-ssl  3529/tcp   JBoss IIOP/SSL
//jboss-iiop-ssl  3529/udp   JBoss IIOP/SSL
//#                          Francisco Reverbel <reverbel&ime.usp.br> June 2002
//gf              3530/tcp   Grid Friendly
//gf              3530/udp   Grid Friendly
//#                          Daivd P. Chassin <david.chassin&pnl.gov> June 2002
//joltid          3531/tcp   Joltid
//joltid          3531/udp   Joltid
//#                          Ahti Heinla <ahti&ahti.bluemoon.ee> June 2002
//raven-rmp       3532/tcp   Raven Remote Management Control
//raven-rmp       3532/udp   Raven Remote Management Control
//raven-rdp       3533/tcp   Raven Remote Management Data
//raven-rdp       3533/udp   Raven Remote Management Data
//#                          Daniel Sorlov <daniel&sorlov.com> June 2002
//urld-port       3534/tcp   URL Daemon Port
//urld-port       3534/udp   URL Daemon Port
//#                          Jim Binkley <jrb&cs.pdx.edu> June 2002
//ms-la           3535/tcp   MS-LA
//ms-la           3535/udp   MS-LA
//#                          Eric Ledoux <ericle&microsoft.com> 
//snac            3536/tcp   SNAC
//snac            3536/udp   SNAC
//#                          Tatsuya Igarashi <Tatsuya.Igarashi&jp.sony.com> July 2002
//ni-visa-remote  3537/tcp   Remote NI-VISA port
//ni-visa-remote  3537/udp   Remote NI-VISA port
//#                          Sinnadurai Dharshan <sinnadurai.dharshan&ni.com> July 2002
//ibm-diradm      3538/tcp   IBM Directory Server
//ibm-diradm      3538/udp   IBM Directory Server
//ibm-diradm-ssl  3539/tcp   IBM Directory Server SSL
//ibm-diradm-ssl  3539/udp   IBM Directory Server SSL
//#                          Mark Cavage <mcavage&us.ibm.com> July 2002
//pnrp-port       3540/tcp   PNRP User Port
//pnrp-port       3540/udp   PNRP User Port
//#                          Igor Kostic <igorko&microsoft.com> July 2002
//voispeed-port   3541/tcp   VoiSpeed Port
//voispeed-port   3541/udp   VoiSpeed Port
//#                          Virgilio Lattanzi <virgilio&harpax.com> July 2002
//hacl-monitor    3542/tcp   HA cluster monitor
//hacl-monitor    3542/udp   HA cluster monitor
//#                          Jason Ko <jason_ko&hp.com> July 2002
//qftest-lookup   3543/tcp   qftest Lookup Port
//qftest-lookup   3543/udp   qftest Lookup Port
//#                          Gregor Schmid <gs&qfs.de> July 2002
//teredo          3544/tcp   Teredo Port
//teredo          3544/udp   Teredo Port
//#                          Dave Thaler <dthaler&microsoft.com> July 2002
//camac           3545/tcp   CAMAC equipment
3545,//camac           3545/udp   CAMAC equipment
//#                          Eugene Zhiganov <zed&dfe3300.karelia.ru> July 2002
//#               3546       Unassigned (removed September 2002)
3547,//symantec-sim    3547/tcp   Symantec SIM
//symantec-sim    3547/udp   Symantec SIM
//#                          George Dzieciol <gdzieciol&symantec.com> July 2002
//interworld      3548/tcp   Interworld
//interworld      3548/udp   Interworld
//#                          John Stephen <iana&mundocani.com> July 2002
//tellumat-nms    3549/tcp   Tellumat MDR NMS 
//tellumat-nms    3549/udp   Tellumat MDR NMS
//#                          Hennie van der Merwe <hvandermerwe&tellumat.com> July 2002
//ssmpp           3550/tcp   Secure SMPP
//ssmpp           3550/udp   Secure SMPP
//#                          Cormac Long <webmaster&smsforum.net> July 2002
//apcupsd         3551/tcp   Apcupsd Information Port
//apcupsd         3551/udp   Apcupsd Information Port
//#                          Riccardo Facchetti <riccardo&inetcosmos.org> July 2002
//taserver        3552/tcp   TeamAgenda Server Port
//taserver        3552/udp   TeamAgenda Server Port
//#                          Dany Ayotte <ayotte&teamsoft.com> July 2002
//rbr-discovery   3553/tcp   Red Box Recorder ADP
//rbr-discovery   3553/udp   Red Box Recorder ADP
//#                          Simon Jolly <simon.jolly&origin-data.co.uk> July 2002
//questnotify     3554/tcp   Quest Notification Server
//questnotify     3554/udp   Quest Notification Server
//#                          Rob Griffin <quest_iana&oz.quest.com> July 2002
//razor           3555/tcp   Vipul's Razor
//razor           3555/udp   Vipul's Razor
//#                          Vipul Ved Prakash <mail&vipul.net> July 2002
//sky-transport   3556/tcp   Sky Transport Protocol
//sky-transport   3556/udp   Sky Transport Protocol
//#                          Michael Paddon <michael.paddon&activesky.com> July 2002
//personalos-001  3557/tcp   PersonalOS Comm Port
//personalos-001  3557/udp   PersonalOS Comm Port
//#                          Shane Roberts <shane&shaneroberts.com> July 2002
//mcp-port        3558/tcp   MCP user port
//mcp-port        3558/udp   MCP user port
//#                          Professor Paul S. Wang <pwang&cs.kent.edu> July 2002
//cctv-port       3559/tcp   CCTV control port
//cctv-port       3559/udp   CCTV control port
//#                          John Skidmore <JSkidmore&vicon-cctv.com> July 2002
//iniserve-port   3560/tcp   INIServe port
//iniserve-port   3560/udp   INIServe port
//#                          Peter Moylan <peter&ee.newcastle.edu.au> August 2002
//bmc-onekey      3561/tcp   BMC-OneKey
//bmc-onekey      3561/udp   BMC-OneKey
//#                          Portnoy Boxman <portnoy_boxman&bmc.com> August 2002
//sdbproxy        3562/tcp   SDBProxy
//sdbproxy        3562/udp   SDBProxy
//#                          Eric Grange <egrange&creative-it.net> August 2002   
//watcomdebug     3563/tcp   Watcom Debug
//watcomdebug     3563/udp   Watcom Debug
//#                          Dave Neudoerffer <Dave.Neudoerffer&ianywhere.com>
//esimport        3564/tcp   Electromed SIM port
//esimport        3564/udp   Electromed SIM port
//#                          Francois Marchand <francois.marchand&electromed.com> August 2002
//m2pa            3565/tcp   M2PA
//m2pa            3565/sctp  M2PA
//#                          [RFC4165]
//quest-launcher  3566/tcp   Quest Agent Manager
//quest-launcher  3566/udp   Quest Agent Manager
//#                          Eyal Kalderon <eyal.kalderon&quest.com> April 2002
//oap		3567/tcp   Object Access Protocol
//oap		3567/udp   Object Access Protocol
//#                          Bryant Eastham <protocols&pewla.us.pewg.panasonic.com> August 2002
//oap-s		3568/tcp   Object Access Protocol over SSL
//oap-s		3568/udp   Object Access Protocol over SSL
//#                          Bryant Eastham <protocols&pewla.us.pewg.panasonic.com> January 2003
//mbg-ctrl        3569/tcp   Meinberg Control Service
//mbg-ctrl        3569/udp   Meinberg Control Service
//#                          Martin Burnicki <martin.burnicki&meinberg.de> August 2002
//mccwebsvr-port  3570/tcp   MCC Web Server Port
//mccwebsvr-port  3570/udp   MCC Web Server Port
//megardsvr-port  3571/tcp   MegaRAID Server Port
//megardsvr-port  3571/udp   MegaRAID Server Port
//megaregsvrport  3572/tcp   Registration Server Port
//megaregsvrport  3572/udp   Registration Server Port
//#                          Sreenivas Bagalkote <sreenib&lsil.com> August 2002
//tag-ups-1       3573/tcp   Advantage Group UPS Suite
//tag-ups-1       3573/udp   Advantage Group UPS Suite
//#                          James Goddard <jamesg&taglim.com> August 2002
//dmaf-server     3574/tcp   DMAF Server
//dmaf-caster     3574/udp   DMAF Caster
//#                          Ramakrishna Nadendla <rama_nadendla&agilent.com> August 2002
//ccm-port        3575/tcp   Coalsere CCM Port
//ccm-port        3575/udp   Coalsere CCM Port
//cmc-port        3576/tcp   Coalsere CMC Port
//cmc-port        3576/udp   Coalsere CMC Port
//#                          Chris Hawkinson <chawkinson&coalsere.com> August 2002
//config-port     3577/tcp   Configuration Port
//config-port     3577/udp   Configuration Port
//data-port       3578/tcp   Data Port
//data-port       3578/udp   Data Port
//#                          Anupam Bharali <ianaports&juniper.net> August 2002
//ttat3lb         3579/tcp   Tarantella Load Balancing
//ttat3lb         3579/udp   Tarantella Load Balancing
//#                          Jim Musgrave <jimm&tarantella.com> August 2002
//nati-svrloc     3580/tcp   NATI-ServiceLocator
//nati-svrloc     3580/udp   NATI-ServiceLocator
//#                          Jason Case <jason.case&ni.com> August 2002
//kfxaclicensing  3581/tcp   Ascent Capture Licensing
//kfxaclicensing  3581/udp   Ascent Capture Licensing
//#                          Brad Hamilton <brad_hamilton&kofax.com> August 2002
//press           3582/tcp   PEG PRESS Server
//press           3582/udp   PEG PRESS Server
//#                          Jim DeLisle <jdelisle&swellsoftware.com> August 2002
//canex-watch     3583/tcp   CANEX Watch System
//canex-watch     3583/udp   CANEX Watch System
//#                          Peter Kollath <peter.kollath&canex.sk> August 2002
//u-dbap          3584/tcp   U-DBase Access Protocol
//u-dbap          3584/udp   U-DBase Access Protocol
//#                          Bodo Rueskamp <br&itchigo.com> August 2002
//emprise-lls     3585/tcp   Emprise License Server
//emprise-lls     3585/udp   Emprise License Server
//emprise-lsc     3586/tcp   License Server Console
//emprise-lsc     3586/udp   License Server Console
//#                          James J. Diaz <JDiaz&EmpriseCorporation.com> August 2002
//p2pgroup        3587/tcp   Peer to Peer Grouping
//p2pgroup        3587/udp   Peer to Peer Grouping
//#                          Igor Kostic <igorko&microsoft.com> August 2002
//sentinel        3588/tcp   Sentinel Server
//sentinel        3588/udp   Sentinel Server
//#                          Ian Gordon <ian.s.gordon&btopenworld.com> August 2002
//isomair         3589/tcp   isomair
//isomair         3589/udp   isomair
//#                          Richard Fleming <richard&apoapsis.com> August 2002
//wv-csp-sms      3590/tcp   WV CSP SMS Binding
//wv-csp-sms      3590/udp   WV CSP SMS Binding
//#                          Matti Salmi <matti.salmi&nokia.com> August 2002
//gtrack-server   3591/tcp   LOCANIS G-TRACK Server
//gtrack-server   3591/udp   LOCANIS G-TRACK Server
//gtrack-ne       3592/tcp   LOCANIS G-TRACK NE Port
//gtrack-ne       3592/udp   LOCANIS G-TRACK NE Port
//#                          Juergen.Edelhaeuser <Juergen.Edelhaeuser&locanis.com> August 2002
//bpmd            3593/tcp   BP Model Debugger
//bpmd            3593/udp   BP Model Debugger
//#                          Keith Fligg <keith&projtech.com> September 2002
//mediaspace      3594/tcp   MediaSpace
//mediaspace      3594/udp   MediaSpace
//shareapp        3595/tcp   ShareApp
//shareapp        3595/udp   ShareApp
//#                          Jeff King <jking&wave3software.com> September 2002
//iw-mmogame      3596/tcp   Illusion Wireless MMOG
//iw-mmogame      3596/udp   Illusion Wireless MMOG
//#                          Jan Vrsinsky <jan.vrsinsky&illusionsoftworks.com> September 2002
//a14             3597/tcp   A14 (AN-to-SC/MM)
//a14             3597/udp   A14 (AN-to-SC/MM)
//a15             3598/tcp   A15 (AN-to-AN)
//a15             3598/udp   A15 (AN-to-AN)
//#                          David Ott <dott&qualcomm.com> September 2002
//quasar-server   3599/tcp   Quasar Accounting Server
//quasar-server   3599/udp   Quasar Accounting Server
//#                          Brad Pepers <brad&linuxcanada.com> September 2002
//trap-daemon     3600/tcp   text relay-answer
//trap-daemon     3600/udp   text relay-answer
//#                          John Willis <jwillis&arielusa.com> September 2002
//visinet-gui     3601/tcp   Visinet Gui
//visinet-gui     3601/udp   Visinet Gui
//#                          Jeff Douglass <ist&att.net> September 2002
//infiniswitchcl  3602/tcp   InfiniSwitch Mgr Client
//infiniswitchcl  3602/udp   InfiniSwitch Mgr Client
//#                          Lee VanTine <lvantine&infiniswitc.com> September 2002
//int-rcv-cntrl   3603/tcp   Integrated Rcvr Control
//int-rcv-cntrl   3603/udp   Integrated Rcvr Control
//#                          Dave Stone <dstone01&harris.com> September 2002
//bmc-jmx-port    3604/tcp   BMC JMX Port
//bmc-jmx-port    3604/udp   BMC JMX Port
//#                          Portnoy Boxman <portnoy_boxman&bmc.com> September 2002
//comcam-io       3605/tcp   ComCam IO Port
//comcam-io       3605/udp   ComCam IO Port
//#                          Don Gilbreath <don&comcam.net> September 2002
//splitlock       3606/tcp   Splitlock Server
//splitlock       3606/udp   Splitlock Server
//#                          Andrew Tune <Andrew.Tune&splitlock.com> September 2002
//precise-i3      3607/tcp   Precise I3
//precise-i3      3607/udp   Precise I3
//#                          Tomer Shain <tshain&precise.com> September 2002
//trendchip-dcp   3608/tcp   Trendchip control protocol
//trendchip-dcp   3608/udp   Trendchip control protocol
//#                          Ming-Jen Chen <mjchen&trendchip.com.tw> September 2002
//cpdi-pidas-cm   3609/tcp   CPDI PIDAS Connection Mon
//cpdi-pidas-cm   3609/udp   CPDI PIDAS Connection Mon
//#                          Tony Splaver <tony&cpdi.com> September 2002
//echonet         3610/tcp   ECHONET
//echonet         3610/udp   ECHONET
//#                          Takeshi Saito <takeshi.saito&toshiba.co.jp> September 2002
//six-degrees     3611/tcp   Six Degrees Port
//six-degrees     3611/udp   Six Degrees Port
//#                          Zach Nies <znies&creo.com> September 2002
//hp-dataprotect  3612/tcp   HP Data Protector
//hp-dataprotect  3612/udp   HP Data Protector
//#                          Stephen Gold <stephen_gold&hp.com> September 2002
//alaris-disc     3613/tcp   Alaris Device Discovery
//alaris-disc     3613/udp   Alaris Device Discovery
//#                          Chris Dern <cdern&nospam.alarismed.com> October 2002, June 2004
//sigma-port      3614/tcp   Invensys Sigma Port
//sigma-port      3614/udp   Invensys Sigma Port
//#                          Dr. Sajed Husein <sajed.husein&invensys.com> October 2002
//start-network   3615/tcp   Start Messaging Network
//start-network   3615/udp   Start Messaging Network
//#                          Peter Rocca <rocca&multiboard.com> October 2002
//cd3o-protocol   3616/tcp   cd3o Control Protocol
//cd3o-protocol   3616/udp   cd3o Control Protocol
//#                          Chris Wilcox <cwilcox&cd3o.com> October 2002
//sharp-server    3617/tcp   ATI SHARP Logic Engine
//sharp-server    3617/udp   ATI SHARP Logic Engine  
//#                          Bill Reveile <breveile&allentek.com>
//aairnet-1       3618/tcp   AAIR-Network 1
//aairnet-1       3618/udp   AAIR-Network 1
//aairnet-2       3619/tcp   AAIR-Network 2 
//aairnet-2       3619/udp   AAIR-Network 2
//#                          James Mealey <jymealey&yahoo.com> October 2002
//ep-pcp          3620/tcp   EPSON Projector Control Port
//ep-pcp          3620/udp   EPSON Projector Control Port
//ep-nsp          3621/tcp   EPSON Network Screen Port
//ep-nsp          3621/udp   EPSON Network Screen Port
//#                          SEIKO EPSON <Sato.Minoru3&exc.epson.co.jp> October 2002
//ff-lr-port      3622/tcp   FF LAN Redundancy Port
//ff-lr-port      3622/udp   FF LAN Redundancy Port
//#                          Fieldbus Foundation <dave.glanzer&fieldbus.org> October 2002
//haipe-discover  3623/tcp   HAIPIS Dynamic Discovery
//haipe-discover  3623/udp   HAIPIS Dynamic Discovery
//#                          Mike Irani <irani_mike&bah.com> October 2002
//dist-upgrade    3624/tcp   Distributed Upgrade Port
//dist-upgrade    3624/udp   Distributed Upgrade Port
//#                          Jason Schoon <jason.schoon&intermec.com> October 2002
//volley          3625/tcp   Volley
//volley          3625/udp   Volley
//#                          David Catmull <uncommon&uncommonplace.com> October 2002
//bvcdaemon-port  3626/tcp   bvControl Daemon
//bvcdaemon-port  3626/udp   bvControl Daemon
//#                          Ravi Gokhale <rgokhale&bindview.com> October 2002
//jamserverport   3627/tcp   Jam Server Port
//jamserverport   3627/udp   Jam Server Port
//#                          Art Pope <apope&sarnoff.com> October 2002
//ept-machine     3628/tcp   EPT Machine Interface
//ept-machine     3628/udp   EPT Machine Interface
//#                          Victor H. Farrace <vfarrace&eaglept.com> October 2002
//escvpnet        3629/tcp   ESC/VP.net
//escvpnet        3629/udp   ESC/VP.net
//#                          Hiroyuki Hashimoto <easymp&exc.epson.co.jp> October 2002
//cs-remote-db    3630/tcp   C&S Remote Database Port
//cs-remote-db    3630/udp   C&S Remote Database Port
//cs-services     3631/tcp   C&S Web Services Port
//cs-services     3631/udp   C&S Web Services Port
//#                          Computer Software GmbH <BrunoRistok&cs-ag.de> October 2002
//distcc          3632/tcp   distributed compiler
//distcc          3632/udp   distributed compiler
//#                          Martin Pool <mbp&samba.org> November 2002
//wacp            3633/tcp   Wyrnix AIS port
//wacp            3633/udp   Wyrnix AIS port
//#                          Harry T. Vennik <htvennik&zonnet.nl> November 2002
//hlibmgr         3634/tcp   hNTSP Library Manager
//hlibmgr         3634/udp   hNTSP Library Manager 
//#                          Kenji Tetsuyama <kenji&onkyo.co.jp> November 2002
//sdo             3635/tcp   Simple Distributed Objects
//sdo             3635/udp   Simple Distributed Objects
//#                          Alexander Philippou <alex&noemax.com> November 2002
//servistaitsm    3636/tcp   SerVistaITSM
//servistaitsm    3636/udp   SerVistaITSM
//#                          Ralph Campbell <ralph.campbell&xasystems.com> November 2002
//scservp         3637/tcp   Customer Service Port
//scservp         3637/udp   Customer Service Port
//#                          Jonathan A. Zdziarski <johathan&networkdweebs.com> November 2002
//ehp-backup      3638/tcp   EHP Backup Protocol
//ehp-backup      3638/udp   EHP Backup Protocol
//#                          Ed Fair <ed_fair&yahoo.com> November 2002
//xap-ha          3639/tcp   Extensible Automation 
//xap-ha          3639/udp   Extensible Automation 
//#                          Mark Harrison <Mark&xapautomation.org> November 2002
//netplay-port1   3640/tcp   Netplay Port 1
//netplay-port1   3640/udp   Netplay Port 1
//netplay-port2   3641/tcp   Netplay Port 2
//netplay-port2   3641/udp   Netplay Port 2
//#                          Predrag Filipovic <pfilipovic&digital5.com> November 2002
//juxml-port      3642/tcp   Juxml Replication port
//juxml-port      3642/udp   Juxml Replication port
//#                          Colin Reid <creid&projux.com> November 2002
//audiojuggler    3643/tcp   AudioJuggler
//audiojuggler    3643/udp   AudioJuggler
//#                          Morten Mertner <mm&audiojuggler.com> November 2002
//ssowatch        3644/tcp   ssowatch
//ssowatch        3644/udp   ssowatch
//#                          Marie-France Dubreuil <Marie-France.Dubreuil&evidian.com> November 2002
//cyc             3645/tcp   Cyc
//cyc             3645/udp   Cyc 
//#                          Stephen Reed <reed&cyc.com> January 2003            
//xss-srv-port    3646/tcp   XSS Server Port
//xss-srv-port    3646/udp   XSS Server Port
//#                          Joe Purcell <jpurcell&ensuretech.com> January 2003
//splitlock-gw    3647/tcp   Splitlock Gateway
//splitlock-gw    3647/udp   Splitlock Gateway
//#                          Andrew Tune <Andrew.Tune&splitlock.com> January 2003
//fjcp            3648/tcp   Fujitsu Cooperation Port
//fjcp            3648/udp   Fujitsu Cooperation Port
//#                          Kouji Sugisawa <sugisawa.kouji&soft.fujitsu.com> January 2003
//nmmp            3649/tcp   Nishioka Miyuki Msg Protocol
//nmmp            3649/udp   Nishioka Miyuki Msg Protocol
//#                          TAKEDA Hiroyuki <takeda&atashi.net> January 2003
//prismiq-plugin  3650/tcp   PRISMIQ VOD plug-in
//prismiq-plugin  3650/udp   PRISMIQ VOD plug-in
//#                          Richard Hodges <rhodges&prismiq.com> January 2003
//xrpc-registry   3651/tcp   XRPC Registry
//xrpc-registry   3651/udp   XRPC Registry
//#                          Slava Monich <Slava.Monich&nokia.com> January 2003
//vxcrnbuport     3652/tcp   VxCR NBU Default Port
//vxcrnbuport     3652/udp   VxCR NBU Default Port
//#                          Boris Star <boris.star&veritas.com> January 2003
//tsp             3653/tcp   Tunnel Setup Protocol
//tsp             3653/udp   Tunnel Setup Protocol
//#                          Marc Blanchet <marc.blanchet&viagenie.ca> January 2003
//#                          [RFC-blanchet-v6ops-tunnelbroker-tsp-04.txt] 
//vaprtm          3654/tcp   VAP RealTime Messenger
//vaprtm          3654/udp   VAP RealTime Messenger
//#                          Boris Polevoy <vapcom&mail.ru> January 2003
//abatemgr        3655/tcp   ActiveBatch Exec Agent
//abatemgr        3655/udp   ActiveBatch Exec Agent 
//abatjss         3656/tcp   ActiveBatch Job Scheduler
//abatjss         3656/udp   ActiveBatch Job Scheduler
//#                          Ben Rosenberg <brosenberg&advsyscon.com> January 2003
//immedianet-bcn  3657/tcp   ImmediaNet Beacon
//immedianet-bcn  3657/udp   ImmediaNet Beacon
//#                          Bill Homan <bhoman&spanworks.com> January 2003
//ps-ams          3658/tcp   PlayStation AMS (Secure)
//ps-ams          3658/udp   PlayStation AMS (Secure)
//#                          Edgar Alan Tu <Edgar_Tu&playstation.sony.com> January 2003
//apple-sasl      3659/tcp   Apple SASL
//apple-sasl      3659/udp   Apple SASL
//#                          David M. O'Rourke <daveo&apple.com> January 2003
//can-nds-ssl     3660/tcp   IBM Tivoli Directory Service using SSL
//can-nds-ssl     3660/udp   IBM Tivoli Directory Service using SSL
//can-ferret-ssl  3661/tcp   IBM Tivoli Directory Service using SSL
//can-ferret-ssl  3661/udp   IBM Tivoli Directory Service using SSL
//#                          Nic Catrambone <ncatramb&us.ibm.com> January 2003
//pserver         3662/tcp   pserver
//pserver         3662/udp   pserver
//#                          Patrick Furlong <pfurlong&darkknight.ca> January 2003
//dtp             3663/tcp   DIRECWAY Tunnel Protocol
//dtp             3663/udp   DIRECWAY Tunnel Protocol
//#                          John Border <border&hns.com> January 2003
//ups-engine      3664/tcp   UPS Engine Port
//ups-engine      3664/udp   UPS Engine Port
//ent-engine      3665/tcp   Enterprise Engine Port
//ent-engine      3665/udp   Enterprise Engine Port
//#                          Mike Delgrosso <mdelgros&tripplite.com> January 2003
//eserver-pap     3666/tcp   IBM eServer PAP
//eserver-pap     3666/udp   IBM EServer PAP
//#                          Dave Gimpl <gimpl&us.ibm.com> January 2003
//infoexch        3667/tcp   IBM Information Exchange
//infoexch        3667/udp   IBM Information Exchange
//#                          Paul Ford-Hutchinson <paulfordh&uk.ibm.com> January 2003
//dell-rm-port    3668/tcp   Dell Remote Management
//dell-rm-port    3668/udp   Dell Remote Management
//#                          Bradley Bransom <bradley_bransom&dell.com> January 2003
//casanswmgmt     3669/tcp   CA SAN Switch Management
//casanswmgmt     3669/udp   CA SAN Switch Management
//#                          Emre Tunar <emre.tunar&ca.com> January 2003
//smile           3670/tcp   SMILE TCP/UDP Interface
//smile           3670/udp   SMILE TCP/UDP Interface
//#                          Andre Petras <#remove#a.petras&arcor.de#remove_too#> January 2003
//efcp            3671/tcp   e Field Control (EIBnet)
//efcp            3671/udp   e Field Control (EIBnet)
//#                          Marc Goossens <mgoossens&eiba.com> January 2003
//lispworks-orb   3672/tcp   LispWorks ORB
//lispworks-orb   3672/udp   LispWorks ORB
//#                          Lisp Support <lisp-support&xanalys.com>
//mediavault-gui  3673/tcp   Openview Media Vault GUI
//mediavault-gui  3673/udp   Openview Media Vault GUI
//#                          Stephen Gold <stephen_gold&hp.com> January 2003
//wininstall-ipc  3674/tcp   WinINSTALL IPC Port
//wininstall-ipc  3674/udp   WinINSTALL IPC Port
//#                          Previous contact: Bill Somerville <Bill.Somerville&attachmate.com> January 2003
//#                          Current contact: Bill Somerville <Bill.Somerville&scalable.com> 13 August 2008
//calltrax        3675/tcp   CallTrax Data Port
//calltrax        3675/udp   CallTrax Data Port
//#                          Oliver Bailey <zzf66jjlm&time-lines.com> January 2003
//va-pacbase      3676/tcp   VisualAge Pacbase server
//va-pacbase      3676/udp   VisualAge Pacbase server
//#                          Dominique Lelievre <dominique.lelievre&fr.ibm.com> January 2003
//roverlog        3677/tcp   RoverLog IPC
//roverlog        3677/udp   RoverLog IPC
//#                          Tom Mayo <tmayo1&rochester.rr.com> January 2003
//ipr-dglt        3678/tcp   DataGuardianLT
//ipr-dglt        3678/udp   DataGuardianLT
//#                          Bruce Carlson <bruce.carlson&iprintl.com> January 2003
//newton-dock     3679/tcp   Newton Dock
//newton-dock     3679/udp   Newton Dock
//npds-tracker    3680/tcp   NPDS HostNode
//npds-tracker    3680/udp   NPDS HostNode
//#                          Paul Guyot <pguyot&kallisys.net> January 2003
//bts-x73         3681/tcp   BTS X73 Port
//bts-x73         3681/udp   BTS X73 Port
//#                          Todd Cooper <todd&DO11073.com> January 2003
//cas-mapi        3682/tcp   EMC SmartPackets-MAPI
//cas-mapi        3682/udp   EMC SmartPackets-MAPI
//#                          Koen Schoofs <schoofs_koen&emc.com> January 2003
//bmc-ea          3683/tcp   BMC EDV/EA
//bmc-ea          3683/udp   BMC EDV/EA
//#                          Portnoy Boxman <portnoy_boxman&bmc.com> January 2003
//faxstfx-port    3684/tcp   FAXstfX
//faxstfx-port    3684/udp   FAXstfX
//#                          Alec Carlson <acarlson&smithmicro.com> January 2003
//dsx-agent       3685/tcp   DS Expert Agent
//dsx-agent       3685/udp   DS Expert Agent
//#                          Previous contact: NetPro Computing <ports&netpro.com> January 2003
//#                          New contacts: Jason Lockett <Jay.Lockett&quest.com> 16 December 2008
//#                          New contacts: Melanie Kacerek <melanie.kacerek&quest.com> 16 December 2008
//tnmpv2          3686/tcp   Trivial Network Management
//tnmpv2          3686/udp   Trivial Network Management
//#                          Andrea Premoli <Andrea_maria.Premoli&icn.siemens.it> January 2003
//simple-push     3687/tcp   simple-push
//simple-push     3687/udp   simple-push
//simple-push-s   3688/tcp   simple-push Secure
//simple-push-s   3688/udp   simple-push Secure
//#                          C. Enrique Ortiz <eortiz&j2medeveloper.com> January 2003
//daap            3689/tcp   Digital Audio Access Protocol
//daap            3689/udp   Digital Audio Access Protocol
//#                          Amandeep Jawa <daap&apple.com> January 2003
//svn             3690/tcp   Subversion
//svn             3690/udp   Subversion
//#                          Greg Hudson <ghudson&mit.edu> January 2003
//magaya-network  3691/tcp   Magaya Network Port
//magaya-network  3691/udp   Magaya Network Port
//#                          Jesus David Rodriguez <jesusdavid&magaya.com> February 2003
//intelsync       3692/tcp   Brimstone IntelSync
3692,//intelsync       3692/udp   Brimstone IntelSync
//#                          Davey Taylor <davey.taylor&brimstone.net> February 2003
//#               3693-3694  Unassigned (Removed 2007-04-05)
3695,//bmc-data-coll   3695/tcp   BMC Data Collection
//bmc-data-coll   3695/udp   BMC Data Collection
//#                          Portnoy Boxman <portnoy_boxman&bmc.com> February 2003
//telnetcpcd      3696/tcp   Telnet Com Port Control
//telnetcpcd      3696/udp   Telnet Com Port Control
//#                          Thomas J. Pinkl <tom&pinkl.com> February 2003
//nw-license      3697/tcp   NavisWorks License System
//nw-license      3697/udp   NavisWorks Licnese System
//#                          Tim Wiegand <tim.wiegand&navisworks.com> February 2003
//sagectlpanel    3698/tcp   SAGECTLPANEL
//sagectlpanel    3698/udp   SAGECTLPANEL
//#                          Mark Gamble <mark.gamble&sage.com> February 2003
//kpn-icw         3699/tcp   Internet Call Waiting
//kpn-icw         3699/udp   Internet Call Waiting
//#                          B.J. Kortekaas <b.j.kortekaas&kpn.com> February 2003
//lrs-paging      3700/tcp   LRS NetPage
//lrs-paging      3700/udp   LRS NetPage
//#                          Geoffrey Wossum <geoffrey&pager.net> February 2003
//netcelera       3701/tcp   NetCelera
//netcelera       3701/udp   NetCelera 
//#                          Tarek Nabhan <standards&itworx.com> February 2003
//ws-discovery    3702/tcp   Web Service Discovery
//ws-discovery    3702/udp   Web Service Discovery
//#                          Christian Huitema <huitema&microsoft.com> February 2003
//adobeserver-3   3703/tcp   Adobe Server 3
//adobeserver-3   3703/udp   Adobe Server 3
//adobeserver-4   3704/tcp   Adobe Server 4
//adobeserver-4   3704/udp   Adobe Server 4
//#                          Frank Soetebeer <frsoeteb&adobe.com> January 2003
//adobeserver-5   3705/tcp   Adobe Server 5
//adobeserver-5   3705/udp   Adobe Server 5
//#                          Previous Contact: Frank Soetebeer <frsoeteb&adobe.com> January 2003
//#                          Current Contact: Bernd Paradies <bparadie&adobe.com> 14 January 2008
//rt-event        3706/tcp   Real-Time Event Port
//rt-event        3706/udp   Real-Time Event Port
//rt-event-s      3707/tcp   Real-Time Event Secure Port
//rt-event-s      3707/udp   Real-Time Event Secure Port
//#                          Terry Gin <terry_gin&inter-tel.com> February 2003
//sun-as-iiops    3708/tcp   Sun App Svr - Naming
//sun-as-iiops    3708/udp   Sun App Svr - Naming
//#                          Abhijit Kumar <as-iana-ports&sun.com> November 2005
//ca-idms         3709/tcp   CA-IDMS Server
//ca-idms         3709/udp   CA-IDMS Server
//#                          Dave Ross <david.ross&ca.com> 
//portgate-auth   3710/tcp   PortGate Authentication
//portgate-auth   3710/udp   PortGate Authentication
//#                          Scott Harris <Scott&XRamp.com> February 2003
//edb-server2     3711/tcp   EBD Server 2
//edb-server2     3711/udp   EBD Server 2
//#                          Carlos Portela <cportela&simple-sw.com> February 2003
//sentinel-ent    3712/tcp   Sentinel Enterprise
//sentinel-ent    3712/udp   Sentinel Enterprise
//#                          Ian Gordon <ian&n-genltd.co.uk> March 2003
//tftps           3713/tcp   TFTP over TLS
//tftps           3713/udp   TFTP over TLS
//#                          Mark mayernick <Mark.Mayernick&thomson.net> March 2003
//delos-dms       3714/tcp   DELOS Direct Messaging
//delos-dms       3714/udp   DELOS Direct Messaging
//#                          Ekkehard Morgenstern <ekkehard&ekkehardmorgenstern.de> March 2003
//anoto-rendezv   3715/tcp   Anoto Rendezvous Port
//anoto-rendezv   3715/udp   Anoto Rendezvous Port
//#                          Ola Sandstrom <ola.sandstrom&anoto.com> March 2003
//wv-csp-sms-cir  3716/tcp   WV CSP SMS CIR Channel
//wv-csp-sms-cir  3716/udp   WV CSP SMS CIR Channel
//wv-csp-udp-cir  3717/tcp   WV CSP UDP/IP CIR Channel
//wv-csp-udp-cir  3717/udp   WV CSP UDP/IP CIR Channel
//#                          Jon Ingi Ingimundarson <jii&oz.com> March 2003
//opus-services   3718/tcp   OPUS Server Port
//opus-services   3718/udp   OPUS Server Port
//#                          Detlef Stoever <mail&ivotec.com> March 2003
//itelserverport  3719/tcp   iTel Server Port
//itelserverport  3719/udp   iTel Server Port
//#                          Mark Hendricks <markah&copper.net> March 2003
//ufastro-instr   3720/tcp   UF Astro. Instr. Services
//ufastro-instr   3720/udp   UF Astro. Instr. Services
//#                          David B. Hon <hon&astro.ufl.edu> March 2003
//xsync           3721/tcp   Xsync
//xsync           3721/udp   Xsync
//xserveraid      3722/tcp   Xserve RAID
//xserveraid      3722/udp   Xserve RAID
//#                          Bob Bradley <bradley&apple.com> March 2003
//sychrond        3723/tcp   Sychron Service Daemon
//sychrond        3723/udp   Sychron Service Daemon
//#                          Robert Marinelli <bob&sychron.com> March 2003
//blizwow         3724/tcp   World of Warcraft
//blizwow         3724/udp   World of Warcraft
//#                          Domain Tech <Domainnametech&blizzard.com> April 2005
//na-er-tip       3725/tcp   Netia NA-ER Port
//na-er-tip       3725/udp   Netia NA-ER Port
//#                          Jean-Pierre Garcia <jp.garcia&netia.net> April 2003
//array-manager   3726/tcp   Xyratex Array Manager
//array-manager   3726/udp   Xyartex Array Manager
//#                          David A. Lethe <david_lethe&us.xyratex.com> April 2003
//e-mdu           3727/tcp   Ericsson Mobile Data Unit
//e-mdu           3727/udp   Ericsson Mobile Data Unit
//e-woa           3728/tcp   Ericsson Web on Air
//e-woa           3728/udp   Ericsson Web on Air
//#                          Marco Casole <marco.casole&ericsson.com> April 2003
//fksp-audit      3729/tcp   Fireking Audit Port
//fksp-audit      3729/udp   Fireking Audit Port
//#                          Richard Thurman <richt&fireking.com> April 2003
//client-ctrl     3730/tcp   Client Control
//client-ctrl     3730/udp   Client Control
//#                          Lawrence W. Dunn <larrydunn&aptcomp.com> April 2003
//smap            3731/tcp   Service Manager
//smap            3731/udp   Service Manager
//m-wnn           3732/tcp   Mobile Wnn
//m-wnn           3732/udp   Mobile Wnn
//#                          Yasunari Yamashita <yamasita&omronsoft.co.jp> April 2003
//multip-msg      3733/tcp   Multipuesto Msg Port
//multip-msg      3733/udp   Multipuesto Msg Port
//#                          Felisa Ares <faa06&tid.es> April 2003
//synel-data      3734/tcp   Synel Data Collection Port
//synel-data      3734/udp   Synel Data Collection Port
//#                          David Ashkenazi <david&synel.co.il> April 2003
//pwdis           3735/tcp   Password Distribution
//pwdis           3735/udp   Password Distribution
//#                          Robert Erl <roerl&web.de> April 2003
//rs-rmi          3736/tcp   RealSpace RMI
//rs-rmi          3736/udp   RealSpace RMI
//#                          Barry McDarby <realspace&starwolf.biz> April 2003
//xpanel          3737/tcp   XPanel Daemon
//#                          Lilian Rudenco <info&xpanel.com> 04 March 2009
//#               3737/udp   Reserved
//versatalk       3738/tcp   versaTalk Server Port
//versatalk       3738/udp   versaTalk Server Port
//#                          Dr. Kingsley C. Nwosu <knwosu&aglowmail.com> April 2003
//launchbird-lm   3739/tcp   Launchbird LicenseManager
//launchbird-lm   3739/udp   Launchbird LicenseManager
//#                          Tom Hawkins <tom1&launchbird.com> April 2003
//heartbeat       3740/tcp   Heartbeat Protocol
//heartbeat       3740/udp   Heartbeat Protocol
//#                          Jeroen Massar <jeroen&unfix.org> April 2003
//wysdma          3741/tcp   WysDM Agent
//wysdma          3741/udp   WysDM Agent
//#                          Jim McDonald <Jim.McDonald&sysdm.com> April 2003
//cst-port        3742/tcp   CST - Configuration & Service HostNode
//cst-port        3742/udp   CST - Configuration & Service HostNode
//#                          Hai Ou-Yang <hai.ou-yang&sun.com> April 2003
//ipcs-command    3743/tcp   IP Control Systems Ltd.
//ipcs-command    3743/udp   IP Control Systems Ltd.
//#                          Paul Anderson <paul.anderson&ip-cs.com> April 2003
//sasg            3744/tcp   SASG
//sasg            3744/udp   SASG
//#                          Cristian Petculescu <cristp&hotmail.com> April 2003
//gw-call-port    3745/tcp   GWRTC Call Port
//gw-call-port    3745/udp   GWRTC Call Port
//#                          Felisa Ares <faa06&tid.es> April 2003
//linktest        3746/tcp   LXPRO.COM LinkTest
//linktest        3746/udp   LXPRO.COM LinkTest
//linktest-s      3747/tcp   LXPRO.COM LinkTest SSL
//linktest-s      3747/udp   LXPRO.COM LinkTest SSL
//#                          Greg Bailey <gbailey&lxpro.com> April 2003
//webdata         3748/tcp   webData
//webdata         3748/udp   webData
//#                          Michael Whiteley <michael&whiteley.com> April 2003
//cimtrak         3749/tcp   CimTrak
//cimtrak         3749/udp   CimTrak
//#                          Robert E. Johnson, III <johnson.robert&cimcor.com> April 2003
//cbos-ip-port    3750/tcp   CBOS/IP ncapsalation port
//cbos-ip-port    3750/udp   CBOS/IP ncapsalatoin port
//#                          Thomas Dannemiller <tom.dannemiller&rolls-royce.com> April 2003
//gprs-cube       3751/tcp   CommLinx GPRS Cube
//gprs-cube       3751/udp   CommLinx GPRS Cube
//#                          Peter Johnson <peter&commlinx.com.au> April 2003
//vipremoteagent  3752/tcp   Vigil-IP RemoteAgent
//vipremoteagent  3752/udp   Vigil-IP RemoteAgent
//#                          Bryan Alvord <bryan&vaticor.com> April 2003
//nattyserver     3753/tcp   NattyServer Port
//nattyserver     3753/udp   NattyServer Port
//#                          Akira Saito <admin&kobu.com> April 2003
//timestenbroker  3754/tcp   TimesTen Broker Port 
//timestenbroker  3754/udp   TimesTen Broker Port
//#                          David Aspinwall <aspinwall&TimesTen.com> April 2003
//sas-remote-hlp  3755/tcp   SAS Remote Help Server
//sas-remote-hlp  3755/udp   SAS Remote Help Server
//#                          Gary T. Ciampa <Gary.Ciampa&sas.com> April 2003
//canon-capt      3756/tcp   Canon CAPT Port
//canon-capt      3756/udp   Canon CAPT Port
//#                          Takashi Okazawa <okazawa.takashi&canon.co.jp> April 2003
//grf-port        3757/tcp   GRF Server Port
//grf-port        3757/udp   GRF Server Port
//#                          Robert Banfill <robert&banfill.net> April 2003
//apw-registry    3758/tcp   apw RMI registry
//apw-registry    3758/udp   apw RMI registry
//#                          Dan Davis <Dan.A.Davis&hp.com> April 2003
//exapt-lmgr      3759/tcp   Exapt License Manager
//exapt-lmgr      3759/udp   Exapt License Manager
//#                          Christoph Kukulies <info&exapt.de> April 2003
//adtempusclient  3760/tcp   adTempus Client
//adtempusclient  3760/udp   adTEmpus Client
//#                          Bill Wingate <bill.wingate&arcanadev.com> May 2003 
//gsakmp          3761/tcp   gsakmp port
//gsakmp          3761/udp   gsakmp port
//#                          [RFC4535]  
//gbs-smp         3762/tcp   GBS SnapMail Protocol
//gbs-smp         3762/udp   GBS SnapMail Protocol
//#                          Eric Harris-Braun <eric&glassbead.com> June 2003
//xo-wave         3763/tcp   XO Wave Control Port
//xo-wave         3763/udp   XO Wave Control Port
//#                          Bjorn Dittmer-Roche <bjorn&xowave.com> June 2003
//mni-prot-rout   3764/tcp   MNI Protected Routing
//mni-prot-rout   3764/udp   MNI Protected Routing
//#                          Tim Behne <timothyb&microwavenetworks.com> June 2003
//rtraceroute     3765/tcp   Remote Traceroute
3765,//rtraceroute     3765/udp   Remote Traceroute
//#                          A. Blake Cooper <blake&cluebie.net> June 2003
//#               3766       Unassigned (Returned 2009-06-19)
3767,//listmgr-port    3767/tcp   ListMGR Port
//listmgr-port    3767/udp   ListMGR Port
//#                          Takashi Kubota <kubota.takashi&pfu.fugitsu.com> June 2003
//rblcheckd       3768/tcp   rblcheckd server daemon
//rblcheckd       3768/udp   rblcheckd server daemon
//#                          Sabri Berisha <sabri&cluecentral.net> June 2003
//haipe-otnk      3769/tcp   HAIPE Network Keying
//haipe-otnk      3769/udp   HAIPE Network Keying
//#                          Mike Irani <irani&spawar.navy.mil> June 2003
//cindycollab     3770/tcp   Cinderella Collaboration
//cindycollab     3770/udp   Cinderella Collaboration
//#                          Ulrich Kortenkamp  <kortenkamp&cinderella.de> June 2003
//paging-port     3771/tcp   RTP Paging Port
//paging-port     3771/udp   RTP Paging Port
//#                          Patrick Ferriter <Patrick.Ferriter&zultys.com> June 2003
//ctp             3772/tcp   Chantry Tunnel Protocol
//ctp             3772/udp   Chantry Tunnel Protocol
//#                          Inderpreet Singh <isingh&chantrynetworks.com> June 2003
//ctdhercules     3773/tcp   ctdhercules
//ctdhercules     3773/udp   ctdhercules
//#                          Carl Banzhof <cbanzhof&citadel.com> June 2003
//zicom           3774/tcp   ZICOM
//zicom           3774/udp   ZICOM
//#                          Sabu Das <sabud&zicomsecure.com> June 2003
//ispmmgr         3775/tcp   ISPM Manager Port
//ispmmgr         3775/udp   ISPM Manager Port
//#                          Eric Anderson <eanderson&netvision.com> June 2003
//dvcprov-port    3776/tcp   Device Provisioning Port
//dvcprov-port    3776/udp   Device Provisioning Port
//#                          Rob Lehew <rlehew&microsoft.com> June 2003
//jibe-eb         3777/tcp   Jibe EdgeBurst
//jibe-eb         3777/udp   Jibe EdgeBurst
//#                          Chap Tippin <chad.tippin&jibeinc.com> June 2003						   
//c-h-it-port     3778/tcp   Cutler-Hammer IT Port
//c-h-it-port     3778/udp   Cutler-Hammer IT Port
//#                          Thomas Ruchti <thomasmruchti&eaton.com> June 2003
//cognima         3779/tcp   Cognima Replication
//cognima         3779/udp   Cognima Replication
//#                          Raplh Greenwell <iana&cognima.com> June 2003
//nnp             3780/tcp   Nuzzler Network Protocol
//nnp             3780/udp   Nuzzler Network Protocol
//#                          Andreas Schwarz <andreas.schwarz&securepoint.de> June 2003
//abcvoice-port   3781/tcp   ABCvoice server port
//abcvoice-port   3781/udp   ABCvoice server port
//#                          Carlos Gonzalez-Roman Ferrer <iana&abcdatos.com> June 2003
//iso-tp0s        3782/tcp   Secure ISO TP0 port
//iso-tp0s        3782/udp   Secure ISO TP0 port
//#                          Herbert Falk <herb&sisconet.com> June 2003
//bim-pem         3783/tcp   Impact Mgr./PEM Gateway
//bim-pem         3783/udp   Impact Mgr./PEM Gateway
//#                          Walter G. Giroir <walt_giroir&bmc.com> July 2003
//bfd-control     3784/tcp   BFD Control Protocol
//bfd-control     3784/udp   BFD Control Protocol
//bfd-echo        3785/tcp   BFD Echo Protocol 
//bfd-echo        3785/udp   BFD Echo Protocol
//#                          Dave Katz <dkatz&juniper.net> Dave Ward <dward&cisco.com> July 2003
//upstriggervsw   3786/tcp   VSW Upstrigger port
//upstriggervsw   3786/udp   VSW Upstrigger port
//#                          Mark-Tim Junghanns <mjunghanns&vangerow.de> July 2003
//fintrx          3787/tcp   Fintrx
//fintrx          3787/udp   Fintrx
//#                          Peter G.L. Potgieser <p.g.l.potgieser&interpay.nl> July 2003
//isrp-port       3788/tcp   SPACEWAY Routing port
//isrp-port       3788/udp   SPACEWAY Routing port
//#                          Vaibhav Kumar <vakumar&hns.com> July 2003
//remotedeploy    3789/tcp   RemoteDeploy Administration Port [July 2003]
//remotedeploy    3789/udp   RemoteDeploy Administration Port [July 2003]
//#                          Detlef Rothe <detlef.rothe&ts.fujitsu.com> 15 May 2009
//quickbooksrds   3790/tcp   QuickBooks RDS
//quickbooksrds   3790/udp   QuickBooks RDS
//#                          Almira <almira_niciu&intuit.com> July 2003
//tvnetworkvideo  3791/tcp   TV NetworkVideo Data port
//tvnetworkvideo  3791/udp   TV NetworkVideo Data port
//#                          Kevin Brunner <brunner&tivo.com> July 2003
//sitewatch       3792/tcp   e-Watch Corporation SiteWatch
//sitewatch       3792/udp   e-Watch Corporation SiteWatch
//#                          John M. Baird <jbaird&e-watch.com> July 2003
//dcsoftware      3793/tcp   DataCore Software
//dcsoftware      3793/udp   DataCore Software
//#                          Andre Cato <andre.cato&datacore.com> July 2003
//jaus            3794/tcp   JAUS Robots
//jaus            3794/udp   JAUS Robots
//#                          Steven B. Cliff <scliff&remotec-andros.com> July 2003
//myblast         3795/tcp   myBLAST Mekentosj port
//myblast         3795/udp   myBLAST Mekentosj port
//#                          Alexander Griekspoor <a.griekspoor&nki.nl> July 2003
//spw-dialer      3796/tcp   Spaceway Dialer
//spw-dialer      3796/udp   Spaceway Dialer
//#                          Patrick Fisher <pfisher&hns.com> July 2003
//idps            3797/tcp   idps
//idps            3797/udp   idps
//#                          Jean-Francois Rabasse <jfr&idps.org> July 2003
//minilock        3798/tcp   Minilock
//minilock        3798/udp   Minilock
//#                          Daniel Julio Reyes <danieljreyes&yahoo.com> August 2003
//radius-dynauth  3799/tcp   RADIUS Dynamic Authorization
//radius-dynauth  3799/udp   RADIUS Dynamic Authorization
//#                          RFC 3576 - July 2003
//pwgpsi          3800/tcp   Print Services Interface
//pwgpsi          3800/udp   Print Services Interface
//#                          Harry Lewis <harryl&us.ibm.com> May 2003  
//ibm-mgr		3801/tcp   ibm manager service
//ibm-mgr		3801/udp   ibm manager service
//#			   Tim Hahn <hahnt&us.ibm.com> March 2006
//vhd             3802/tcp   VHD
//vhd             3802/udp   VHD
//#                          Chris Duncombe <cdunc&atpeng.com>   
//soniqsync       3803/tcp   SoniqSync
//soniqsync       3803/udp   SoniqSync
//#                          Ryan Melville <ryan_melville&soniqcast.com> January 2004 
//iqnet-port      3804/tcp   Harman IQNet Port
//iqnet-port      3804/udp   Harman IQNet Port
//#                          Bruce Vander Werf <bvanderwerf&crownintl.com> February 2004
//tcpdataserver   3805/tcp   ThorGuard Server Port
//tcpdataserver   3805/udp   ThorGuard Server Port
//#                          Joel E. Steiger <jsteiger&eic-us.com> February 2004
//wsmlb           3806/tcp   Remote System Manager
//wsmlb           3806/udp   Remote System Manager
//#                          Thomas Fiege <tfiege&us.ibm.com> February 2004
//spugna          3807/tcp   SpuGNA Communication Port
//spugna          3807/udp   SpuGNA Communication Port
//#                          Samuele Sequi <samuelesequi&defcom.it> February 2004
//sun-as-iiops-ca 3808/tcp   Sun App Svr-IIOPClntAuth
//sun-as-iiops-ca 3808/udp   Sun App Svr-IIOPClntAuth
//#                          Abhijit Kumar <as-iana-ports&sun.com> November 2005
//apocd		3809/tcp   Java Desktop System Configuration Agent
//apocd		3809/udp   Java Desktop System Configuration Agent
//#			   Geoff Higgins <geoff.higgins&sun.com> March 2006
//wlanauth        3810/tcp   WLAN AS server
//wlanauth        3810/udp   WLAN AS server
//#                          Bianling Zhang <blzhang&iwncomm.com> February 2004    
//amp             3811/tcp   AMP
//amp             3811/udp   AMP
//#                          Northon Rodrigues <northon.rodrigues&thomson.net> February 2004 
//neto-wol-server 3812/tcp   netO WOL Server
//neto-wol-server 3812/udp   netO WOL Server
//#                          Martin Bestmann <martin&no.netopia.com> March 2004
//rap-ip          3813/tcp   Rhapsody Interface Protocol
//rap-ip          3813/udp   Rhapsody Interface Protocol
//#                          Paul Zander (Philips CFT) <p.j.zander&philips.com> March 2004
//neto-dcs        3814/tcp   netO DCS
//neto-dcs        3814/udp   netO DCS
//#                          Martin Bestmann <martin&no.netopia.com> March 2004
//lansurveyorxml  3815/tcp   LANsurveyor XML
//lansurveyorxml  3815/udp   LANsurveyor XML
//#                          Michael Swan <swan&neon.com> April 2004
//sunlps-http     3816/tcp   Sun Local Patch Server
//sunlps-http     3816/udp   Sun Local Patch Server
//#                          Barry Greenberg <barry.greenberg&sun.com> April 2004
//tapeware        3817/tcp   Yosemite Tech Tapeware
//tapeware        3817/udp   Yosemite Tech Tapeware
//#                          Luke Dion <ldion&tapeware.com> April 2004
//crinis-hb       3818/tcp   Crinis Heartbeat
//crinis-hb       3818/udp   Crinis Heartbeat
//#                          Eric McMurry <emcmurry&crinisnetworks.com> April 2004
//epl-slp         3819/tcp   EPL Sequ Layer Protocol
//epl-slp         3819/udp   EPL Sequ Layer Protocol
//#                          Hans Weibel <hans.weibel&zhwin.ch> October 2004
//scp             3820/tcp   Siemens AuD SCP
//scp             3820/udp   Siemens AuD SCP
//#                          Johann Arnold <johann.arnold&siemens.com> October 2004
//pmcp            3821/tcp   ATSC PMCP Standard
//pmcp            3821/udp   ATSC PMCP Standard
//#                          Graham Jones <gjones&nab.org> November 2004
//acp-discovery   3822/tcp   Compute Pool Discovery
//acp-discovery   3822/udp   Compute Pool Discovery
//acp-conduit     3823/tcp   Compute Pool Conduit
//acp-conduit     3823/udp   Compute Pool Conduit
//acp-policy      3824/tcp   Compute Pool Policy
//acp-policy      3824/udp   Compute Pool Policy
//#                          Andy Belk <register1&azulsystems.com> February 2005
//ffserver	3825/tcp   Antera FlowFusion Process Simulation
//ffserver	3825/udp   Antera FlowFusion Process Simulation
//#			   Armin Liebchen <armin&anteradesign.com> June 2007
//wormux		3826/tcp   Wormux server
//wormux		3826/udp   Wormux server
//#			   DEFERT-SIMONNEAU <laurent_defert&yahoo.fr> June 2007
//netmpi		3827/tcp   Netadmin Systems MPI service
//netmpi		3827/udp   Netadmin Systems MPI service
//#			   G�ran Runfeldt <goran&netadmin.se> 10 July 2007
//neteh		3828/tcp   Netadmin Systems Event Handler
//neteh		3828/udp   Netadmin Systems Event Handler
//neteh-ext	3829/tcp   Netadmin Systems Event Handler External
//neteh-ext	3829/udp   Netadmin Systems Event Handler External
//#			   Jonas Krogell <jonas.krogell&netadmin.se> 10 July 2007
//cernsysmgmtagt  3830/tcp   Cerner System Management Agent
//cernsysmgmtagt  3830/udp   Cerner System Management Agent
//#                          Mike Craft <mcraft&cerner.com> 29 January 2008
//dvapps		3831/tcp   Docsvault Application Service
//dvapps		3831/udp   Docsvault Application Service
//#			   Ketul Patel <ketulp76&yahoo.com> October 2006
//xxnetserver	3832/tcp   xxNETserver
//xxnetserver	3832/udp   xxNETserver
//#			   Lawrence R. Bulduc <LBulduc&ATTGlobal.net> October 2006
//aipn-auth	3833/tcp   AIPN LS Authentication
//aipn-auth	3833/udp   AIPN LS Authentication
//#			   Qiang Zhang <qzhang&iwncomm.com> October 2006
//spectardata	3834/tcp   Spectar Data Stream Service
//spectardata	3834/udp   Spectar Data Stream Service
//spectardb	3835/tcp   Spectar Database Rights Service
//spectardb	3835/udp   Spectar Database Rights Service
//#			   Jan Rutger Voorhorst <janrutger&roadware.nl> October 2006
//markem-dcp      3836/tcp   MARKEM NEXTGEN DCP
//markem-dcp      3836/udp   MARKEM NEXTGEN DCP
//mkm-discovery   3837/tcp   MARKEM Auto-Discovery
//mkm-discovery   3837/udp   MARKEM Auto-Discovery
//#                          Vadym Kargin <vkargin&markem.com> August 2005
//sos             3838/tcp   Scito Object Server
//sos             3838/udp   Scito Object Server
//#                          Arno Klaassen <arno&ccr.jussieu.fr> November 2003 
//amx-rms         3839/tcp   AMX Resource Management Suite
//amx-rms         3839/udp   AMX Resource Management Suite
//#                          Ron Barber <ron.barber&amx.com> November 2003
//flirtmitmir     3840/tcp   www.FlirtMitMir.de
//flirtmitmir     3840/udp   www.FlirtMitMir.de
//#                          Carsten Falticska <falticska&freenet.de> November 2003
//zfirm-shiprush3 3841/tcp   Z-Firm ShipRush v3
//zfirm-shiprush3 3841/udp   Z-Firm ShipRush v3
//#                          Rafael Zimberoff <rafael&zfirmllc.com> November 2003
//nhci            3842/tcp   NHCI status port
//nhci            3842/udp   NHCI status port
//#                          Eric Welch <eric&innosys.com> November 2003
//quest-agent     3843/tcp   Quest Common Agent
//quest-agent     3843/udp   Quest Common Agent
//#                          Peter Maher <quest_iana&oz.quest.com> November 2003
//rnm             3844/tcp   RNM
//rnm             3844/udp   RNM
//#                          sn0w of renegade labs <sn0w&devious.tsongkie.com> November 2003                                        
//v-one-spp       3845/tcp   V-ONE Single Port Proxy
//v-one-spp       3845/udp   V-ONE Single Port Proxy
//#                          Daniel Becker <dbecker&v-one.com>
//an-pcp          3846/tcp   Astare Network PCP
//an-pcp          3846/udp   Astare Network PCP
//#                          Tony Gulino <astaregod&hotmail.com> August 2003 
//msfw-control    3847/tcp   MS Firewall Control
//msfw-control    3847/udp   MS Firewall Control
//#                          Oren Trutner <orentrut&microsoft.com> August 2003
//item            3848/tcp   IT Environmental Monitor
//item            3848/udp   IT Environmental Monitor
//#                          Keith Wright <kwright&sensatronics.com> August 2003
//spw-dnspreload  3849/tcp   SPACEWAY DNS Preload
//spw-dnspreload  3849/udp   SPACEWAY DNS Prelaod
//#                          Daniel Friedman <dfriedman&hns.com> August 2003
//qtms-bootstrap  3850/tcp   QTMS Bootstrap Protocol
//qtms-bootstrap  3850/udp   QTMS Bootstrap Protocol
//#                          Phil Willis <phil.willis&prism-uk.com> August 2003
//spectraport     3851/tcp   SpectraTalk Port
//spectraport     3851/udp   SpectraTalk Port
//#                          Madhav Karhade <madhav.karhade&wibhu.com> August 2003
//sse-app-config  3852/tcp   SSE App Configuration
//sse-app-config  3852/udp   SSE App Configuration
//#                          Tim Wilson <tim.wilson&motorola.com> August 2003
//sscan           3853/tcp   SONY scanning protocol
//sscan           3853/udp   SONY scanning protocol
//#                          Takashi Aihara <aiharat&sm.sony.co.jp> August 2003
//stryker-com     3854/tcp   Stryker Comm Port
//stryker-com     3854/udp   Stryker Comm Port
//#                          Andrew Schultz <aschultz&strykercom.com> August 2003
//opentrac        3855/tcp   OpenTRAC
//opentrac        3855/udp   OpenTRAC
//#                          Scott Miller <scott&opentrac.org> August 2003
//informer        3856/tcp   INFORMER
//informer        3856/udp   INFORMER
//#                          Filippo Fadda <fadda&osway.com> August 2003
//trap-port       3857/tcp   Trap Port
//trap-port       3857/udp   Trap Port
//#                          Norm Freedman <normfree&san.rr.com> August 2003
//trap-port-mom   3858/tcp   Trap Port MOM
//trap-port-mom   3858/udp   Trap Port MOM
//#                          Norm Freedman <normfree&san.rr.com> August 2003
//nav-port        3859/tcp   Navini Port
//nav-port        3859/udp   Navini Port
//#                          Chris Sanders <csanders&navini.com> August 2003
//sasp		3860/tcp   Server/Application State Protocol (SASP)
//sasp		3860/udp   Server/Application State Protocol (SASP)
//#                          Alan Bivens <jbivens&us.ibm.com> August 2003
//winshadow-hd    3861/tcp   winShadow Host Discovery
//winshadow-hd    3861/udp   winShadow Host Discovery
//#                          Shu-Wei Tan <stan&omnicomtech.com> March 2003
//giga-pocket     3862/tcp   GIGA-POCKET
//giga-pocket     3862/udp   GIGA-POCKET
//#                          Yoshikazu Watanabe <nabe&sm.sony.co.jp>
//asap-tcp        3863/tcp   asap tcp port
//asap-udp        3863/udp   asap udp port
//#                          [RFC5352]
//asap-sctp       3863/sctp  asap sctp
//#                          [RFC5352]
//asap-tcp-tls    3864/tcp   asap/tls tcp port
//#                          [RFC5352]
//asap-sctp-tls   3864/sctp  asap-sctp/tls 
//#                          [RFC5352]
//xpl             3865/tcp   xpl automation protocol
//xpl             3865/udp   xpl automation protocol
//#                          Ian Lowe <ian&xplproject.org.uk> August 2003
//dzdaemon        3866/tcp   Sun SDViz DZDAEMON Port
//dzdaemon        3866/udp   Sun SDViz DZDAEMON Port
//#                          Kevin Rushforth <kevin.rushforth&sun.com> August 2003
//dzoglserver     3867/tcp   Sun SDViz DZOGLSERVER Port
//dzoglserver     3867/udp   Sun SDViz DZOGLSERVER Port
//#                          Kevin Rushforth <kevin.rushforth&sun.com> August 2003
//diameter        3868/tcp   DIAMETER
//#               3868/udp   Reserved
//diameter        3868/sctp  DIAMETER
//#                          RFC3588
//ovsam-mgmt      3869/tcp   hp OVSAM MgmtServer Disco
//ovsam-mgmt      3869/udp   hp OVSAM MgmtServer Disco
//#                          Mike Pontillo <pontillo&hp.com> August 2003
//ovsam-d-agent   3870/tcp   hp OVSAM HostAgent Disco
//ovsam-d-agent   3870/udp   hp OVSAM HostAgent Disco
//#                          Mike Pontillo <pontillo&hp.com> August 2003
//avocent-adsap   3871/tcp   Avocent DS Authorization
//avocent-adsap   3871/udp   Avocent DS Authorization
//#                          Eduardo Fernandez <eduardo.fernandez&avocent.com> August 2003
//oem-agent       3872/tcp   OEM Agent
//oem-agent       3872/udp   OEM Agent
//#                          Narain Jagathesan <narain.jagathesan&oracle.com> November 2003
//fagordnc        3873/tcp   fagordnc
//fagordnc        3873/udp   fagordnc
//#                          Luis Zugasti <lzugasti&fagorautomation.es> November 2003
//sixxsconfig     3874/tcp   SixXS Configuration
//sixxsconfig     3874/udp   SixXS Configuration
//#                          Jeroen Massar <jeroen&unfix.org> November 2003
//pnbscada        3875/tcp   PNBSCADA
//pnbscada        3875/udp   PNBSCADA
//#                          Philip N. Bergstresser <phil&bergstresser.org> 
//dl_agent        3876/tcp   DirectoryLockdown Agent
//dl_agent        3876/udp   DirectoryLockdown Agent
//#                          Previous contact: NetPro Computing <ports&netpro.com> October 2003
//#                          New contacts: Jason Lockett <Jay.Lockett&quest.com> 16 December 2008
//#                          New contacts: Melanie Kacerek <melanie.kacerek&quest.com> 16 December 2008
//xmpcr-interface 3877/tcp   XMPCR Interface Port
//xmpcr-interface 3877/udp   XMPCR Interface Port
//#                          Christopher Carlson <cjc&dobbz.com> October 2003
//fotogcad        3878/tcp   FotoG CAD interface
//fotogcad        3878/udp   FotoG CAD interface
//#                          Jason Szabo <jason.szabo&vexcel.com> October 2003
//appss-lm        3879/tcp   appss license manager
//appss-lm        3879/udp   appss license manager
//#                          Peter Krueger <krueger&appss.de> October 2003
//igrs		3880/tcp   IGRS
//igrs		3880/udp   IGRS
//#                          Huang Jingnan <huangjnb&lenovo.com> October 2003
//idac            3881/tcp   Data Acquisition and Control
//idac            3881/udp   Data Acquisition and Control
//#                          Chatziandreoglou Christos <chatzi&xan.forthnet.gr> October 2003
//msdts1          3882/tcp   DTS Service Port
//msdts1          3882/udp   DTS Service Port
//#                          Sergei Ivanov <sergei&microsoft.com> October 2003
//vrpn            3883/tcp   VR Peripheral Network
//vrpn            3883/udp   VR Peripheral Network
//#                          Russell M. Taylor II <taylor&cs.unc.edu> October 2003
//softrack-meter  3884/tcp   SofTrack Metering
//softrack-meter  3884/udp   SofTrack Metering
//#                          John T. McCann <jmccann&softwaremetering.com> October 2003
//topflow-ssl     3885/tcp   TopFlow SSL
//topflow-ssl     3885/udp   TopFlow SSL
//#                          Ken Nelson <nelson&TopLayer.com>
//nei-management  3886/tcp   NEI management port
//nei-management  3886/udp   NEI management port
//#                          Kevin Murphy <kevin.murphy&networkengines.com> October 2003
//ciphire-data    3887/tcp   Ciphire Data Transport
//ciphire-data    3887/udp   Ciphire Data Transport
//#                          Lars Eilebrecht <le+iana&leogic.com> October 2003
//ciphire-serv    3888/tcp   Ciphire Services
//ciphire-serv    3888/udp   Ciphire Services
//#                          Lars Eilebrecht <le+iana&leogic.com> October 2003
//dandv-tester    3889/tcp   D and V Tester Control Port
//dandv-tester    3889/udp   D and V Tester Control Port
//#                          Voiko Loukanov <v.loukanov&dvelectronics.com> October 2003
//ndsconnect      3890/tcp   Niche Data Server Connect
//ndsconnect      3890/udp   Niche Data Server Connect
//#                          Roland Schneider <rsch&nicherms.com> October 2003
//rtc-pm-port     3891/tcp   Oracle RTC-PM port
//rtc-pm-port     3891/udp   Oracle RTC-PM port
//#                          PV Shivkumar <p.shivkumar&oracle.com> October 2003
//pcc-image-port  3892/tcp   PCC-image-port
//pcc-image-port  3892/udp   PCC-image-port
//#                          Shiro Tamoto <tamoto.shiro&jp.panasonic.com> October 2003
//cgi-starapi     3893/tcp   CGI StarAPI Server
//cgi-starapi     3893/udp   CGI StarAPI Server
//#                          Garry Moore <garry.moore&cgi.com> October 2003
//syam-agent      3894/tcp   SyAM Agent Port
//syam-agent      3894/udp   SyAM Agent Port
//#                          Michael Daniele <michael.daniele&syamsoftware.com> October 2003
//syam-smc        3895/tcp   SyAm SMC Service Port
//syam-smc        3895/udp   SyAm SMC Service Port
//#                          Michael Daniele <michael.daniele&syamsoftware.com> October 2003
//sdo-tls         3896/tcp   Simple Distributed Objects over TLS
//sdo-tls         3896/udp   Simple Distributed Objects over TLS
//#                          Alexander Philippou <alex&noemax.com> October 2003
//sdo-ssh         3897/tcp   Simple Distributed Objects over SSH
//sdo-ssh         3897/udp   Simple Distributed Objects over SSH
//#                          Alexander Philippou <alex&noemax.com> October 2003
//senip           3898/tcp   IAS, Inc. SmartEye NET Internet Protocol
//senip           3898/udp   IAS, Inc. SmartEye NET Internet Protocol
//#                          Matt Nowicki <nowickim&iasdirect.com> October 2003
//itv-control     3899/tcp   ITV Port
//itv-control     3899/udp   ITV Port
//#                          Alex Nicu <alex.nicu&philips.com> October 2003
//udt_os          3900/tcp   Unidata UDT OS
//udt_os          3900/udp   Unidata UDT OS
//#                          James Powell <james&mailhost.unidata.com>
//nimsh           3901/tcp   NIM Service Handler
//nimsh           3901/udp   NIM Service Handler
//#                          Paul B. Finley <pfinley&us.ibm.com> October 2003
//nimaux          3902/tcp   NIMsh Auxiliary Port
//nimaux          3902/udp   NIMsh Auxiliary Port
//#                          Paul B. Finley <pfinley&us.ibm.com> October 2003
//charsetmgr      3903/tcp   CharsetMGR
//charsetmgr      3903/udp   CharsetMGR
//#                          Tatsuya Ueda <tatsu&ist.fujitsu.com> October 2003
//omnilink-port   3904/tcp   Arnet Omnilink Port
//omnilink-port   3904/udp   Arnet Omnilink Port
//#                          Ronen Shaul <ronen&arnetsystems.com> October 2003
//mupdate         3905/tcp   Mailbox Update (MUPDATE) protocol    
//mupdate         3905/udp   Mailbox Update (MUPDATE) protocol
//#                          [RFC3656]
//topovista-data  3906/tcp   TopoVista elevation data
//topovista-data  3906/udp   TopoVista elevation data
//#                          Gregg Townsend <gmt&cs.arizona.edu> November 2003
//imoguia-port    3907/tcp   Imoguia Port
//imoguia-port    3907/udp   Imoguia Port
//#                          Emidio Cunha <emidio&janeladigital.com> November 2003
//hppronetman     3908/tcp   HP Procurve NetManagement
//hppronetman     3908/udp   HP Procurve NetManagement
//#                          Devon Dawson <devon.dawson&hp.com> November 2003
//surfcontrolcpa  3909/tcp   SurfControl CPA
//surfcontrolcpa  3909/udp   SurfControl CPA
//#                          Hywel Morgan <hywelm&surfcontrol.com> November 2003
//prnrequest      3910/tcp   Printer Request Port
//prnrequest      3910/udp   Printer Request Port
//#                          Brett Green <brett_green&hp.com> November 2003
//prnstatus       3911/tcp   Printer Status Port
//prnstatus       3911/udp   Printer Status Port
//#                          Brett Green <brett_green&hp.com> November 2003
//gbmt-stars      3912/tcp   Global Maintech Stars
//gbmt-stars      3912/udp   Global Maintech Stars
//#                          Harry Goldschmitt <hgoldschmitt&hgac.com> November 2003
//listcrt-port    3913/tcp   ListCREATOR Port
//listcrt-port    3913/udp   ListCREATOR Port
//#                          Tomokazu Asai <asai.tomokazu&pfu.fujitsu.com> November 2003
//listcrt-port-2  3914/tcp   ListCREATOR Port 2
//listcrt-port-2  3914/udp   ListCREATOR Port 2
//#                          Tomokazu Asai <asai.tomokazu&pfu.fujitsu.com> November 2003
//agcat           3915/tcp   Auto-Graphics Cataloging
//agcat           3915/udp   Auto-Graphics Cataloging
//#                          Paul Cope <prc&auto-graphics.com> November 2003
//wysdmc          3916/tcp   WysDM Controller
//wysdmc          3916/udp   WysDM Controller
//#                          Jim McDonald <jim.mcdonald&sysdm.com> November 2003
//aftmux          3917/tcp   AFT multiplex port
//aftmux          3917/udp   AFT multiples port
//#                          Alfred Schmidt <a.schmidt&aft-werdohl.de> November 2003
//pktcablemmcops  3918/tcp   PacketCableMultimediaCOPS
//pktcablemmcops  3918/udp   PacketCableMultimediaCOPS
//#                          Eric Rosenfeld <e.rosenfeld&cablelabs.com> November 2003
//hyperip         3919/tcp   HyperIP
//hyperip         3919/udp   HyperIP
//#                          Dave Reiland <dave.reiland&netex.com> November 2003
//exasoftport1    3920/tcp   Exasoft IP Port
//exasoftport1    3920/udp   Exasoft IP Port
//#                          Alan Malik <alan&exasoft.co.uk> November 2003
//herodotus-net   3921/tcp   Herodotus Net
//herodotus-net   3921/udp   Herodotus Net
//#                          Adam Gawne-Cain <adam&gawncainresearch.co.uk> November 2003
//sor-update      3922/tcp   Soronti Update Port
//sor-update      3922/udp   Soronti Update Port
//#                          Carleton Watkins <carleton&soronti.com> November 2003
//symb-sb-port    3923/tcp   Symbian Service Broker
//symb-sb-port    3923/udp   Symbian Service Broker
//#                          Ian McDowall <ian.mcdowall&symbian.com> November 2003
//mpl-gprs-port   3924/tcp   MPL_GPRS_PORT
//mpl-gprs-port   3924/udp   MPL_GPRS_Port
//#                          David Barrass <david.barrass&minorplante.com> November 2003 
//zmp             3925/tcp   Zoran Media Port
//zmp             3925/udp   Zoran Media Port
//#                          Gerard Cerchio gjpc&circlesoft.com November 2003
//winport         3926/tcp   WINPort
//winport         3926/udp   WINPort
//#                          Alwin Egger <alwin.egger&tegonal.com> November 2003
//natdataservice  3927/tcp   ScsTsr
//natdataservice  3927/udp   ScsTsr
//#                          Ghanshyam Patel <gpatel&natinc.com> November 2003
//netboot-pxe     3928/tcp   PXE NetBoot Manager
//netboot-pxe     3928/udp   PXE NetBoot Manager
//#                          Markus Treinen <markus.treinen&siemens.com> November 2003
//smauth-port     3929/tcp   AMS Port
//smauth-port     3929/udp   AMS Port
//#                          Angelique Dokos <angelique.dokos&hp.com> November 2003
//syam-webserver  3930/tcp   Syam Web Server Port
//syam-webserver  3930/udp   Syam Web Server Port
//#                          Michael Daniele <michael.daniele&syamsoftware.com> November 2003
//msr-plugin-port 3931/tcp   MSR Plugin Port
//msr-plugin-port 3931/udp   MSR Plugin Port
//#                          Ron Steed <rsteed&cemaphore.com> November 2003
//dyn-site        3932/tcp   Dynamic Site System
//dyn-site        3932/udp   Dynamic Site System
//#                          Steve Qi <steve.qi&dyn-site.com> November 2003
//plbserve-port   3933/tcp   PL/B App Server User Port
//plbserve-port   3933/udp   PL/B App Server User Port
//#                          Edward R. Boedecker <boedeck1&flash.net> November 2003
//sunfm-port      3934/tcp   PL/B File Manager Port
//sunfm-port      3934/udp   PL/B File Manager Port
//#                          Edward R. Boedecker <boedeck1&flash.net> November 2003
//sdp-portmapper  3935/tcp   SDP Port Mapper Protocol
//sdp-portmapper  3935/udp   SDP Port Mapper Protocol
//#                          James Pinkerton <jpink&microsoft.com> November 2003
//mailprox        3936/tcp   Mailprox
//mailprox        3936/udp   Mailprox
//#                          Christof Drescher <drescher&mailprox.net> November 2003
//dvbservdsc      3937/tcp   DVB Service Discovery 
//dvbservdsc      3937/udp   DVB Service Discovery 
//#                          Bert van Willigen <bert.vanwilligen&philips.com> Novebmer 2003
//dbcontrol_agent 3938/tcp   Oracle dbControl Agent po
//dbcontrol_agent 3938/udp   Oracel dbControl Agent po
//#                          Todd Guay <todd.guay&oracle.com> November 2003
//aamp            3939/tcp   Anti-virus Application Management Port
//aamp            3939/udp   Anti-virus Application Management Port
//#                          In-sik Choi <iscard&virusdesk.com> February 2002
//xecp-node       3940/tcp   XeCP Node Service 
//xecp-node       3940/udp   XeCP Node Service
//#                          Brent McCullough <bmccullough&timemgmt.com> November 2003
//homeportal-web  3941/tcp   Home Portal Web Server
//homeportal-web  3941/udp   Home Portal Web Server
//#                          Christian Beaumont <chrisb&lantronix.com> November 2003
//srdp            3942/tcp   satellite distribution
//srdp            3942/udp   satellite distribution
//#                          Simone Molendini <simone.molendini&unile.it> November 2003
//tig             3943/tcp   TetraNode Ip Gateway
//tig             3943/udp   TetraNode Ip Gateway
//#                          B. van Klinken <b.vklinken&rohill.nl> December 2003
//sops            3944/tcp   S-Ops Management
//sops            3944/udp   S-Ops Management
//#                          Stefan Hochuli <iana.org&dunes.ch> December 2003
//emcads          3945/tcp   EMCADS Server Port
//emcads          3945/udp   EMCADS Server Port
//#                          Lars Struwe Christensen <lsc&giritech.com> January 2004
//backupedge      3946/tcp   BackupEDGE Server
//backupedge      3946/udp   BackupEDGE Server
//#                          Frank Liberato <frank&microlite.com> June 2004
//ccp             3947/tcp   Connect and Control Protocol for Consumer, Commercial, and Industrial Electronic Devices
//ccp             3947/udp   Connect and Control Protocol for Consumer, Commercial, and Industrial Electronic Devices
//#                          Aaron Myer <aaron.myer&in2nets.com> June 2004
//apdap           3948/tcp   Anton Paar Device Administration Protocol
//apdap           3948/udp   Anton Paar Device Administration Protocol
//#                          Martin Leitner <info&anton-paar.com> June 2004
//drip            3949/tcp   Dynamic Routing Information Protocol
//drip            3949/udp   Dynamic Routing Information Protocol
//#                          Dana Blair <dblair&cisco.com> June 2004
//namemunge       3950/tcp   Name Munging
//namemunge       3950/udp   Name Munging
//#                          John C. Klensin <klensin&jck.com> July 2004
//pwgippfax       3951/tcp   PWG IPP Facsimile
//pwgippfax       3951/udp   PWG IPP Facsimile
//#                          Ira McDonald <imcdonald&sharplabs.com> August 2004
//i3-sessionmgr   3952/tcp   I3 Session Manager
//i3-sessionmgr   3952/udp   I3 Session Manager
//#                          Mike Gagle <mikeg&inin.com> August 2004
//xmlink-connect  3953/tcp   Eydeas XMLink Connect
//xmlink-connect  3953/udp   Eydeas XMLink Connect
//#                          David Crewson <davidc&eydeas.net> September 2004
//adrep           3954/tcp   AD Replication RPC
//adrep           3954/udp   AD Replication RPC
//#                          Previous Contact: Robert Ball <robert.ball&smiths-aerospace.com> August 2005
//#                          Current Contact: Robert Ball <rob.ball&ge.com> 26 March 2008
//p2pcommunity    3955/tcp   p2pCommunity
//p2pcommunity    3955/udp   p2pCommunity
//#                          Tiago Bittencourt Silva <tiagobs&ufpr.br> August 2005
//gvcp            3956/tcp   GigE Vision Control
//gvcp            3956/udp   GigE Vision Control
//#                          Eric Carey <ecarey&corecoimaging.com> August 2005
//mqe-broker      3957/tcp   MQEnterprise Broker
//mqe-broker      3957/udp   MQEnterprise Broker
//mqe-agent       3958/tcp   MQEnterprise Agent
//mqe-agent       3958/udp   MQEnterprise Agent
//#                          Bob Lauria <bob.lauria&asg.com> August 2005
//treehopper      3959/tcp   Tree Hopper Networking 
//treehopper      3959/udp   Tree Hopper Networking 
//#                          Gary Whelan <gwhelan&sybonic.com> August 2005
//bess            3960/tcp   Bess Peer Assessment
//bess            3960/udp   Bess Peer Assessment
//#                          Peter Verdon <bess&dcs.warwick.ac.uk> August 2005
//proaxess        3961/tcp   ProAxess Server 
//proaxess        3961/udp   ProAxess Server 
//#                          Jonas Ahlqvist <jonas.a&informationssystem.se> August 2005
//sbi-agent       3962/tcp   SBI Agent Protocol
//sbi-agent       3962/udp   SBI Agent Protocol
//#                          Yossi Appleboum <yossia&web-silicon.com> August 2005
//thrp            3963/tcp   Teran Hybrid Routing Protocol
//thrp            3963/udp   Teran Hybrid Routing Protocol
//#                          Spencer Teran <steran&dotalot.com> August 2005
//sasggprs        3964/tcp   SASG GPRS
//sasggprs        3964/udp   SASG GPRS
//#                          Cristian Petculescu <petcu40&gmail.com> August 2005
//ati-ip-to-ncpe  3965/tcp   Avanti IP to NCPE API
//ati-ip-to-ncpe  3965/udp   Avanti IP to NCPE API
//#                          Steve Meyer, Sr. <stevem&avanti-tech.com> August 2005
//bflckmgr        3966/tcp   BuildForge Lock Manager
//bflckmgr        3966/udp   BuildForge Lock Manager
//#                          Joe Senner <jsenner&buildforge.com> August 2005
//ppsms           3967/tcp   PPS Message Service
//ppsms           3967/udp   PPS Message Service
//#                          Bart Schaefer <bart&suburbansoftware.com> August 2005
//ianywhere-dbns  3968/tcp   iAnywhere DBNS
//ianywhere-dbns  3968/udp   iAnywhere DBNS
//#                          Graeme Perrow <gperrow&ianywhere.com> August 2005
//landmarks       3969/tcp   Landmark Messages
//landmarks       3969/udp   Landmark Messages
//#                          Petri Rauhala <petri.rauhala&nokia.com> August 2005
//lanrevagent     3970/tcp   LANrev Agent
//lanrevagent     3970/udp   LANrev Agent
//lanrevserver    3971/tcp   LANrev Server
//lanrevserver    3971/udp   LANrev Server
//#                          Martin Bestmann <martin&poleposition-sw.com> August 2005
//iconp           3972/tcp   ict-control Protocol
//iconp           3972/udp   ict-control Protocol
//#                          Roel Harbers <r.harbers&ict-control.com> August 2005
//progistics      3973/tcp   ConnectShip Progistics
//progistics      3973/udp   ConnectShip Progistics
//#                          Jeff Skaistis <jskaistis&connectship.com> August 2005
//citysearch      3974/tcp   Remote Applicant Tracking Service 
//citysearch      3974/udp   Remote Applicant Tracking Service 
//#                          Marc Castelluccio <mcastell&areanetworks.net> August 2005
//airshot         3975/tcp   Air Shot
//airshot         3975/udp   Air Shot
//#                          Shingo Kimura <Shingo.Kimura&jp.sony.com> August 2005
//opswagent 	3976/tcp   Opsware Agent
//opswagent 	3976/udp   Opsware Agent
//opswmanager	3977/tcp   Opsware Manager
//opswmanager	3977/udp   Opsware Manager
//#			   Dave Jagoda <dj&opsware.com> June 2006
//secure-cfg-svr	3978/tcp   Secured Configuration Server
//secure-cfg-svr	3978/udp   Secured Configuration Server
//#			   Dr. Anupam Bharali <paniana&gmail.com> June 2006
//smwan		3979/tcp   Smith Micro Wide Area Network Service
//smwan		3979/udp   Smith Micro Wide Area Network Service
//#			   David Sperling <dsperling&smithmicro.com> June 2006
//acms		3980/tcp   Aircraft Cabin Management System
//acms		3980/udp   Aircraft Cabin Management System
//#			   Dustin Zack <dustin.e.zack&gmail.com> June 2006
//starfish	3981/tcp   Starfish System Admin
//starfish	3981/udp   Starfish System Admin
//#			   Dan Razzell <dan&starfishsystems.ca> June 2006
//eis		3982/tcp   ESRI Image Server 
//eis		3982/udp   ESRI Image Server 
//eisp		3983/tcp   ESRI Image Service
//eisp		3983/udp   ESRI Image Service
//#			   Keith Ryden <kryden&esri.com> July 2006
//mapper-nodemgr  3984/tcp   MAPPER network node manager
//mapper-nodemgr  3984/udp   MAPPER network node manager
//mapper-mapethd  3985/tcp   MAPPER TCP/IP server
//mapper-mapethd  3985/udp   MAPPER TCP/IP server
//mapper-ws_ethd  3986/tcp   MAPPER workstation server
//mapper-ws_ethd  3986/udp   MAPPER workstation server
//#                          John C. Horton <jch&unirsvl.rsvl.unisys.com>
//centerline      3987/tcp   Centerline
//centerline      3987/udp   Centerline
//#                          Mark Simpson <simpson&centerline.com>
//dcs-config      3988/tcp   DCS Configuration Port
//dcs-config      3988/udp   DCS Configuration Port
//#                          Ian Cargill <ian.cargill&e-dendrite.com> August 2005
//bv-queryengine  3989/tcp   BindView-Query Engine
//bv-queryengine  3989/udp   BindView-Query Engine
//bv-is           3990/tcp   BindView-IS
//bv-is           3990/udp   BindView-IS
//bv-smcsrv       3991/tcp   BindView-SMCServer
//bv-smcsrv       3991/udp   BindView-SMCServer
//bv-ds           3992/tcp   BindView-DirectoryServer
//bv-ds           3992/udp   BindView-DirectoryServer
//bv-agent        3993/tcp   BindView-Agent
3993,//bv-agent        3993/udp   BindView-Agent
//#                          David A. Gayler <David.Gayler&bindview.com> August 2005
//#               3994       Unassigned (Returned 2008-04-24)
3995,//iss-mgmt-ssl    3995/tcp   ISS Management Svcs SSL
//iss-mgmt-ssl    3995/udp   ISS Management Svcs SSL
//#                          Wes Wilson <wwilson&iss.net> October 2003
//abcsoftware     3996/tcp   abcsoftware-01
//abcsoftware     3996/udp   abcsoftware-01
//#                          Andrew Zimmerman <andrew&zimmerman.net> June 2004
//agentsease-db   3997/tcp   aes_db
//agentsease-db   3997/udp   aes_db
//#			   Colin Hughes <chughes&agentsease.net> February 2006
//dnx		3998/tcp   Distributed Nagios Executor Service
//dnx		3998/udp   Distributed Nagios Executor Service
//#			   John Calcote <jcalcote&users.sourceforge.net> 06 November 2007
//nvcnet		3999/tcp   Norman distributes scanning service
//nvcnet		3999/udp   Norman distributes scanning service
//#			   Kristian A. Bognaes, Norman ASA <kbo&norman.no> 06 November 2007
//terabase        4000/tcp   Terabase
//terabase        4000/udp   Terabase
//#                          Thor Olson <Thor&terabase.com>   
//####### Potential Conflict of ports ################################
//####### PORT 4000 also used by ICQ <www.icq.com> ################### 
//newoak          4001/tcp   NewOak
//newoak          4001/udp   NewOak
//#                          Jim Philippou <jphilippou&newoak.com>
//pxc-spvr-ft     4002/tcp   pxc-spvr-ft
//pxc-spvr-ft     4002/udp   pxc-spvr-ft
//pxc-splr-ft     4003/tcp   pxc-splr-ft
//pxc-splr-ft     4003/udp   pxc-splr-ft
//pxc-roid        4004/tcp   pxc-roid
//pxc-roid        4004/udp   pxc-roid
//pxc-pin	        4005/tcp   pxc-pin
//pxc-pin         4005/udp   pxc-pin
//pxc-spvr        4006/tcp   pxc-spvr
//pxc-spvr        4006/udp   pxc-spvr
//pxc-splr        4007/tcp   pxc-splr
//pxc-splr        4007/udp   pxc-splr
//#                          Dave Nesbitt <nesbitt&cp10.es.xerox.com>
//netcheque       4008/tcp   NetCheque accounting 
//netcheque       4008/udp   NetCheque accounting 
//#                          B. Clifford Neuman <bcn&isi.edu>
//chimera-hwm     4009/tcp   Chimera HWM
//chimera-hwm	4009/udp   Chimera HWM
//#			   Ken Anderson <kanderso&kleber.ICS.UCI.EDU>
//samsung-unidex  4010/tcp   Samsung Unidex
//samsung-unidex	4010/udp   Samsung Unidex
//#			   Konstantin V. Vyaznikov <kv&ssm6000.samsung.ru>
//altserviceboot	4011/tcp   Alternate Service Boot
//altserviceboot	4011/udp   Alternate Service Boot
//#			   Eric Dittert <Eric_Dittert&ccm.jf.intel.com>
//pda-gate	4012/tcp   PDA Gate
//pda-gate	4012/udp   PDA Gate
//#			   Masakuni Okada <masakuni&jp.ibm.com>
//acl-manager	4013/tcp   ACL Manager
//acl-manager	4013/udp   ACL Manager
//#			   Toru Murai <murai&saint.nm.fujitsu.co.jp>
//taiclock	4014/tcp   TAICLOCK
//taiclock	4014/udp   TAICLOCK
//#			   Dan Bernstein <djb&koobera.math.uic.edu>
//talarian-mcast1	4015/tcp   Talarian Mcast
//talarian-mcast1	4015/udp   Talarian Mcast
//talarian-mcast2	4016/tcp   Talarian Mcast
//talarian-mcast2	4016/udp   Talarian Mcast
//talarian-mcast3	4017/tcp   Talarian Mcast
//talarian-mcast3	4017/udp   Talarian Mcast
//talarian-mcast4	4018/tcp   Talarian Mcast
//talarian-mcast4	4018/udp   Talarian Mcast
//talarian-mcast5	4019/tcp   Talarian Mcast
//talarian-mcast5	4019/udp   Talarian Mcast
//#			   Geoff Mendal <mendal&talarian.com>
//trap            4020/tcp   TRAP Port
//trap            4020/udp   TRAP Port
//#                          Jeffrey C. Byrd <admin&vspacegroup.com>
//nexus-portal    4021/tcp   Nexus Portal
//nexus-portal    4021/udp   Nexus Portal
//#                          Damian Tarnawsky <support&nexusconcepts.com>
//dnox            4022/tcp   DNOX
//dnox            4022/udp   DNOX
//#                          Leo Rathnayake <leo&perlnet.com>
//esnm-zoning     4023/tcp   ESNM Zoning Port
//esnm-zoning     4023/udp   ESNM Zoning Port
//#                          Yong Cai <ycai&emc.com>
//tnp1-port       4024/tcp   TNP1 User Port
//tnp1-port       4024/udp   TNP1 User Port
//#                          Tony Gibbs <tony.gibbs&europe.simoco.com>
//partimage       4025/tcp   Partition Image Port
//partimage       4025/udp   Partition Image Port
//#                          Franck Ladurelle <ladurelf&partimage.org>
//as-debug        4026/tcp   Graphical Debug Server
//as-debug        4026/udp   Graphical Debug Server
//#                          Steve Halverson <shalver&us.ibm.com>
//bxp             4027/tcp   bitxpress
//bxp             4027/udp   bitxpress
//#                          Morgan Doyle <morgan&mpt.ie>
//dtserver-port   4028/tcp   DTServer Port
//dtserver-port   4028/udp   DTServer Port
//#                          Stephen Aikins <stephen.aikins&embarcadero.com>
//ip-qsig         4029/tcp   IP Q signaling protocol
//ip-qsig         4029/udp   IP Q signaling protocol
//#                          Toru Tachibana <tatibana&exs.ts.fujitsu.co.jp>
//jdmn-port       4030/tcp   Accell/JSP Daemon Port
//jdmn-port       4030/udp   Accell/JSP Daemon Port
//#                          Art Grand <aig&unify.com>
//suucp           4031/tcp   UUCP over SSL
//suucp           4031/udp   UUCP over SSL
//#                          Harald Welte <laforge&gnumonks.org>
//vrts-auth-port  4032/tcp   VERITAS Authorization Service
//vrts-auth-port  4032/udp   VERITAS Authorization Service
//#                          Stefan Winkel <stefan&veritas.com>
//sanavigator     4033/tcp   SANavigator Peer Port
//sanavigator     4033/udp   SANavigator Peer Port
//#                          Robert J. Chansler <robert.chansler&mcdata.com>
//ubxd            4034/tcp   Ubiquinox Daemon 
//ubxd            4034/udp   Ubiquinox Daemon
//#                          Kit Smithers <ksmithers&argogroup.com>
//wap-push-http   4035/tcp   WAP Push OTA-HTTP port
//wap-push-http   4035/udp   WAP Push OTA-HTTP port
//wap-push-https  4036/tcp   WAP Push OTA-HTTP secure
//wap-push-https  4036/udp   WAP Push OTA-HTTP secure
//#                          Matthieu Lachance 
//#                          <matthieu.lachance&openwave.com>
//ravehd          4037/tcp   RaveHD network control
//ravehd          4037/udp   RaveHD network control
//#			   Jason Howard <jason&spectsoft.com> January 2006
//fazzt-ptp	4038/tcp   Fazzt Point-To-Point
//fazzt-ptp	4038/udp   Fazzt Point-To-Point
//fazzt-admin	4039/tcp   Fazzt Administration
//fazzt-admin	4039/udp   Fazzt Administration
//#			   Lewis Wolfgang <wolfgang&kencast.com> May 2006
//yo-main         4040/tcp   Yo.net main service
//yo-main         4040/udp   Yo.net main service
//#                          John Tintor <jt&yo.net>
//houston         4041/tcp   Rocketeer-Houston
//houston         4041/udp   Rocketeer-Houston
//#                          Johnny C. Norris II <jnorris&uiuc.edu>
//ldxp            4042/tcp   LDXP
//ldxp            4042/udp   LDXP
//#                          Craig Calef <craig&katmango.com>    
//nirp            4043/tcp   Neighbour Identity Resolution
//nirp            4043/udp   Neighbour Identity Resolution
//ltp             4044/tcp   Location Tracking Protocol
//ltp             4044/udp   Location Tracking Protocol
//npp             4045/tcp   Network Paging Protocol
//npp             4045/udp   Network Paging Protocol
//acp-proto       4046/tcp   Accounting Protocol 
//acp-proto       4046/udp   Accounting Protocol 
//ctp-state       4047/tcp   Context Transfer Protocol
4047,//ctp-state       4047/udp   Context Transfer Protocol
//#                          Hesham Soliman <H.Soliman&flarion.com> November 2005
//#               4048       Unassigned (Returned 2008-04-24)
4049,//wafs            4049/tcp   Wide Area File Services
//wafs            4049/udp   Wide Area File Services
//#                          Yuval Hager <yuval&avramzon.net> January 2006
//cisco-wafs      4050/tcp   Wide Area File Services
//cisco-wafs      4050/udp   Wide Area File Services
//#                          Etai Lev-Ran <elevran&cisco.com> February 2005
//cppdp		4051/tcp   Cisco Peer to Peer Distribution Protocol
//cppdp		4051/udp   Cisco Peer to Peer Distribution Protocol
//#			   Susan Sauter <ssauter&cisco.com> July 2006
//interact	4052/tcp   VoiceConnect Interact
//interact	4052/udp   VoiceConnect Interact
//#			   Jonathan Custance <jevc&camrivox.com> July 2006
//ccu-comm-1	4053/tcp   CosmoCall Universe Communications Port 1
//ccu-comm-1	4053/udp   CosmoCall Universe Communications Port 1
//ccu-comm-2	4054/tcp   CosmoCall Universe Communications Port 2
//ccu-comm-2	4054/udp   CosmoCall Universe Communications Port 2
//ccu-comm-3	4055/tcp   CosmoCall Universe Communications Port 3
//ccu-comm-3	4055/udp   CosmoCall Universe Communications Port 3
//#			   Steve Dellutri <sdellutri&cosmocom.com> July 2006
//lms		4056/tcp   Location Message Service
//lms		4056/udp   Location Message Service
//#			   Sergey Burnevsky <sergey.burnevsky&nokia.com> August 2006
//wfm		4057/tcp   Servigistics WFM server
//wfm		4057/udp   Servigistics WFM server
//#			   Yuri Machkasov <ymachkasov&servigistics.com> August 2006
//kingfisher	4058/tcp   Kingfisher protocol
//kingfisher	4058/udp   Kingfisher protocol
//#			   Vaughan Wesson <vaughanw&rtunet.com> October 2006
//dlms-cosem	4059/tcp   DLMS/COSEM 
//dlms-cosem	4059/udp   DLMS/COSEM 
//#			   Gyozo Kmethy <gyozo.kmethy&gnarus.hu> November 2006
//dsmeter_iatc	4060/tcp   DSMETER Inter-Agent Transfer Channel
//dsmeter_iatc	4060/udp   DSMETER Inter-Agent Transfer Channel
//#			   john mccann <jmccann&visualclick.com> December 2006
//ice-location	4061/tcp   Ice Location Service (TCP)
//ice-location	4061/udp   Ice Location Service (TCP)
//ice-slocation	4062/tcp   Ice Location Service (SSL)
//ice-slocation	4062/udp   Ice Location Service (SSL)
//ice-router	4063/tcp   Ice Firewall Traversal Service (TCP)
//ice-router	4063/udp   Ice Firewall Traversal Service (TCP)
//ice-srouter 	4064/tcp   Ice Firewall Traversal Service (SSL)
//ice-srouter	4064/udp   Ice Firewall Traversal Service (SSL)
//#			   Bernard Normier <bernard&zeroc.com> December 2006
//avanti_cdp	4065/tcp   Avanti Common Data 
//avanti_cdp	4065/udp   Avanti Common Data 
//#			   Steve Meyer, Sr. <stevem&avanti-tech.com> February 2007
//pmas		4066/tcp   Performance Measurement and Analysis
//pmas		4066/udp   Performance Measurement and Analysis
//#			   Zenon Fortuna <zenon&mips.com> February 2007
//idp		4067/tcp   Information Distribution Protocol
//idp		4067/udp   Information Distribution Protocol
//#			   Michaela Vanderveen <mvandervn&yahoo.com> February 2007
//ipfltbcst	4068/tcp   IP Fleet Broadcast
//ipfltbcst	4068/udp   IP Fleet Broadcast
//#			   Trung Huu Tran <trung.tran&navy.mil> March 2007
//minger		4069/tcp   Minger Email Address Validation Service
//minger		4069/udp   Minger Email Address Validation Service
//#			   Arvel Hathcock <arvel&altn.com> March 2007
//tripe		4070/tcp   Trivial IP Encryption (TrIPE)
//tripe		4070/udp   Trivial IP Encryption (TrIPE)
//#			   Mark Wooding <mdw&distorted.org.uk> 10 July 2007
//aibkup		4071/tcp   Automatically Incremental Backup
//aibkup		4071/udp   Automatically Incremental Backup
//#			   Volker Wiegand <volker.wiegand&t-online.de> 10 July 2007
//zieto-sock	4072/tcp   Zieto Socket Communications
//zieto-sock	4072/udp   Zieto Socket Communications
//#			   Malcolm McLean <malcolmm&zieto.co.za> 19 July 2007
//iRAPP		4073/tcp   iRAPP Server Protocol
//iRAPP		4073/udp   iRAPP Server Protocol
//#			   Vladimir Bickov <vbickov&coderebel.com> 20 August 2007
//cequint-cityid  4074/tcp   Cequint City ID UI trigger
//cequint-cityid  4074/udp   Cequint City ID UI trigger
//#			   Phill Goeckler <pgoeckler&Cequint.com> 20 August 2007
//perimlan	4075/tcp   ISC Alarm Message Service
//perimlan	4075/udp   ISC Alarm Message Service
//#			   Bernie Malkowski <bmalkowski&integratedsecuritycorp.com> 20 August 2007
//seraph          4076/tcp   Seraph DCS
//seraph          4076/udp   Seraph DCS
//#                          Jason Spence <jspence&lightconsulting.com> 22 January 2008
//#               4077/tcp   Reserved 
//ascomalarm      4077/udp   Ascom IP Alarming
//#                          Ascom Austria GmbH <info&ascom.at> 01 May 2008
//cssp            4078/tcp   Coordinated Security Service Protocol
//#                          Michael McDaniels on behalf of Extreme Networks, Inc <mmcdaniels&extremenetworks.com> 01 May 2008
//#               4078/udp   Reserved 
//santools        4079/tcp   SANtools Diagnostic Server
//santools        4079/udp   SANtools Diagnostic Server
//#                          David A Lethe <david&santools.com> 01 May 2008
//lorica-in       4080/tcp   Lorica inside facing 
//lorica-in       4080/udp   Lorica inside facing 
//lorica-in-sec   4081/tcp   Lorica inside facing (SSL)
//lorica-in-sec   4081/udp   Lorica inside facing (SSL)
//lorica-out      4082/tcp   Lorica outside facing
//lorica-out      4082/udp   Lorica outside facing
//lorica-out-sec  4083/tcp   Lorica outside facing (SSL)
//lorica-out-sec  4083/udp   Lorica outside facing (SSL)
//#                          Johannes Skov Frandsen <joe&42tools.com> 28 February 2008
//#               4084/tcp   Reserved
//fortisphere-vm  4084/udp   Fortisphere VM Service
//#                          Daniel Becker <Dan.Becker&Fortisphere.com> 03 June 2008
//ezmessagesrv    4085/tcp   EZNews Newsroom Message Service
//#                          Gerald R. Jensen <tech&autodatasys.com> 05 June 2008
//#               4085/udp   Reserved
//#               4086/tcp   Reserved
//ftsync          4086/udp   Firewall/NAT state table synchronization
//#                          Heiner Erne, Hirschmann Automation and Control GmbH 
//#                          <heiner.erne&hirschmann.de> 06 June 2008
//applusservice   4087/tcp   APplus Service
//#                          Thomas Boerkel <tbo&ap-ag.com> 05 June 2008 
//#               4087/udp   Reserved
//npsp            4088/tcp   Noah Printing Service Protocol
//#                          Hiromi Ohara <Hiromi.Ohara&fujixerox.co.jp> 18 June 2008
//#               4088/udp   Reserved
//opencore	4089/tcp   OpenCORE Remote Control Service
//opencore	4089/udp   OpenCORE Remote Control Service
//#			   Pim van Riezen <registries&panelsix.com> July 2006
//omasgport	4090/tcp   OMA BCAST Service Guide
//omasgport	4090/udp   OMA BCAST Service Guide
//#			   Mark Lipford <mark.a.lipford&sprint.com> July 2006
//ewinstaller	4091/tcp   EminentWare Installer
//ewinstaller	4091/udp   EminentWare Installer
//ewdgs		4092/tcp   EminentWare DGS
//ewdgs		4092/udp   EminentWare DGS
//#			   David A. Gayler <dgayler&eminentware.com> July 2006
//pvxpluscs	4093/tcp   Pvx Plus CS Host
//pvxpluscs	4093/udp   Pvx Plus CS Host
//#			   Michael King <mike.king&pvxplus.com> July 2006
//sysrqd		4094/tcp   sysrq daemon
//sysrqd		4094/udp   sysrq daemon
//#			   Julien Danjou <acid&debian.org> July 2006
//xtgui		4095/tcp   xtgui information service
//xtgui		4095/udp   xtgui information service
//#			   Jim Robanske <jimr&cray.com> May 2006
//bre 		4096/tcp   BRE (Bridge Relay Element)
//bre 		4096/udp   BRE (Bridge Relay Element)
//#			   Stephen Egbert <egbert&ra.timeplex.com>
//patrolview	4097/tcp   Patrol View
//patrolview	4097/udp   Patrol View
//#			   Portnoy Boxman <portnoy_boxman&bmc.com>
//drmsfsd		4098/tcp   drmsfsd
//drmsfsd		4098/udp   drmsfsd
//#			   Masao Iwai <iwai&kel.fujitsu.co.jp>
//dpcp		4099/tcp   DPCP
//dpcp		4099/udp   DPCP
//#			   John Croft <john.croft&calista.demon.co.uk>
//igo-incognito   4100/tcp   IGo Incognito Data Port
//igo-incognito   4100/udp   IGo Incognito Data Port
//#                          Paul Reddy <support&igo-incognito.com> February 2002
//brlp-0		4101/tcp   Braille protocol
//brlp-0		4101/udp   Braille protocol
//brlp-1		4102/tcp   Braille protocol
//brlp-1		4102/udp   Braille protocol
//brlp-2		4103/tcp   Braille protocol
//brlp-2		4103/udp   Braille protocol
//brlp-3		4104/tcp   Braille protocol
//brlp-3		4104/udp   Braille protocol
//#			   S�bastien Hinderer <Sebastien.Hinderer&ens-lyon.org> March 2006
//shofarplayer    4105/tcp   ShofarPlayer
//shofarplayer    4105/udp   ShofarPlayer
//#			   John Kozlowski <John.Kozlowski&HeritageSystems.com> July 2006
//synchronite	4106/tcp   Synchronite
//synchronite	4106/udp   Synchronite
//#			   James Figgins <james.figgins&durodata.co.uk> July 2006
//j-ac		4107/tcp   JDL Accounting LAN Service
//j-ac		4107/udp   JDL Accounting LAN Service
//#			   Takashi Sahara <sahara&jdl.co.jp> September 2006
//accel		4108/tcp   ACCEL
//accel		4108/udp   ACCEL
//#			   Masahiro Koiwai <Koiwai.Masahiro&exc.epson.co.jp> October 2006
//izm		4109/tcp   Instantiated Zero-control Messaging
//izm		4109/udp   Instantiated Zero-control Messaging
//#			   David Miller <dave.dsm&gmail.com> February 2007
//g2tag		4110/tcp   G2 RFID Tag Telemetry Data
//g2tag		4110/udp   G2 RFID Tag Telemetry Data
//#			   David Goodall <david.goodall&g2microsystems.com> February 2007
//xgrid           4111/tcp   Xgrid
//xgrid           4111/udp   Xgrid
//#                          David Kramer <dkramer&apple.com> November 2004
//apple-vpns-rp	4112/tcp   Apple VPN Server Reporting Protocol
//apple-vpns-rp	4112/udp   Apple VPN Server Reporting Protocol
//#			   Christophe Allie <callie&apple.com> August 2006
//aipn-reg	4113/tcp   AIPN LS Registration
//aipn-reg	4113/udp   AIPN LS Registration
//#			   Qiang Zhang <iad&iwncomm.com> October 2006
//jomamqmonitor   4114/tcp   JomaMQMonitor
//jomamqmonitor   4114/udp   JomaMQMonitor
//#                          Marcel Hofstetter <marcel.hofstetter&jomasoft.ch> January 2003       
//cds		4115/tcp   CDS Transfer Agent
//cds		4115/udp   CDS Transfer Agent
//#			   Neil Coggins <neil.coggins&6thsight.com> July 2006
//smartcard-tls	4116/tcp   smartcard-TLS
//smartcard-tls	4116/udp   smartcard-TLS
//#			   Ilan Mahalal <imahalal&axalto.com> April 2006
//hillrserv       4117/tcp   Hillr Connection Manager
//hillrserv       4117/udp   Hillr Connection Manager
//#                          Previous record: Freddy A. Ayuso-Henson <frecom32&hotmail.com> November 2006
//#                          Current record: Freddy A. Ayuso-Henson <fayusohenson&hillr.com> 22 May 2008
//netscript	4118/tcp   Netadmin Systems NETscript service
//netscript	4118/udp   Netadmin Systems NETscript service
//#			   G�ran Runfeldt <goran&netadmin.se> December 2006
//assuria-slm	4119/tcp   Assuria Log Manager
4119,//assuria-slm	4119/udp   Assuria Log Manager
//#			   Nick Connor <nickc&assuria.com> December 2006
//#		4120       Unassigned (Returned on 2007-02-01)
4121,//e-builder	4121/tcp   e-Builder Application Communication
//e-builder	4121/udp   e-Builder Application Communication
//#			   James Caza <jcaza&e-builder.net> December 2006
//fprams		4122/tcp   Fiber Patrol Alarm Service
//fprams		4122/udp   Fiber Patrol Alarm Service
//#			   Zhizhong Zhuang <ZZhuang&Optellios.com> December 2006
//z-wave		4123/tcp   Zensys Z-Wave Control Protocol
//z-wave		4123/udp   Zensys Z-Wave Control Protocol
//#			   Anders Brandt, Zensys Inc. <abr&zen-sys.com> February 2007
//tigv2		4124/tcp   Rohill TetraNode Ip Gateway v2
//tigv2		4124/udp   Rohill TetraNode Ip Gateway v2
//#			   Bert Bouwers <e.bouwers&rohill.nl> May 2007
//opsview-envoy	4125/tcp   Opsview Envoy
//opsview-envoy	4125/udp   Opsview Envoy
//#			   Previous contact: Ton Voon <ton.voon&altinity.com> May 2007
//#			   Current contact: Ton Voon <ton.voon&opsera.com> 26 September 2008
//ddrepl		4126/tcp   Data Domain Replication Service
//ddrepl		4126/udp   Data Domain Replication Service
//#			   Pratik Wadher <pratik&datadomain.com> May 2007
//unikeypro	4127/tcp   NetUniKeyServer
//unikeypro	4127/udp   NetUniKeyServer
//#			   Raymond Chaw <Raymond&eSecuTech.com> May 2007
//nufw		4128/tcp   NuFW decision delegation protocol
//nufw		4128/udp   NuFW decision delegation protocol
//nuauth		4129/tcp   NuFW authentication protocol
//nuauth		4129/udp   NuFW authentication protocol
//#			   Eric Leblond <eric&inl.fr> June 2007
//fronet		4130/tcp   FRONET message protocol
//fronet		4130/udp   FRONET message protocol
//#			   Christer Nygren <christer.nygren&fro.se> 07 August 2007
//stars		4131/tcp   Global Maintech Stars
//stars		4131/udp   Global Maintech Stars
//#			   Harry Goldschmitt <harry&hgac.com> June 2007
//nuts_dem        4132/tcp   NUTS Daemon
//nuts_dem        4132/udp   NUTS Daemon
//nuts_bootp      4133/tcp   NUTS Bootp Server
//nuts_bootp      4133/udp   NUTS Bootp Server
//#                          Martin Freiss <freiss.pad@sni.>
//nifty-hmi       4134/tcp   NIFTY-Serve HMI protocol
//nifty-hmi       4134/udp   NIFTY-Serve HMI protocol
//#                          Ryuichi Suzuki <SCI00376&niftyserve.or.jp>
//cl-db-attach	4135/tcp   Classic Line Database Server Attach
//cl-db-attach	4135/udp   Classic Line Database Server Attach
//cl-db-request	4136/tcp   Classic Line Database Server Request
//cl-db-request	4136/udp   Classic Line Database Server Request
//cl-db-remote	4137/tcp   Classic Line Database Server Remote
//cl-db-remote	4137/udp   Classic Line Database Server Remote
//#			   Arno Kirmeir <Arno.kirmeir&sage.de> January 2007
//nettest         4138/tcp   nettest
//nettest         4138/udp   nettest
//#                          David Borman <dab&windriver.com> March 2003
//thrtx		4139/tcp   Imperfect Networks Server
//thrtx		4139/udp   Imperfect Networks Server
//#			   Dinkar Chivaluri <dchivaluri&imperfectnetworks.com> February 2006
//cedros_fds	4140/tcp   Cedros Fraud Detection System
//cedros_fds	4140/udp   Cedros Fraud Detection System
//#			   Markus Michels <markus.michels&cedros.com> October 2006
//oirtgsvc        4141/tcp   Workflow Server
//oirtgsvc        4141/udp   Workflow Server
//oidocsvc        4142/tcp   Document Server
//oidocsvc        4142/udp   Document Server
//oidsr           4143/tcp   Document Replication
4143,//oidsr           4143/udp   Document Replication
//#                          Norman Brie <norm_brie&sns.ca>
//##########  Compuserve (unoffically) is using port 4144 #########
//#               4144       Unassigned
4145,//vvr-control     4145/tcp   VVR Control
//vvr-control     4145/udp   VVR Control
//#                          Ming Xu <ming&veritas.com>
//tgcconnect	4146/tcp   TGCConnect Beacon
//tgcconnect	4146/udp   TGCConnect Beacon
//#			   Brian Becker <bbecker&tgc-usa.com> October 2006
//vrxpservman	4147/tcp   Multum Service Manager
//vrxpservman	4147/udp   Multum Service Manager
//#			   Scott Mager <Scott.Mager&cerner.com> October 2006
//hhb-handheld	4148/tcp   HHB Handheld Client
//hhb-handheld	4148/udp   HHB Handheld Client
//#			   Steven G. Loughner <stevengloughner&eaton.com> March 2007
//agslb		4149/tcp   A10 GSLB Service
//agslb		4149/udp   A10 GSLB Service
//#			   John Chiong <jchiong&a10networks.com> 02 July 2007
//PowerAlert-nsa  4150/tcp   PowerAlert Network Shutdown Agent
//PowerAlert-nsa  4150/udp   PowerAlert Network Shutdown Agent
//#			   Mike Delgrosso <Mike_Delgrosso&tripplite.com> 02 July 2007
//menandmice_noh	4151/tcp   Men & Mice Remote Control
//menandmice_noh	4151/udp   Men & Mice Remote Control
//#			   Eggert Thorlacius <eggert&menandmice.com> 30 August 2007
//idig_mux	4152/tcp   iDigTech Multiplex
//idig_mux	4152/udp   iDigTech Multiplex
//#			   Robin Findley <rfindley&usa.net> May 2007
//mbl-battd	4153/tcp   MBL Remote Battery Monitoring
//mbl-battd	4153/udp   MBL Remote Battery Monitoring
//#			   Claudio Procida <claudio&emeraldion.it> May 2007
//atlinks         4154/tcp   atlinks device discovery
//atlinks         4154/udp   atlinks device discovery
//#                          Scott Griepentrog <griepentrogs&atlinks.com> October 2002
//bzr		4155/tcp   Bazaar version control system
//bzr		4155/udp   Bazaar version control system
//#			   Martin Pool <mbp&canonical.com> February 2007
//stat-results	4156/tcp   STAT Results
//stat-results	4156/udp   STAT Results
//stat-scanner	4157/tcp   STAT Scanner Control
//stat-scanner	4157/udp   STAT Scanner Control
//stat-cc		4158/tcp   STAT Command Center
//stat-cc		4158/udp   STAT Command Center
//#			   Darwin Ammala <dammala&harris.com> March 2007
//nss		4159/tcp   Network Security Service
//nss		4159/udp   Network Security Service
//#			   Dave Wierbowski <wierbows&us.ibm.com> August 2006
//jini-discovery  4160/tcp   Jini Discovery
//jini-discovery  4160/udp   Jini Discovery
//#                          Mark Hodapp <mark.hodapp&sun.com>	
//omscontact      4161/tcp   OMS Contact
//omscontact      4161/udp   OMS Contact
//omstopology     4162/tcp   OMS Topology
//omstopology     4162/udp   OMS Topology
//#                          David Page <david.page&sun.com> August 2005
//silverpeakpeer	4163/tcp   Silver Peak Peer Protocol
//silverpeakpeer	4163/udp   Silver Peak Peer Protocol
//#			   Damon Ennis <damon&silver-peak.com> March 2007
//silverpeakcomm	4164/tcp   Silver Peak Communication Protocol
//silverpeakcomm	4164/udp   Silver Peak Communication Protocol
//#			   Damon Ennis <damon&silver-peak.com> March 2007
//altcp		4165/tcp   ArcLink over Ethernet
//altcp		4165/udp   ArcLink over Ethernet
//#			   Dmitry Brant <dmitry_brant&lincolnelectric.com> March 2007
//joost		4166/tcp   Joost Peer to Peer Protocol
//joost		4166/udp   Joost Peer to Peer Protocol
//#			   Colm MacCarthaigh <colm.maccarthaigh&joost.com> April 2007
//ddgn		4167/tcp   DeskDirect Global Network
//ddgn		4167/udp   DeskDirect Global Network
//#			   Laurie Charlwood <laurie.charlwood&printsoft.com> 22 August 2007
//pslicser	4168/tcp   PrintSoft License Server
//pslicser	4168/udp   PrintSoft License Server
//#			   David Weisgerber <david.weisgerber&printsoft.de> 27 September 2007
//iadt            4169/tcp   Automation Drive Interface Transport
//#                          Paul Suhler <paul.suhler&quantum.com> 15 February 2008
//iadt-disc       4169/udp   Internet ADT Discovery Protocol
//#                          Paul A. Suhler <paul.suhler&quantum.com> 06 February 2009
//d-cinema-csp    4170/tcp   SMPTE Content Synchonization Protocol
//#                          Michael Karagosian <michael.karagosian&mkpe.com> 04 September 2008
4170,//#               4170/udp   Reserved
//#               4171-4176  Unassigned
4177,//wello		4177/tcp   Wello P2P pubsub service
//wello		4177/udp   Wello P2P pubsub service
//#			   Christian Westbrook <cw&wellohorld.com> 15 November 2007
//storman		4178/tcp   StorMan
//storman		4178/udp   StorMan
//#			   Previous contact: Werner Guertler <Werner.Guertler&fujitsu-siemens.com> February 2007
//#                          Current contact: Werner Guertler <werner.guertler&ts.fujitsu.com> 11 May 2009
//MaxumSP		4179/tcp   Maxum Services
//MaxumSP		4179/udp   Maxum Services
//#			   Greg Stine <greg.stine&siemens.com> 05 July 2007
//httpx		4180/tcp   HTTPX
//httpx		4180/udp   HTTPX
//#			   Paul McGough <pmcgough&2factor.com> February 2007
//macbak		4181/tcp   MacBak
//macbak		4181/udp   MacBak
//#			   Wes Peters <wes&softweyr.com> April 2007
//pcptcpservice	4182/tcp   Production Company Pro TCP Service
//pcptcpservice	4182/udp   Production Company Pro TCP Service
//#			   Ben McNeill <ben.mcneill&cinexec.com> May 2007
//gmmp		4183/tcp   General Metaverse Messaging Protocol
//gmmp		4183/udp   General Metaverse Messaging Protocol
//#			   Gareth Nelson <gareth&garethnelson.com> June 2007
//universe_suite  4184/tcp   UNIVERSE SUITE MESSAGE SERVICE
//universe_suite  4184/udp   UNIVERSE SUITE MESSAGE SERVICE
//#                          Gary ANDREWS <gan&orsyp.com> 07 January 2008
//wcpp            4185/tcp   Woven Control Plane Protocol
//wcpp            4185/udp   Woven Control Plane Protocol
//#                          Christopher LILJENSTOLPE <cdl&asgaard.org> 14 April 2008
//boxbackupstore  4186/tcp   Box Backup Store Service
//#                          Chris Wilson <chris+iana&qwirx.com> 11 September 2008
//#               4186/udp   Reserved
//csc_proxy       4187/tcp   Cascade Proxy
//#                          Matt Craighead <matt.craighead&conifersystems.com> 11 September 2008
//#               4187/udp   Reserved  
//vatata          4188/tcp   Vatata Peer to Peer Protocol
//vatata          4188/udp   Vatata Peer to Peer Protocol
//#                          Song Jian <info&vatata.com> 15 September 2008
//pcep            4189/tcp   Path Computation Element Communication Protocol
//#               4189/udp   Reserved
//#                          [RFC5440]
//sieve           4190/tcp   ManageSieve Protocol
//#               4190/udp   Reserved
//#                          [RFC-ietf-sieve-managesieve-09.txt]
//#               4191/tcp   Reserved
4191,//dsmipv6         4191/udp   Dual Stack MIPv6 NAT Traversal
//#                          [RFC5555]
//#               4192-4198  Unassigned
4199,//eims-admin      4199/tcp   EIMS ADMIN
//eims-admin      4199/udp   EIMS ADMIN
//#                          Glenn Anderson <glenn&qualcomm.co.nz> 
//vrml-multi-use  4200-4299  VRML Multi User Systems
//#			   Mitra <mitra&earth.path.net>
//corelccam	4300/tcp   Corel CCam
//corelccam	4300/udp   Corel CCam
//#			   Jason Aiken <jasona&corelcomputer.com>
//d-data		4301/tcp   Diagnostic Data
//d-data		4301/udp   Diagnostic Data 
//d-data-control	4302/tcp   Diagnostic Data Control
//d-data-control	4302/udp   Diagnostic Data Control
//#			   Jon March <jon.march&paget-analyst-services.co.uk> September 2006
//srcp		4303/tcp   Simple Railroad Command Protocol
//srcp		4303/udp   Simple Railroad Command Protocol
//#			   Matthias Trute <mtrute&web.de> January 2007
//owserver	4304/tcp   One-Wire Filesystem Server
//owserver	4304/udp   One-Wire Filesystem Server
//#			   Paul Alfille <paul.alfille&gmail.com> January 2007
//batman		4305/tcp   better approach to mobile ad-hoc networking
//batman		4305/udp   better approach to mobile ad-hoc networking
//#			   Simon Wunderlich <siwu&hrz.tu-chemnitz.de> 30 August 2007
//pinghgl		4306/tcp   Hellgate London
//pinghgl		4306/udp   Hellgate London
//#			   David Berk <dberk&ping-0.com> 30 August 2007
//visicron-vs     4307/tcp   Visicron Videoconference Service
//visicron-vs     4307/udp   Visicron Videoconference Service
//#			   Alexey Vlaskin <avlaskin&visicron.com> 22 October 2007
//compx-lockview  4308/tcp   CompX-LockView
//compx-lockview  4308/udp   CompX-LockView
//#			   John Payson <john&circad.com> 22 October 2007
//dserver		4309/tcp   Exsequi Appliance Discovery
//dserver		4309/udp   Exsequi Appliance Discovery
//#			   Angelo Masci <angelomasci&yahoo.co.uk> January 2007
//mirrtex         4310/tcp   Mir-RT exchange service 
4310,//mirrtex         4310/udp   Mir-RT exchange service 
//#                          Sylvain Robert <sylvain.robert&datadis.com> 14 February 2008
//#		4311-4319  Unassigned
4320,//fdt-rcatp	4320/tcp   FDT Remote Categorization Protocol
//fdt-rcatp	4320/udp   FDT Remote Categorization Protocol
//#			   Russell P. Holsclaw, Fast Data Technology, Inc. <rholsclaw&fastdatatech.com> March 2006
//rwhois          4321/tcp   Remote Who Is
//rwhois          4321/udp   Remote Who Is
//#                          Mark Kosters  <markk&internic.net>
//trim-event	4322/tcp   TRIM Event Service
//trim-event	4322/udp   TRIM Event Service
//trim-ice 	4323/tcp   TRIM ICE Service
//trim-ice 	4323/udp   TRIM ICE Service
//#			   Siva Poobalasingam <Siva.Poobalasingam&towersoft.com.au> February 2007
//balour		4324/tcp   Balour Game Server
//balour		4324/udp   Balour Game Server
//#			   Konstantin Schauwecker <hi&konstantin-schauwecker.de> February 2007
//geognosisman	4325/tcp   Cadcorp GeognoSIS Manager Service
//geognosisman	4325/udp   Cadcorp GeognoSIS Manager Service
//geognosis	4326/tcp   Cadcorp GeognoSIS Service
//geognosis	4326/udp   Cadcorp GeognoSIS Service
//#			   Martin Daly <martin.daly&cadcorp.com> November 2006
//jaxer-web       4327/tcp   Jaxer Web Protocol
//jaxer-web       4327/udp   Jaxer Web Protocol
//#                          Uri Sarid <uri&aptana.com> 07 January 2008
//jaxer-manager   4328/tcp   Jaxer Manager Command Protocol
4328,//jaxer-manager   4328/udp   Jaxer Manager Command Protocol
//#                          Uri Sarid <uri&aptana.com> 22 January 2008
//#		4329-4339  Unassigned
4340,//gaia		4340/tcp   Gaia Connector Protocol
//gaia		4340/udp   Gaia Connector Protocol
//#			   Philippe Detournay <philippe.detournay&acrosoft.be> 12 November 2007
//lisp-data	4341/tcp   LISP Data Packets
//lisp-data	4341/udp   LISP Data Packets
//#			   Dino Farinacci <dino&cisco.com> 12 November 2007
//lisp-cons	4342/tcp   LISP-CONS Control
//lisp-control	4342/udp   LISP Data-Triggered Control
//#			   Dino Farinacci <dino&cisco.com> May 2007
//unicall         4343/tcp   UNICALL
//unicall         4343/udp   UNICALL
//#                          James Powell <james&enghp.unidata.comp>
//vinainstall 	4344/tcp   VinaInstall
//vinainstall	4344/udp   VinaInstall
//#			   Jay Slupesky <js&vina-tech.com>
//m4-network-as	4345/tcp   Macro 4 Network AS
//m4-network-as   4345/udp   Macro 4 Network AS
//#			   Paul Wren <Paul.Wren&macro4.com>
//elanlm		4346/tcp   ELAN LM
//elanlm		4346/udp   ELAN LM
//#			   Paul Ballew <ballew&projtech.com>
//lansurveyor	4347/tcp   LAN Surveyor
//lansurveyor	4347/udp   LAN Surveyor
//#			   Michael Swan <swan&neon.com>
//itose		4348/tcp   ITOSE
//itose		4348/udp   ITOSE
//#			   Michael Haeuptle <Michael_Haeuptle&hp.com>
//fsportmap	4349/tcp   File System Port Map
//fsportmap	4349/udp   File System Port Map
//#			   Ron Minnich <rminnich&sarnoff.com>
//net-device	4350/tcp   Net Device
//net-device	4350/udp   Net Device
//#			   Glenn Peterson <glennp&microsoft.com>
//plcy-net-svcs	4351/tcp   PLCY Net Services
//plcy-net-svcs	4351/udp   PLCY Net Services
//#                          J.J. Ekstrom
//pjlink          4352/tcp   Projector Link
//pjlink          4352/udp   Projector Link
//#                          Mitsuo Kodama <kodama&jbmia.or.jp> June 2005
//f5-iquery       4353/tcp   F5 iQuery 
//f5-iquery       4353/udp   F5 iQuery 
//#                          Tom Kee <t.kee&f5.com>
//qsnet-trans     4354/tcp   QSNet Transmitter
//qsnet-trans     4354/udp   QSNet Transmitter
//qsnet-workst    4355/tcp   QSNet Workstation
//qsnet-workst    4355/udp   QSNet Workstation
//qsnet-assist    4356/tcp   QSNet Assistant
//qsnet-assist    4356/udp   QSNet Assistant
//qsnet-cond      4357/tcp   QSNet Conductor
//qsnet-cond      4357/udp   QSNet Conductor
//qsnet-nucl      4358/tcp   QSNet Nucleus
//qsnet-nucl      4358/udp   QSNet Nucleus
//#                          Neer Kleinman <neer&qsr.co.il>
//omabcastltkm	4359/tcp   OMA BCAST Long-Term Key Messages
//omabcastltkm	4359/udp   OMA BCAST Long-Term Key Messages
//#			   Frank Hartung <Frank.Hartung&ericsson.com> 07 September 2007
//matrix_vnet     4360/tcp   Matrix VNet Communication Protocol
//#                          Rehan Mahmood <rehan&matrixmultimedia.co.uk> 18 March 2009
//#               4360/udp   Reserved
//#               4361/tcp   Reserved
4361,//nacnl           4361/udp   NavCom Discovery and Control Port
//#                          Yilei Jia <yjia&navcomtech.com> 18 March 2009
//#               4362-4367  Unassigned
4368,//wxbrief		4368/tcp   WeatherBrief Direct
//wxbrief		4368/udp   WeatherBrief Direct
//#			   Kim Alan Waggoner <kimw&weatherbank.com> November 2006
//epmd            4369/tcp   Erlang Port Mapper Daemon
//epmd            4369/udp   Erlang Port Mapper Daemon
//#                          Erlang/OTP support <epmd&erix.ericsson.se> December 2004
//elpro_tunnel    4370/tcp   ELPRO V2 Protocol Tunnel
//elpro_tunnel    4370/udp   ELPRO V2 Protocol Tunnel
//#                          Harry Courtice <harry.courtice&elprotech.com> 14 April 2008
//l2c-connect     4371/tcp   LAN 2 CAN connection service
//#                          Phil Tolson <philtolson&eaton.com> 07 July 2008
//#               4371/udp   Reserved
//l2c-info        4372/tcp   LAN 2 CAN information service 
//#                          Phil Tolson <philtolson&eaton.com> 07 July 2008
//#               4372/udp   Reserved
//remctl		4373/tcp   Remote Authenticated Command Service
//remctl		4373/udp   Remote Authenticated Command Service
//#			   Russ Allbery <rra&stanford.edu> 30 August 2007
//psi-ptt         4374/tcp   PSI Push-to-Talk Protocol
//#                          Frank Bredenbr�cker <fbredenbroecker&psi.de> 17 July 2008
//#               4374/udp   Reserved
//tolteces        4375/tcp   Toltec EasyShare
//tolteces        4375/udp   Toltec EasyShare
//#                          Joon Radley <joon&toltec.co.za, support&toltec.co.za> 21 October 2008
//bip		4376/tcp   BioAPI Interworking 
//bip		4376/udp   BioAPI Interworking 
//#			   Jean-Paul Lemaire <jean-paul.lemaire&univ-paris-diderot.fr> 05 July 2007
//cp-spxsvr	4377/tcp   Cambridge Pixel SPx Server
//cp-spxsvr	4377/udp   Cambridge Pixel SPx Server
//cp-spxdpy	4378/tcp   Cambridge Pixel SPx Display
//cp-spxdpy	4378/udp   Cambridge Pixel SPx Display
//#			   Richard Warren <richard&cambridgepixel.com> 05 July 2007
//ctdb		4379/tcp   CTDB
4379,//ctdb		4379/udp   CTDB
//#			   Ronnie Sahlberg <ronniesahlberg&gmail.com> 05 July 2007
//#               4380-4388  Unassigned
4389,//xandros-cms	4389/tcp   Xandros Community Management Service
//xandros-cms	4389/udp   Xandros Community Management Service
//#			   Stephen M. Webb <stephenw&xandros.com> May 2007
//wiegand         4390/tcp   Physical Access Control
//wiegand         4390/udp   Physical Access Control
//#                          Scott Guthery <sguthery&hidcorp.com> 25 August 2008
//apwi-imserver   4391/tcp   American Printware IMServer Protocol
//#                          Lech Lakomy <llakomy&apwi.com> 12 February 2009
//#               4391/udp   Reserved
//apwi-rxserver   4392/tcp   American Printware RXServer Protocol
//#                          Lech Lakomy <llakomy&apwi.com> 12 February 2009
//#               4392/udp   Reserved
//apwi-rxspooler  4393/tcp   American Printware RXSpooler Protocol
//#                          Lech Lakomy <llakomy&apwi.com> 12 February 2009
//#               4393/udp   Reserved
//#               4394/tcp   Reserved
//apwi-disc       4394/udp   American Printware Discovery
//#                          Lech Lakomy <llakomy&apwi.com> 12 February 2009
//omnivisionesx   4395/tcp   OmniVision communication for Virtual environments
//omnivisionesx   4395/udp   OmniVision communication for Virtual environments
//#                          Vacquier Serge <vacquier&systar.fr> 12 February 2009
//fly             4396/tcp   Fly Object Space
//#                          Nigel Warren <info&flyobjectspace.com> 12 February 2009
4396,//#               4396/udp   Reserved
//#               4397-4399  Unassigned
4400,//ds-srv          4400/tcp   ASIGRA Services
//ds-srv          4400/udp   ASIGRA Services
//#                          David Farajun <dfarajun&asigra.com> November 2004
//ds-srvr         4401/tcp   ASIGRA Televaulting DS-System Service
//ds-srvr         4401/udp   ASIGRA Televaulting DS-System Service
//ds-clnt         4402/tcp   ASIGRA Televaulting DS-Client Service
//ds-clnt         4402/udp   ASIGRA Televaulting DS-Client Service
//ds-user         4403/tcp   ASIGRA Televaulting DS-Client Monitoring/Management
//ds-user         4403/udp   ASIGRA Televaulting DS-Client Monitoring/Management
//ds-admin        4404/tcp   ASIGRA Televaulting DS-System Monitoring/Management
//ds-admin        4404/udp   ASIGRA Televaulting DS-System Monitoring/Management
//ds-mail         4405/tcp   ASIGRA Televaulting Message Level Restore service
//ds-mail         4405/udp   ASIGRA Televaulting Message Level Restore service
//ds-slp          4406/tcp   ASIGRA Televaulting DS-Sleeper Service
//ds-slp          4406/udp   ASIGRA Televaulting DS-Sleeper Service
//#                          Andrei Litvinn <support&asigra.com> January 2005
//nacagent        4407/tcp   Network Access Control Agent
//#                          ITGroup <itgroup&stillsecure.com> 30 June 2008
//#               4407/udp   Reserved
//slscc           4408/tcp   SLS Technology Control Centre
//#                          Steven Sweeting <ssweeting&sls-technology.com> 28 January 2008
4408,//#               4408/udp   Reserved
//#               4409-4425  Unassigned
4426,//beacon-port-2   4426/tcp   SMARTS Beacon Port
//beacon-port-2   4426/udp   SMARTS Beacon Port
//#                          Eyal Yardeni <eyal.yardeni&smarts.com> November 2003
//drizzle         4427/tcp   Drizzle database server
//#                          Elliot Murphy <elliot.murphy&gmail.com> 09 July 2008
//#               4427/udp   Reserved
//omviserver      4428/tcp   OMV-Investigation Server-Client
//#                          Serge Vacquier <vacquier&systar.fr> 20 May 2009
//#               4428/udp   Reserved
//omviagent       4429/tcp   OMV Investigation Agent-Server
//#                          Serge Vacquier <vacquier&systar.fr> 20 May 2009
//#               4429/udp   Reserved
//rsqlserver      4430/tcp   REAL SQL Server
//rsqlserver      4430/udp   REAL SQL Server
//#                          Marco Bambini <marco&realsoftware.com> 28 August 2008
//wspipe          4431/tcp   adWISE Pipe
//#                          Heikki Ellil� <heikki.ellila&western.fi> 18 June 2009
4431,//#               4431/udp   Reserved
//#               4432-4440  Unassigned
4441,//#               4441/tcp   Reserved
//netblox         4441/udp   Netblox Protocol
//#                          Brian S. Locke <blocke&zortlabs.com> 10 July 2008
//saris           4442/tcp   Saris
//saris           4442/udp   Saris
//pharos          4443/tcp   Pharos
//pharos          4443/udp   Pharos
//#                          TeleConsult GmbH, 76275 Ettlingen, Germany
//#                          <teleconsult&t-online.de>	
//krb524          4444/tcp   KRB524
//krb524          4444/udp   KRB524
//#                          B. Clifford Neuman <bcn&isi.edu>
//# PROBLEM krb524 assigned the port, 
//# PROBLEM nv used it without an assignment
//nv-video        4444/tcp   NV Video default
//nv-video        4444/udp   NV Video default
//#                          Ron Frederick <frederick&parc.xerox.com>
//upnotifyp	4445/tcp   UPNOTIFYP
//upnotifyp 	4445/udp   UPNOTIFYP
//#			   Mark Fox <markf&uplanet.com>
//n1-fwp		4446/tcp   N1-FWP
//n1-fwp		4446/udp   N1-FWP
//n1-rmgmt	4447/tcp   N1-RMGMT
//n1-rmgmt	4447/udp   N1-RMGMT
//#			   Lori Tassin <Ramsey&network-1.com>
//asc-slmd	4448/tcp   ASC Licence Manager
//asc-slmd	4448/udp   ASC Licence Manager
//#			   Casper Stoel <cbs&ascinc.com>
//privatewire     4449/tcp   PrivateWire
//privatewire     4449/udp   PrivateWire
//#			   Uri Resnitzky <info&arx.com>
//camp		4450/tcp   Camp
//camp		4450/udp   Camp
//ctisystemmsg    4451/tcp   CTI System Msg
//ctisystemmsg    4451/udp   CTI System Msg
//ctiprogramload  4452/tcp   CTI Program Load
//ctiprogramload  4452/udp   CTI Program Load
//#			   Steven Cliff <sbcliff&controltechnology.com>
//nssalertmgr 	4453/tcp   NSS Alert Manager
//nssalertmgr	4453/udp   NSS Alert Manager
//nssagentmgr	4454/tcp   NSS Agent Manager
//nssagentmgr 	4454/udp   NSS Agent Manager
//#			   Jim Hill<jhill&symantec.com>
//prchat-user	4455/tcp   PR Chat User
//prchat-user	4455/udp   PR Chat User
//prchat-server	4456/tcp   PR Chat Server
//prchat-server	4456/udp   PR Chat Server
//prRegister	4457/tcp   PR Register
//prRegister	4457/udp   PR Register
//#			   Donny Gilor <dgilor&pop01.ny.us.ibm.net>
//mcp		4458/tcp   Matrix Configuration Protocol
4458,//mcp		4458/udp   Matrix Configuration Protocol
//#			   Tim DeBaillie <debaillie&ciholas.com> December 2006
//#		4459-4483  Unassigned
4484,//hpssmgmt        4484/tcp   hpssmgmt service
//hpssmgmt        4484/udp   hpssmgmt service
//#                          David Straw <david.straw _at_ hp.com> November 2005
//assyst-dr       4485/tcp   Assyst Data Repository Service
//#                          Albert Cester <albert.cester&assyst-intl.com> 26 August 2008
4485,//#               4485/udp   Reserved           
//#		4486-4499  Unassigned
4500,//ipsec-nat-t     4500/tcp   IPsec NAT-Traversal
//ipsec-nat-t     4500/udp   IPsec NAT-Traversal
//#                          [RFC3947]
4501,//#               4501       De-registered (08 June 2001)
//#                          IANA <iana&iana.org>
//#               4502-4534  Unassigned
4535,//ehs             4535/tcp   Event Heap Server
//ehs             4535/udp   Event Heap Server
//ehs-ssl         4536/tcp   Event Heap Server SSL 
//ehs-ssl         4536/udp   Event Heap Server SSL 
//#                          Brad Johanson <bradj&tidebreak.com> August 2005
//wssauthsvc      4537/tcp   WSS Security Service
//wssauthsvc      4537/udp   WSS Security Service
//#			   Mark Tirschwell <mark.tirschwell&wallstreetsystems.com> January 2006
//isigate		4538/tcp   isigate
//isigate		4538/udp   isigate
4538,//#			   Julien VALIENTE <j.valiente&objectif-software.com> May 2006
//#               4539-4544  Unassigned
4545,//worldscores	4545/tcp   WorldScores
//worldscores	4545/udp   WorldScores
//#                          Steve Davis <sdavis&optum-inc.com>
//sf-lm           4546/tcp   SF License Manager (Sentinel)
//sf-lm           4546/udp   SF License Manager (Sentinel)
//#                          Thomas Koell <info&sf.com>
//lanner-lm	4547/tcp   Lanner License Manager
//lanner-lm	4547/udp   Lanner License Manager
//#			   Les Enstone <lenstone&lanner.co.uk>
//synchromesh	4548/tcp   Synchromesh
//synchromesh	4548/udp   Synchromesh
//#			   Tom Hawkins <tomahawkins&gmail.com> February 2006
//aegate		4549/tcp   Aegate PMR Service
//aegate		4549/udp   Aegate PMR Service
//#			   Nick Warrington <nick.warrington&paconsulting.com> March 2006
//gds-adppiw-db	4550/tcp   Perman I Interbase Server
//gds-adppiw-db	4550/udp   Perman I Interbase Server
//#			   Leo Lesage <leo.lesage&adp.nl> April 2006
//ieee-mih        4551/tcp   MIH Services
//ieee-mih        4551/udp   MIH Services
//#                          [RFC-ietf-mipshop-mstp-solution-12.txt]
//menandmice-mon  4552/tcp   Men and Mice Monitoring
//menandmice-mon  4552/udp   Men and Mice Monitoring
4552,//#                          Carsten Strotmann <carsten.strotmann&menandmice.com> 20 May 2009
//#               4553       Unassigned
4554,//msfrs		4554/tcp   MS FRS Replication
//msfrs		4554/udp   MS FRS Replication
//#			   Kev George <Kev.George&smiths-aerospace.com> September 2006
//rsip            4555/tcp   RSIP Port
//rsip            4555/udp   RSIP Port
//#                          RFC 3103    
//dtn-bundle-tcp  4556/tcp   DTN Bundle TCP CL Protocol
//dtn-bundle-udp  4556/udp   DTN Bundle UDP CL Protocol
//#			   Michael Demmer <demmer&cs.berkeley.edu> November 2006
//#               4557/tcp   Reserved
//mtcevrunqss     4557/udp   Marathon everRun Quorum Service Server
//#                          David Schwartz <david.schwartz&marathontechnologies.com> 18 June 2009
//#               4558/tcp   Reserved 
//mtcevrunqman    4558/udp   Marathon everRun Quorum Service Manager
//#                          David Schwartz <david.schwartz&marathontechnologies.com> 18 June 2009
//hylafax         4559/tcp   HylaFAX
4559,//hylafax         4559/udp   HylaFAX
//#                          Lee Howard <iana&hylafax.org> March 2002 
//#               4560-4565  Unassigned
4566,//kwtc		4566/tcp   Kids Watch Time Control Service
//kwtc		4566/udp   Kids Watch Time Control Service
//#			   Larry Zarou <zarla01&cbsits.com> October 2006
//tram            4567/tcp   TRAM
//tram            4567/udp   TRAM
//#                          Joe Wesley <joe.wesley&east.sun.com>
//bmc-reporting   4568/tcp   BMC Reporting 
//bmc-reporting   4568/udp   BMC Reporting 
//#                          Portnoy Boxman <portnoy_boxman&bmc.com>
//iax             4569/tcp   Inter-Asterisk eXchange
//iax             4569/udp   Inter-Asterisk eXchange
4569,//#                          [RFC-guy-iax-05.txt]
//#               4570-4590  Unassigned
4591,//l3t-at-an       4591/tcp   HRPD L3T (AT-AN)
//l3t-at-an       4591/udp   HRPD L3T (AT-AN)
//#                          Avi Lior <avi&bridgewatersystems.com> 27 February 2009
//#               4592/tcp   Reserved
//hrpd-ith-at-an  4592/udp   HRPD-ITH (AT-AN)
//#                          David Ott <dott&qualcomm.com> 05 June 2008
//ipt-anri-anri	4593/tcp   IPT (ANRI-ANRI)
//ipt-anri-anri	4593/udp   IPT (ANRI-ANRI)
//ias-session	4594/tcp   IAS-Session (ANRI-ANRI)
//ias-session	4594/udp   IAS-Session (ANRI-ANRI)
//ias-paging	4595/tcp   IAS-Paging (ANRI-ANRI)
//ias-paging	4595/udp   IAS-Paging (ANRI-ANRI)
//ias-neighbor	4596/tcp   IAS-Neighbor (ANRI-ANRI)
//ias-neighbor	4596/udp   IAS-Neighbor (ANRI-ANRI)
//#			   David Ott <dott&qualcomm.com> 31 July 2007
//a21-an-1xbs	4597/tcp   A21 (AN-1xBS)
//a21-an-1xbs	4597/udp   A21 (AN-1xBS)
//#			   David Ott <dott&qualcomm.com> February 2006
//a16-an-an       4598/tcp   A16 (AN-AN)
//a16-an-an       4598/udp   A16 (AN-AN)
//#                          David Ott <dott&qualcomm.com> December 2005
//a17-an-an	4599/tcp   A17 (AN-AN)
//a17-an-an	4599/udp   A17 (AN-AN)
//#			   David Ott <dott&qualcomm.com> February 2006
//piranha1        4600/tcp   Piranha1
//piranha1        4600/udp   Piranha1
//piranha2        4601/tcp   Piranha2
//piranha2        4601/udp   Piranha2
//#                          Primark Corporation <joe.boone&primark.com>
//mtsserver       4602/tcp   EAX MTS Server
//#                          Pedro A Rodriguez <pedro.rdz&eaxtechnologies.com.mx> 06 August 2008
4602,//#               4602/udp   Reserved
//#               4603-4657  Unassigned
4658,//playsta2-app    4658/tcp   PlayStation2 App Port
//playsta2-app    4658/udp   PlayStation2 App Port
//playsta2-lob    4659/tcp   PlayStation2 Lobby Port
//playsta2-lob    4659/udp   PlayStation2 Lobby Port
//#                          Noam Rimon <noam.rimon&playstation.sony.com> December 2004
//smaclmgr        4660/tcp   smaclmgr
//smaclmgr        4660/udp   smaclmgr
//#                          Hiromi Taki <stg-togo&saint.nm.fujitsu.co.jp> 
//kar2ouche       4661/tcp   Kar2ouche Peer location service
//kar2ouche       4661/udp   Kar2ouche Peer location service
//#                          Andy Krouwel <andy&kar2ouche.com>  
//oms             4662/tcp   OrbitNet Message Service
//oms             4662/udp   OrbitNet Message Service
//#                          Roy Davies <rdavies&daq.net> August 2005
//noteit          4663/tcp   Note It! Message Service
//noteit          4663/udp   Note It! Message Service
//#			   Pedro Alpedrinha <pedro.alpedrinha&redevirtual.com> February 2006
//ems             4664/tcp   Rimage Messaging Server
//ems             4664/udp   Rimage Messaging Server
//#			   David V. Raskin <draskin&rimage.com> February 2006
//contclientms    4665/tcp   Container Client Message Service
//contclientms    4665/udp   Container Client Message Service
//#			   Bruce Thompson <brucet&actioninformationsystems.com> February 2006
//eportcomm       4666/tcp   E-Port Message Service
//eportcomm       4666/udp   E-Port Message Service
//mmacomm         4667/tcp   MMA Comm Services
//mmacomm         4667/udp   MMA Comm Services
//mmaeds          4668/tcp   MMA EDS Service
//mmaeds          4668/udp   MMA EDS Service
//#			   Robert Shaffer <bob.shaffer&micmod.com> February 2006
//eportcommdata   4669/tcp   E-Port Data Service
//eportcommdata   4669/udp   E-Port Data Service
//#			   Robert Shaffer <bob.shaffer&micmod.com> February 2006
//light		4670/tcp   Light packets transfer protocol
//light		4670/udp   Light packets transfer protocol
//#			   Adam Golovenko <golovenko&gmail.com> October 2006
//acter		4671/tcp   Bull RSF action server
//acter		4671/udp   Bull RSF action server
//#			   Christian Caudrelier <Christian.Caudrelier@%bull.net> February 2006
//rfa             4672/tcp   remote file access server
//rfa             4672/udp   remote file access server
//#			   No contact Listed
//cxws            4673/tcp   CXWS Operations
//cxws            4673/udp   CXWS Operations
//#                          Phil Abercrombie <phil.abercrombie&appiq.com> August 2005
//appiq-mgmt      4674/tcp   AppIQ Agent Management
//appiq-mgmt      4674/udp   AppIQ Agent Management
//#                          Phil Abercrombie <phil.abercrombie&appiq.com> August 2005
//dhct-status     4675/tcp   BIAP Device Status
//dhct-status     4675/udp   BIAP Device Status
//dhct-alerts     4676/tcp   BIAP Generic Alert
//dhct-alerts     4676/udp   BIAP Generic Alert
//#                          Louis Slothouber <lpslot&biap.com> August 2005
//bcs             4677/tcp   Business Continuity Servi
//bcs             4677/udp   Business Continuity Servi
//#                          Siew Sim <ssim&asempra.com> August 2005
//traversal       4678/tcp   boundary traversal
//traversal       4678/udp   boundary traversal
//#                          Kevin Lu <kevinlu&micromethod.com> August 2005
//mgesupervision  4679/tcp   MGE UPS Supervision
//mgesupervision  4679/udp   MGE UPS Supervision
//mgemanagement   4680/tcp   MGE UPS Management
//mgemanagement   4680/udp   MGE UPS Management
//#                          Lecuivre J <software.team&mgeups.com> August 2005
//parliant        4681/tcp   Parliant Telephony System
//parliant        4681/udp   Parliant Telephony System
//#                          Colin Henein <iana&cmh.parliant.com> August 2005
//finisar         4682/tcp   finisar
//finisar         4682/udp   finisar
//#                          Christina Mercier <christina.mercier&finisar.com> August 2005
//spike           4683/tcp   Spike Clipboard Service
//spike           4683/udp   Spike Clipboard Service
//#                          Scott Herscher <scott&porchdogsoft.com> August 2005
//rfid-rp1        4684/tcp   RFID Reader Protocol 1.0
//rfid-rp1        4684/udp   RFID Reader Protocol 1.0
//#                          Michael Mealling <michael&refactored-networks.com> August 2005
//autopac         4685/tcp   Autopac Protocol
//autopac         4685/udp   Autopac Protocol
//#                          Peter Hallenbeck <pete&consumertechnologiesgroup.com> August 2005
//msp-os          4686/tcp   Manina Service Protocol
//msp-os          4686/udp   Manina Service Protocol
//#                          Markus Nix <mnix&docuverse.de> August 2005
//nst             4687/tcp   Network Scanner Tool FTP 
//nst             4687/udp   Network Scanner Tool FTP 
//#                          Mala Bhat <bmala&ssdi.sharp.co.in> August 2005
//mobile-p2p      4688/tcp   Mobile P2P Service
//mobile-p2p      4688/udp   Mobile P2P Service
//#                          Previous contact: Hanz Hager <Hanz.Hager&ericsson.com> August 2005
//#                          Current contact: Hanz Hager <Hanz.Hager&comhem.se> 04 December 2008
//altovacentral   4689/tcp   Altova DatabaseCentral
//altovacentral   4689/udp   Altova DatabaseCentral
//#                          Altova <has&altova.com> August 2005
//prelude         4690/tcp   Prelude IDS message proto
//prelude         4690/udp   Prelude IDS message proto
//#                          Yoann Vandoorselaere <yoann&prelude-ids.org> August 2005
//monotone        4691/tcp   Monotone Network Protocol
//monotone        4691/udp   Monotone Network Protocol
//#                          Tomas Fasth <tomfa&debian.org> August 2005
//conspiracy      4692/tcp   Conspiracy messaging
4692,//conspiracy      4692/udp   Conspiracy messaging
//#                          Jens Edlund <edlund&speech.kth.se> August 2005
//#               4693-4699  Unassigned
4700,//netxms-agent	4700/tcp   NetXMS Agent
//netxms-agent	4700/udp   NetXMS Agent
//netxms-mgmt	4701/tcp   NetXMS Management
//netxms-mgmt	4701/udp   NetXMS Management
//netxms-sync	4702/tcp   NetXMS Server Synchronization
4702,//netxms-sync	4702/udp   NetXMS Server Synchronization
//#			   Victor Kirhenshtein <victor&opticom.lv> July 2006
//#               4703-4727  Unassigned
4728,//capmux		4728/tcp   CA Port Multiplexer
//capmux		4728/udp   CA Port Multiplexer
//#			   Nigel Groves <nigel.groves&ca.com> June 2006
//#               4729/tcp   Reserved
//gsmtap          4729/udp   GSM Interface Tap
//#                          Harald Welte <laforge&gnumonks.org> 16 January 2009
//gearman         4730/tcp   Gearman Job Queue System
//gearman         4730/udp   Gearman Job Queue System
//#                          Eric Day <eday&oddments.org> 16 January 2009
//remcap          4731/tcp   Remote Capture Protocol
//#                          Marc Donner <mail&poweraudio.de> 16 January 2009
4731,//#               4731/udp   Reserved
//#               4732-4736  Unassigned
4737,//ipdr-sp         4737/tcp   IPDR/SP
//ipdr-sp         4737/udp   IPDR/SP
//#                          Ken Sarno <kensarno&insightbb.com> August 2005
//solera-lpn	4738/tcp   SoleraTec Locator
//solera-lpn	4738/udp   SoleraTec Locator
//#                          Mark Armstrong <Mark.Armstrong&SoleraTec.com> December 2005
//ipfix           4739/tcp   IP Flow Info Export
//ipfix           4739/udp   IP Flow Info Export
//#                          Nevil Brownlee <n.brownlee&auckland.ac.nz> August 2005
//ipfix           4739/sctp  IP Flow Info Export
//#			   Nevil Brownlee <n.brownlee&auckland.ac.nz> January 2006
//ipfixs 		4740/tcp   ipfix protocol over TLS
//ipfixs 		4740/sctp  ipfix protocol over DTLS
//ipfixs 		4740/udp   ipfix protocol over DTLS
//#			   Nevil Brownlee <n.brownlee&auckland.ac.nz> October 2006
//lumimgrd	4741/tcp   Luminizer Manager
//lumimgrd	4741/udp   Luminizer Manager
//#			   George Hwa <ghwa&luminescent.com> March 2007
//sicct		4742/tcp   SICCT
//sicct-sdp	4742/udp   SICCT Service Discovery Protocol
//#			   TeleTrusT Deutschland e.V. <info&teletrust.de> April 2006
//openhpid        4743/tcp   openhpi HPI service
//openhpid        4743/udp   openhpi HPI service
//#			   Thomas Kanngieser <thomas.kanngieser&arcor.de> January 2006
//ifsp		4744/tcp   Internet File Synchronization Protocol
//ifsp		4744/udp   Internet File Synchronization Protocol
//#			   Alex White <alex&intralan.co.uk> 12 September 2007
//fmp		4745/tcp   Funambol Mobile Push
4745,//fmp		4745/udp   Funambol Mobile Push
//#			   Andrea Gazzaniga <gazzaniga&funambol.com> January 2007
//#               4746-4748  Unassigned
4749,//profilemac	4749/tcp   Profile for Mac
//profilemac	4749/udp   Profile for Mac
//#			   David Sinclair <dev&profilemac.com> May 2006
//ssad		4750/tcp   Simple Service Auto Discovery
//ssad		4750/udp   Simple Service Auto Discovery
//#                          Dr Horst Herb <horst&dorrigomedical.com> December 2005
//spocp           4751/tcp   Simple Policy Control Protocol
//spocp           4751/udp   Simple Policy Control Protocol
//#                          Roland Hedberg <roland&catalogix.se> August 2005
//snap            4752/tcp   Simple Network Audio Protocol
//snap            4752/udp   Simple Network Audio Protocol
4752,//#                          Dameon Wagner <d.wagner&freemail.absa.co.za> February 2002
//#               4753-4783  Unassigned
4784,//bfd-multi-ctl   4784/tcp   BFD Multihop Control
//bfd-multi-ctl   4784/udp   BFD Multihop Control
//#			   Dave Katz <dkatz&juniper.net>; Dave Ward <dward&cisco.com> February 2006
//#               4785/tcp   Reserved
4785,//cncp            4785/udp   Cisco Nexus Control Protocol
//#                          Joseph Swaminathan <jswamina&cisco.com> 01 April 2009
//#               4786-4799  Unassigned
4800,//iims            4800/tcp   Icona Instant Messenging System
//iims            4800/udp   Icona Instant Messenging System
//iwec            4801/tcp   Icona Web Embedded Chat
//iwec            4801/udp   Icona Web Embedded Chat
//ilss            4802/tcp   Icona License System Server
//ilss            4802/udp   Icona License System Server
//#                          Paul Stephen Borlie <paul&icona.it>
//notateit        4803/tcp   Notateit Messaging 
4803,//notateit-disc   4803/udp   Notateit Messaging Discovery
//#                           Ean Black <eanb&bladesoftware.co.uk> 08 April 2009
//#               4804-4826  Unassigned
4827,//htcp            4827/tcp   HTCP
4827,//htcp            4827/udp   HTCP
//#                          Paul Vixie <paul&vix.com>
//#               4828-4836  Unassigned
4837,//varadero-0      4837/tcp   Varadero-0
//varadero-0      4837/udp   Varadero-0 
//varadero-1      4838/tcp   Varadero-1
//varadero-1      4838/udp   Varadero-1
//varadero-2      4839/tcp   Varadero-2
//varadero-2      4839/udp   Varadero-2
//#                          Carlos Arteaga <carteaga&abacoinc.com>
//opcua-tcp	4840/tcp   OPC UA TCP Protocol
//opcua-udp	4840/udp   OPC UA TCP Protocol
//#			   Randy Armstrong <randy.armstrong&opcfoundation.org> September 2006
//quosa		4841/tcp   QUOSA Virtual Library Service
//quosa		4841/udp   QUOSA Virtual Library Service
//#			   Uri Blank <uri&quosa.com> September 2006
//gw-asv		4842/tcp   nCode ICE-flow Library AppServer
//gw-asv		4842/udp   nCode ICE-flow Library AppServer
//#			   Ross Swithenbank <iana&ncode.co.uk> September 2006
//opcua-tls	4843/tcp   OPC UA TCP Protocol over TLS/SSL
//opcua-tls	4843/udp   OPC UA TCP Protocol over TLS/SSL
//#			   Randy Armstrong <randy.armstrong&opcfoundation.org> September 2006
//gw-log		4844/tcp   nCode ICE-flow Library LogServer
//gw-log		4844/udp   nCode ICE-flow Library LogServer
//#			   Ross Swithenbank <iana&ncode.co.uk> September 2006
//wcr-remlib      4845/tcp   WordCruncher Remote Library Service
//wcr-remlib      4845/udp   WordCruncher Remote Library Service
//#                          Jason Dzubak <dzubak&byu.edu> 17 March 2008
//contamac_icm    4846/tcp   Contamac ICM Service
//contamac_icm    4846/udp   Contamac ICM Service
//#                          Abdullah Obeid <a.obeid&contamac.nl> 20 March 2008
//wfc		4847/tcp   Web Fresh Communication
//wfc		4847/udp   Web Fresh Communication
//#			   Jonathan Bastnagel <jonthebagel&gmail.com> 17 September 2007
//appserv-http    4848/tcp   App Server - Admin HTTP
//appserv-http    4848/udp   App Server - Admin HTTP
//appserv-https   4849/tcp   App Server - Admin HTTPS
//appserv-https   4849/udp   App Server - Admin HTTPS
//#                          Sreeram Duvvuru <sduv&sfbay.sun.com> April 2002
//sun-as-nodeagt  4850/tcp   Sun App Server - NA
//sun-as-nodeagt  4850/udp   Sun App Server - NA
//#                          Kedar Mhaswade <kedar.Mhaswade&sun.com> November 2004   
//derby-repli     4851/tcp   Apache Derby Replication
4851,//derby-repli     4851/udp   Apache Derby Replication
//#                          Jorgen Loland <jorgen.loland&sun.com> 27 February 2008
//#               4852-4866  Unassigned
4867,//unify-debug     4867/tcp   Unify Debugger
//unify-debug     4867/udp   Unify Debugger
//#			   Ron Kuris <rk&unify.com> May 2006
//phrelay         4868/tcp   Photon Relay
//phrelay         4868/udp   Photon Relay
//phrelaydbg      4869/tcp   Photon Relay Debug
//phrelaydbg      4869/udp   Photon Relay Debug
//#                          Michael Hunter <mphunter&qnx.com>
//cc-tracking     4870/tcp   Citcom Tracking Service
//cc-tracking     4870/udp   Citcom Tracking Service
//#                          Wolfgang Weidner <ww&citcom.de> December 2005
//wired           4871/tcp   Wired
4871,//wired           4871/udp   Wired
//#			   Axel Andersson <axel&zankasoftware.com> February 2006
//#               4872-4883  Unassigned
4884,//hivestor        4884/tcp   HiveStor Distributed File System
//hivestor        4884/udp   HiveStor Distributed File System
//#                          Nicholas Young <ntchkd&gmail.com> 10 July 2008 
//abbs            4885/tcp   ABBS
4885,//abbs            4885/udp   ABBS
//#                          Ryan Rubley <root&ark.dyn.ml.org>
//#               4886-4893  Unassigned
4894,//lyskom          4894/tcp   LysKOM Protocol A
4894,//lyskom          4894/udp   LysKOM Protocol A
//#                          Per Cederqvist <ceder&lysator.liu.se>
//#               4895-4898  Unassigned
4899,//radmin-port     4899/tcp   RAdmin Port
//radmin-port     4899/udp   RAdmin Port
//#                          Dmitri Znosko <support&radmin.com> March 2003
//hfcs		4900/tcp   Hyper File Client/Server Database Engine
//hfcs		4900/udp   Hyper File Client/Server Database Engine
//#			   Jerome AERTS <jae&pcsoft.fr> March 2006
//flr_agent       4901/tcp   FileLocator Remote Search Agent
//#                          David Vest <dave&mythicsoft.com> 19 November 2008
//#               4901/udp   Reserved
//magiccontrol    4902/tcp   magicCONROL RF and Data Interface
//#                          Andreas Spalenski <andreas.spalenski&trsystems.de> 24 November 2008
4902,//#               4902/udp   Reserved
//#               4903-4911  Unassigned
4912,//lutap           4912/tcp   Technicolor LUT Access Protocol
//#                          Markus Loeffler <markus.loeffler&thomson.net> 17 February 2009
//#               4912/udp   Reserved
//lutcp		4913/tcp   LUTher Control Protocol
//#			   Markus Loeffler <markus.loeffler&thomson.net> 03 July 2007
//bones           4914/tcp   Bones Remote Control
//bones           4914/udp   Bones Remote Control
//#                          Andreas Foedrowitz <andreas.foedrowitz&thomson.net> 18 June 2008
//frcs            4915/tcp   Fibics Remote Control Service
//#                          Ken Lagarec <klagarec&fibics.com> 17 April 2009
4915,//#               4915/udp   Reserved
//#               4916-4936  Unassigned
4937,//#               4937/tcp   Reserved
4937,//atsc-mh-ssc     4937/udp   ATSC-M/H Service Signaling Channel
//#                          Jerry Whitaker <jwhitaker&atsc.org> 27 October 2008
//#               4938-4939  Unassigned
4940,//eq-office-4940	4940/tcp   Equitrac Office
//eq-office-4940	4940/udp   Equitrac Office
//eq-office-4941	4941/tcp   Equitrac Office
//eq-office-4941	4941/udp   Equitrac Office
//eq-office-4942	4942/tcp   Equitrac Office
4942,//eq-office-4942	4942/udp   Equitrac Office
//#			   Tom Haapanen <tomh&equitrac.com> 11 July 2007
//#               4943-4948  Unassigned
4949,//munin           4949/tcp   Munin Graphing Framework
//munin           4949/udp   Munin Graphing Framework
//#                          Nicolai Langfeldt <janl&linpro.no> August 2005
//sybasesrvmon    4950/tcp   Sybase Server Monitor
//sybasesrvmon    4950/udp   Sybase Server Monitor
//#                          Chris Irie <irie&sybase.com> 26 March 2008
//pwgwims         4951/tcp   PWG WIMS
//pwgwims         4951/udp   PWG WIMS
//#                          Ira McDonald <imcdonald&sharplabs.com> December 2005
//sagxtsds        4952/tcp   SAG Directory Server
4952,//sagxtsds        4952/udp   SAG Directory Server
//#			   Michael Chirila <Michael.Chirila&softwareag.com> January 2006
//#               4953-4968  Unassigned
4969,//ccss-qmm        4969/tcp   CCSS QMessageMonitor
//ccss-qmm        4969/udp   CCSS QMessageMonitor
//ccss-qsm        4970/tcp   CCSS QSystemMonitor
4970,//ccss-qsm        4970/udp   CCSS QSystemMonitor
//#			   David Young <david.young&ccsseurope.co.uk> January 2006
//#               4971-4982  Unassigned
//#               4983       Unassigned (Removed on 2005-12-22)
//#               4984-4985  Unassigned
4986,//mrip		4986/tcp   Model Railway Interface Program
//mrip		4986/udp   Model Railway Interface Program
//#			   Howard Amos <amos&ccww.co.uk> April 2006
//smar-se-port1   4987/tcp   SMAR Ethernet Port 1
//smar-se-port1   4987/udp   SMAR Ethernet Port 1
//smar-se-port2   4988/tcp   SMAR Ethernet Port 2
//smar-se-port2   4988/udp   SMAR Ethernet Port 2
//#                          Delcio Prizon <dprizon&smar.com.br>
//parallel        4989/tcp   Parallel for GAUSS (tm)
//parallel        4989/udp   Parallel for GAUSS (tm)
//#                          Matthew Ford <Matthew.Ford&forward.com.au> March 2003
//busycal         4990/tcp   BusySync Calendar Synch. Protocol
//busycal         4990/udp   BusySync Calendar Synch. Protocol
//#                          David Riggle <dave&busymac.com> 07 January 2008
//vrt             4991/tcp   VITA Radio Transport
4991,//vrt             4991/udp   VITA Radio Transport
//#                          Sam Bretheim <info&opensigint.org> 08 January 2009
//#               4992-4998  Unassigned
4999,//hfcs-manager    4999/tcp   Hyper File Client/Server Database Engine Manager
//hfcs-manager    4999/udp   Hyper File Client/Server Database Engine Manager
//#			   Jerome AERTS <jae&pcsoft.fr> March 2006
//commplex-main	5000/tcp
//commplex-main	5000/udp
//commplex-link	5001/tcp
//commplex-link	5001/udp
//rfe             5002/tcp   radio free ethernet
//rfe             5002/udp   radio free ethernet
//fmpro-internal  5003/tcp   FileMaker, Inc. - Proprietary transport
//fmpro-internal  5003/udp   FileMaker, Inc. - Proprietary name binding
//#                          Clay Maeckel <clay_maeckel&filemaker.com>
//avt-profile-1   5004/tcp   RTP media data [RFC 3551, RFC 4571]
//avt-profile-1   5004/udp   RTP media data [RFC 3551]
//avt-profile-1   5004/dccp  RTP media data [RFC 3551, RFC-ietf-dccp-rtp-07.txt]
//avt-profile-2   5005/tcp   RTP control protocol [RFC 3551, RFC 4571]
//avt-profile-2   5005/udp   RTP control protocol [RFC 3551]
//avt-profile-2   5005/dccp  RTP control protocol [RFC 3551, RFC-ietf-dccp-rtp-07.txt]
//wsm-server      5006/tcp   wsm server
//wsm-server      5006/udp   wsm server
//wsm-server-ssl  5007/tcp   wsm server ssl
//wsm-server-ssl  5007/udp   wsm server ssl
//#                          Adam Berk <aberk&empirix.com>
//synapsis-edge   5008/tcp   Synapsis EDGE
//synapsis-edge   5008/udp   Synapsis EDGE
//#                          Paul Schilling <PaulS&Synapsis.com>
//winfs           5009/tcp   Microsoft Windows Filesystem
//winfs           5009/udp   Microsoft Windows Filesystem
//#			   Simon Skaria <simonsk&microsoft.com> January 2006
//telelpathstart  5010/tcp   TelepathStart
//telelpathstart  5010/udp   TelepathStart
//telelpathattack 5011/tcp   TelepathAttack
//telelpathattack 5011/udp   TelepathAttack
//#                          Helmuth Breitenfellner <hbreitenf&vnet.imb.com>
//nsp             5012/tcp   NetOnTap Service
//nsp             5012/udp   NetOnTap Service
//#			   Kim Hancock <registry&dragondex.com> 24 October 2007
//fmpro-v6	5013/tcp   FileMaker, Inc. - Proprietary transport 
5013,//fmpro-v6	5013/udp   FileMaker, Inc. - Proprietary transport 
//#			   Alex Chen <alex_chen&filemaker.com> 01 August 2007
//#               5014-5019  Unassigned
5020,//zenginkyo-1     5020/tcp   zenginkyo-1
//zenginkyo-1     5020/udp   zenginkyo-1
//zenginkyo-2     5021/tcp   zenginkyo-2
//zenginkyo-2     5021/udp   zenginkyo-2
//#                          Masashi Suzaki <susakim&noa.nttdata.jp>
//mice            5022/tcp   mice server
//mice            5022/udp   mice server
//#                          Alan Clifford <alan&clifford.ac>
//htuilsrv        5023/tcp   Htuil Server for PLD2
//htuilsrv        5023/udp   Htuil Server for PLD2
//#                          Dennis Reinhardt <DennisR&dair.com>
//scpi-telnet     5024/tcp   SCPI-TELNET
//scpi-telnet     5024/udp   SCPI-TELNET
//scpi-raw        5025/tcp   SCPI-RAW
//scpi-raw        5025/udp   SCPI-RAW
//#                          Ryan Columbus <IANA_Contact&Agilent.com> October 2002
//strexec-d       5026/tcp   Storix I/O daemon (data)
//strexec-d       5026/udp   Storix I/O daemon (data)
//strexec-s       5027/tcp   Storix I/O daemon (stat)
5027,//strexec-s       5027/udp   Storix I/O daemon (stat)
//#                          Anthony Johnson <stxadmin&storix.com> August 2005
//#               5028-5029  Unassigned
5030,//surfpass	5030/tcp   SurfPass
5030,//surfpass	5030/udp   SurfPass
//#			   Olivier Guezenec <olivier.guezenec&cogilab.com> December 2006
//#               5031-5041  Unassigned
5042,//asnaacceler8db  5042/tcp   asnaacceler8db
//asnaacceler8db  5042/udp   asnaacceler8db
//#                          Walter Goodwin <wpgoodwin&asna.com>
//swxadmin        5043/tcp   ShopWorX Administration
//swxadmin        5043/udp   ShopWorX Administration
//#                          Don W. Fitzpatrick <dwf&InterNetworXsystems.com> August 2005
//lxi-evntsvc     5044/tcp   LXI Event Service
5044,//lxi-evntsvc     5044/udp   LXI Event Service
//#                          Nick Barendt <nbarendt&vxitech.com> August 2005
//#               5045-5048  Unassigned 
5049,//ivocalize	5049/tcp   iVocalize Web Conference
//ivocalize	5049/udp   iVocalize Web Conference
//#			   Bryan Vergato <iana&ivocalize.com> May 2006
//mmcc            5050/tcp   multimedia conference control tool
//mmcc            5050/udp   multimedia conference control tool
//#                          Steve Casner <Casner&isi.edu>
//ita-agent       5051/tcp   ITA Agent
//ita-agent       5051/udp   ITA Agent
//ita-manager     5052/tcp   ITA Manager
//ita-manager     5052/udp   ITA Manager
//#                          Don Merrell <donmer&axent.com>
//rlm             5053/tcp   RLM License Server
//#                          Matt Christiano <matt&reprisesoftware.com> 28 July 2008 
//#               5053/udp   Reserved
//rlm-admin       5054/tcp   RLM administrative interface
//#                          Matt Christiano <matt&reprisesoftware.com> 28 July 2008 
//#               5054/udp   Reserved
//unot            5055/tcp   UNOT
//unot            5055/udp   UNOT
//#                          Gordon Mohr <gmohr&cmgisolutions.com>
//intecom-ps1     5056/tcp   Intecom Pointspan 1
//intecom-ps1     5056/udp   Intecom Pointspan 1
//intecom-ps2     5057/tcp   Intecom Pointspan 2
5057,//intecom-ps2     5057/udp   Intecom Pointspan 2
//#                          David Meermans <david.meermans&aastra.com>
//#               5058       Unassigned
5059,//sds		5059/tcp   SIP Directory Services
//sds		5059/udp   SIP Directory Services
//#			   Arthur Wilton <art&awilton.com> March 2006
//sip             5060/tcp   SIP
//sip             5060/udp   SIP
//sip-tls         5061/tcp   SIP-TLS
5061,//sip-tls         5061/udp   SIP-TLS
//#                          Henning Schulzrinne <hgs&cs.columbia.edu>
//#               5062-5063  Unassigned
5064,//ca-1            5064/tcp   Channel Access 1
//ca-1            5064/udp   Channel Access 1
//ca-2            5065/tcp   Channel Access 2
//ca-2            5065/udp   Channel Access 2
//#                          Jeffrey Hill <johill&lanl.gov> August 2002
//stanag-5066     5066/tcp   STANAG-5066-SUBNET-INTF
//stanag-5066     5066/udp   STANAG-5066-SUBNET-INTF
//#                          Donald G. Kallgren
//#                          <Donald.Kallgren&nc3a.nato.int>      
//authentx        5067/tcp   Authentx Service
//authentx        5067/udp   Authentx Service
//#                          Alberto Fernandez <af&xtec.com> January 2006
//bitforestsrv    5068/tcp   Bitforest Data Service
//#                          Ville-Pekka Vahteala <ville-pekka.vahteala&bitcomp.fi> 05 June 2008
//#               5068/udp   Reserved
//i-net-2000-npr  5069/tcp   I/Net 2000-NPR
//i-net-2000-npr  5069/udp   I/Net 2000-NPR
//#                          Chris Megede <chris.megede&tac.com>
//vtsas		5070/tcp   VersaTrans Server Agent Service
//vtsas		5070/udp   VersaTrans Server Agent Service
//#			   Christopher Miller <Chris.Miller&versatrans.com> February 2006
//powerschool     5071/tcp   PowerSchool
//powerschool     5071/udp   PowerSchool
//#                          Greg Porter <gporter&powerschool.com>
//ayiya           5072/tcp   Anything In Anything
//ayiya           5072/udp   Anything In Anything
//#                          Jeroen Massar <jeroen&unfix.org> August 2005
//tag-pm          5073/tcp   Advantage Group Port Mgr
//tag-pm          5073/udp   Advantage Group Port Mgr
//#                          James Goddard <jamesg&taglim.com> August 2005
//alesquery       5074/tcp   ALES Query
5074,//alesquery       5074/udp   ALES Query
//#                          Tim Maloney <tim.maloney&allianceconsultingllc.com> August 2005
//#               5075-5078  Unassigned
5079,//#               5079/tcp   Reserved
//cp-spxrpts      5079/udp   Cambridge Pixel SPx Reports
//#                          Richard Warren <richard&cambridgepixel.com> 17 September 2008
//onscreen        5080/tcp   OnScreen Data Collection Service 
//onscreen        5080/udp   OnScreen Data Collection Service 
//#                          Christopher Miller <chris.miller&versatrans.com> 14 January 2008
//sdl-ets         5081/tcp   SDL - Ent Trans Server
//sdl-ets         5081/udp   SDL - Ent Trans Server
//#                          Marc Morin <mmorin&sdlintl.com> April 2002
//qcp             5082/tcp   Qpur Communication Protocol
//qcp             5082/udp   Qpur Communication Protocol
//qfp             5083/tcp   Qpur File Protocol
//qfp             5083/udp   Qpur File Protocol
//#                          Joachim Kluemper <ports&raikosoft.com> 19 March 2008
//llrp		5084/tcp   EPCglobal Low-Level Reader Protocol
//llrp		5084/udp   EPCglobal Low-Level Reader Protocol
//encrypted-llrp	5085/tcp   EPCglobal Encrypted LLRP
5085,//encrypted-llrp	5085/udp   EPCglobal Encrypted LLRP
//#			   Margaret Wasserman <margaret&thingmagic.com> November 2006
//#               5086-5089  Unassigned
5090,//car             5090/sctp  Candidate AR
//cxtp            5091/sctp  Context Transfer Protocol 
//#                          RFC 4065 - July 2005
//#               5092/tcp   Reserved
//magpie          5092/udp   Magpie Binary
//#                          Phil Maker <pjm&gnu.org> 18 June 2008
//sentinel-lm     5093/tcp   Sentinel LM
5093,//sentinel-lm     5093/udp   Sentinel LM
//#                          Derick Snyder <dsnyder&rainbow.com>
//#               5094-5098  Unassigned 
5099,//sentlm-srv2srv  5099/tcp   SentLM Srv2Srv
//sentlm-srv2srv  5099/udp   SentLM Srv2Srv
//#                          Derick Snyder <dsnyder&rainbow.com>
//socalia         5100/tcp   Socalia service mux
//socalia         5100/udp   Socalia service mux
//#                          Alberto Raydan <raydan_a&socalia.com> August 2005
//talarian-tcp    5101/tcp   Talarian_TCP
//talarian-udp    5101/udp   Talarian_UDP
//#                          Leo Martins <leo&talarian.com>
//oms-nonsecure   5102/tcp   Oracle OMS non-secure
5102,//oms-nonsecure   5102/udp   Oracle OMS non-secure
//#                          Todd Guay <todd.guay&oracle.com> August 2005
//#               5103-5110  Unassigned
5111,//taep-as-svc     5111/tcp   TAEP AS service
//taep-as-svc     5111/udp   TAEP AS service
//#                          Liu Changchun <blzhang&infospark.cn> 05 November 2008
//pm-cmdsvr       5112/tcp   PeerMe Msg Cmd Service
5112,//pm-cmdsvr       5112/udp   PeerMe Msg Cmd Service
//#                          Marcos Della <mdella&peerme.com> August 2005
//#               5113       Unassigned
5114,//ev-services     5114/tcp   Enterprise Vault Services
//#                          Richard Jones <richard_jones1&symantec.com> 26 May 2009
//#               5114/udp   Reserved
//autobuild       5115/tcp   Symantec Autobuild Service
//#                          David Warden <david_warden&symantec.com> 17 November 2008
//#               5115/udp   Reserved
//#               5116/tcp   Reserved
5116,//emb-proj-cmd    5116/udp   EPSON Projecter Image Transfer
//#                          SEIKO EPSON <ProjectorSoft&exc.epson.co.jp> 17 November 2008
//#               5117-5132  Unassigned
5133,//nbt-pc          5133/tcp   Policy Commander
5133,//nbt-pc          5133/udp   Policy Commander
//#                          Emily Harris <eharris&newboundary.com> November 2004
//#               5134-5136  Unassigned
5137,//ctsd            5137/tcp   MyCTS server port
5137,//ctsd            5137/udp   MyCTS server port
//#                          Jilles Oldenbeuving <ojilles&hotmail.com> June 2002
//#               5138-5144  Unassigned
5145,//rmonitor_secure	5145/tcp   RMONITOR SECURE
5145,//rmonitor_secure	5145/udp   RMONITOR SECURE
//#                          Kory Hamzeh <kory&ascend.com> 
//#               5146-5149  Unassigned
5150,//atmp            5150/tcp   Ascend Tunnel Management Protocol
//atmp            5150/udp   Ascend Tunnel Management Protocol
//#                          Kory Hamzeh <kory&ascend.com>
//esri_sde        5151/tcp   ESRI SDE Instance
//esri_sde        5151/udp   ESRI SDE Remote Start
//sde-discovery   5152/tcp   ESRI SDE Instance Discovery
5152,//sde-discovery   5152/udp   ESRI SDE Instance Discovery
//#                          Peter Aronson <paronson&esri.com> 
//#               5153       Unassigned
5154,//bzflag          5154/tcp   BZFlag game server
//bzflag          5154/udp   BZFlag game server
//#                          Tim Riker <tim&rikers.org> July 2003 
//asctrl-agent    5155/tcp   Oracle asControl Agent
5155,//asctrl-agent    5155/udp   Oracle asControl Agent
//#                          Todd Guay <todd.guay&oracle.com> August 2005
//#               5156-5160  Unassigned
//snmpssh         5161/tcp   SNMP over SSH Transport Model
//#               5161/udp   Reserved
//#                          [RFC-ietf-isms-secshell-18.txt]
5162,//snmpssh-trap    5162/tcp   SNMP Notification over SSH Transport Model
//#               5162/udp   Reserved
//#                          [RFC-ietf-isms-secshell-18.txt]
//#               5163-5164  Unassigned
5165,//ife_icorp       5165/tcp   ife_1corp
//ife_icorp       5165/udp   ife_1corp
//#                          Paul Annala <paa&bull.se>
//winpcs          5166/tcp   WinPCS Service Connection
//winpcs          5166/udp   WinPCS Service Connection
//#                          Complan Network AS <knut&winpcs.com> February 2006
//scte104         5167/tcp   SCTE104 Connection
//scte104         5167/udp   SCTE104 Connection
//scte30          5168/tcp   SCTE30 Connection
5168,//scte30          5168/udp   SCTE30 Connection
//#                          Thomas Russell <trussell&scte.org> May 2005
//#               5169-5189  Unassigned
5190,//aol             5190/tcp   America-Online
//aol             5190/udp   America-Online
//#                          Marty Lyons <marty&aol.com>
//aol-1           5191/tcp   AmericaOnline1
//aol-1           5191/udp   AmericaOnline1
//aol-2           5192/tcp   AmericaOnline2
//aol-2           5192/udp   AmericaOnline2
//aol-3           5193/tcp   AmericaOnline3
5193,//aol-3           5193/udp   AmericaOnline3
//#                          Bruce Mackey <BAMackey&aol.com>
//#               5194-5199  Unassigned
5200,//targus-getdata  5200/tcp   TARGUS GetData 
//targus-getdata  5200/udp   TARGUS GetData  
//targus-getdata1 5201/tcp   TARGUS GetData 1
//targus-getdata1 5201/udp   TARGUS GetData 1
//targus-getdata2 5202/tcp   TARGUS GetData 2
//targus-getdata2 5202/udp   TARGUS GetData 2
//targus-getdata3 5203/tcp   TARGUS GetData 3 
5203,//targus-getdata3 5203/udp   TARGUS GetData 3
//#                          John Keaveney <johnkeaveney&targusinfo.com>
//#               5204-5221  Unassigned
5222,//xmpp-client     5222/tcp   XMPP Client Connection
//xmpp-client     5222/udp   XMPP Client Connection
//#                          [RFC3920]
//hpvirtgrp	5223/tcp   HP Virtual Machine Group Management
//hpvirtgrp	5223/udp   HP Virtual Machine Group Management
//hpvirtctrl	5224/tcp   HP Virtual Machine Console Operations
//hpvirtctrl	5224/udp   HP Virtual Machine Console Operations
//#			   John Williams <John.H.Williams&hp.com> June 2007
//hp-server       5225/tcp   HP Server
//hp-server       5225/udp   HP Server
//hp-status       5226/tcp   HP Status
//hp-status       5226/udp   HP Status
//#                          Brett Green <Brett_Green&HP.Com>
//perfd		5227/tcp   HP System Performance Metric Service
//perfd		5227/udp   HP System Performance Metric Service
//#			   Previous contact: Phyllis Gallgher <phyllis.gallagher&hp.com> April 2007
//#                          Current contact: Chris Bertin <chris.bertin&hp.com> 19 May 2009
//hpvroom         5228/tcp   HP Virtual Room Service
//#                          Scott Levin <scott.levin&hp.com> 19 March 2009
5228,//#               5228/udp   Reserved
//#               5229-5233  Unassigned
5234,//eenet           5234/tcp   EEnet communications
//eenet           5234/udp   EEnet communications
//#                          Helmut Giritzer <helmut.giritzer&epluse.at> November 2005
//galaxy-network  5235/tcp   Galaxy Network Service
//galaxy-network  5235/udp   Galaxy Network Service
//#			   Michael Andre <mandre&gatewayticketing.com> 04 October 2007
//padl2sim        5236/tcp
//padl2sim        5236/udp
//#
//mnet-discovery	5237/tcp   m-net discovery
5237,//mnet-discovery	5237/udp   m-net discovery
//#			   Andy Crick <acrick&haascnc.com> 13 November 2007
//#               5238-5244  Unassigned
5245,//downtools       5245/tcp   DownTools Control Protocol
//downtools-disc  5245/udp   DownTools Discovery Protocol
//#                          Jarrod Sayers <jarrod&downtools.com.au> 07 April 2009
//#               5246/tcp   Reserved
//capwap-control  5246/udp   CAPWAP Control Protocol
//#                          [RFC5415]
//#               5247/tcp   Reserved
//capwap-data     5247/udp   CAPWAP Data Protocol
//#                          [RFC5415]
//caacws          5248/tcp   CA Access Control Web Service
//caacws          5248/udp   CA Access Control Web Service
//#                          Gabriel Kalmar <kalga01&ca.com> 06 March 2008
//caaclang2       5249/tcp   CA AC Lang Service
//caaclang2       5249/udp   CA AC Lang Service
//#                          Gabriel Kalmar <kalga01&ca.com> 19 February 2008
//soagateway	5250/tcp   soaGateway
//soagateway	5250/udp   soaGateway
//#                          Greg Bodine <gregory.bodine&ca.com> February 2002
//caevms          5251/tcp   CA eTrust VM Service
//caevms          5251/udp   CA eTrust VM Service
//#                          Kevin Bond <kevin.bond&ca.com> November 2004
//movaz-ssc       5252/tcp   Movaz SSC
5252,//movaz-ssc       5252/udp   Movaz SSC
//#                          Lou Berger <lberger&movaz.com> November 2004
//#               5253-5263  Unassigned
5264,//3com-njack-1    5264/tcp   3Com Network Jack Port 1 
//3com-njack-1    5264/udp   3Com Network Jack Port 1
//3com-njack-2    5265/tcp   3Com Network Jack Port 2
5265,//3com-njack-2    5265/udp   3Com Network Jack Port 2
//#                          Abhay Rajaram <Abhay_Rajaram&3Com.com> March 2003
//#               5266-5268  Unassigned
5269,//xmpp-server     5269/tcp   XMPP Server Connection
//xmpp-server     5269/udp   XMPP Server Connection
//#                          [RFC3920] 
//xmp             5270/tcp   Cartographer XMP
5270,//xmp             5270/udp   Cartographer XMP
//#                          Bobby Krupczak <rdk&krupczak.org> 03 April 2008 
//#               5271       Unassigned
5272,//pk              5272/tcp   PK
5272,//pk              5272/udp   PK
//#                          Patrick Kara <Patrick&EBA.NET>
//#               5273-5281  Unassigned
5282,//transmit-port   5282/tcp   Marimba Transmitter Port
5282,//transmit-port   5282/udp   Marimba Transmitter Port
//#                          Johan Eriksson <johan&marimba.com> April 2002
//#               5283-5297  Unassigned
5282,//presence        5298/tcp   XMPP Link-Local Messaging
//presence        5298/udp   XMPP Link-Local Messaging
//#                          Eric St. Onge <stonge&apple.com> 14 January 2008
//nlg-data        5299/tcp   NLG Data Service
//nlg-data        5299/udp   NLG Data Service
//#                          Andy Shellam <andy&networkmail.eu> 19 February 2008
//hacl-hb		5300/tcp   HA cluster heartbeat
//hacl-hb		5300/udp   HA cluster heartbeat
//hacl-gs		5301/tcp   HA cluster general services
//hacl-gs		5301/udp   HA cluster general services
//hacl-cfg	5302/tcp   HA cluster configuration
//hacl-cfg	5302/udp   HA cluster configuration
//hacl-probe	5303/tcp   HA cluster probing
//hacl-probe	5303/udp   HA cluster probing
//hacl-local      5304/tcp   HA Cluster Commands
//hacl-local      5304/udp   HA Cluster Commands
//hacl-test       5305/tcp   HA Cluster Test
//hacl-test       5305/udp   HA Cluster Test
//#                          Eric Soderberg <seric&hposl102.cup.hp>
//#                          Edward Yim <eyim&hpmfas4.cup.hp.com>
//sun-mc-grp	5306/tcp   Sun MC Group
//sun-mc-grp	5306/udp   Sun MC Group
//#                          Michael DeMoney <demoney&eng.sun.com>
//sco-aip		5307/tcp   SCO AIP
//sco-aip		5307/udp   SCO AIP
//#			   Barrie Cooper <barrie&sco.com>
//cfengine 	5308/tcp   CFengine
//cfengine	5308/udp   CFengine
//#			   Mark Burgess <mark.burgess&iu.hioslo.no>
//jprinter	5309/tcp   J Printer
//jprinter  	5309/udp   J Printer
//#			   Ken Blackwell <kenb&bristol.com>
//outlaws         5310/tcp   Outlaws
5310,//outlaws         5310/udp   Outlaws
//#                          Richard Fife <richardf&lucasarts.com>
//#               5311       Unassigned (removed 7 May 2004)
5312,//permabit-cs     5312/tcp   Permabit Client-Server
//permabit-cs     5312/udp   Permabit Client-Server
//#                          Jered Floyd <jered&permabit.com>, June 2004
//rrdp            5313/tcp   Real-time & Reliable Data
//rrdp            5313/udp   Real-time & Reliable Data
//#                          Ted Hoshi <tetsuo.hoshi&jp.yokogawa.com>, June 2004
//opalis-rbt-ipc  5314/tcp   opalis-rbt-ipc
//opalis-rbt-ipc  5314/udp   opalis-rbt-ipc
//#                          Laurent Domenech <ldomenech&opalis.com>
//hacl-poll       5315/tcp   HA Cluster UDP Polling
//hacl-poll       5315/udp   HA Cluster UDP Polling
//#                          Hoa Nguyen <hoan&cup.hp.com>
//hpdevms		5316/tcp   HP Device Monitor Service
5316,//hpdevms		5316/udp   HP Device Monitor Service
//#			   Masato Maeda <Masato.Maeda&hp.com> 04 October 2007
//#               5317-5319  Unassigned
5320,//bsfserver-zn    5320/tcp   Webservices-based Zn interface of BSF
//#                          Bert Paul <bert.paul&apertio.com> 01 May 2008
//#               5320/udp   Reserved
5321,//bsfsvr-zn-ssl   5321/tcp   Webservices-based Zn interface of BSF over SSL
//#                          Bert Paul <bert.paul&apertio.com> 03 July 2008
//#               5321/udp   Reserved
//#               5322-5342  Unassigned
5343,//kfserver	5343/tcp   Sculptor Database Server
//kfserver	5343/udp   Sculptor Database Server
//#                          Keith Ashman <sciana&sculptor.co.uk> December 2005
//xkotodrcp	5344/tcp   xkoto DRCP 
5344,//xkotodrcp	5344/udp   xkoto DRCP 
//#			   Jeff Heisz <jeff.heisz&xkoto.com> February 2006
//#               5345-5348  Unassigned
5349,//stuns           5349/tcp   STUN over TLS
//stuns           5349/udp   Reserved for a future enhancement of STUN
//#                          [RFC5389]
//nat-pmp-status	5350/tcp   NAT-PMP Status Announcements
//nat-pmp-status	5350/udp   NAT-PMP Status Announcements
//#			   Stuart Cheshire <cheshire&apple.com> 03 December 2007
//nat-pmp         5351/tcp   NAT Port Mapping Protocol
//nat-pmp         5351/udp   NAT Port Mapping Protocol
//#                          Joshua Graessley <jgraessley&apple.com> December 2004
//dns-llq         5352/tcp   DNS Long-Lived Queries
//dns-llq         5352/udp   DNS Long-Lived Queries
//#                          Kiren Sekar <kiren&apple.com> August 2005
//mdns            5353/tcp   Multicast DNS
//mdns            5353/udp   Multicast DNS
//#                          Stuart Cheshire <cheshire&multicastdns.org>
//mdnsresponder   5354/tcp   Multicast DNS Responder IPC 
//mdnsresponder   5354/udp   Multicast DNS Responder IPC
//#                          Stuart Cheshire <mdnsresponder-ipc&multicastdns.org> June 2004
//llmnr           5355/tcp   LLMNR
//llmnr           5355/udp   LLMNR
//#                          Bernard Aboba <bernarda&microsoft.com> June 2004
//ms-smlbiz       5356/tcp   Microsoft Small Business
//ms-smlbiz       5356/udp   Microsoft Small Business
//#                          Gopikrishna Sandra <v-gosand&microsoft.com> February 2005
//wsdapi          5357/tcp   Web Services for Devices
//wsdapi          5357/udp   Web Services for Devices
//wsdapi-s        5358/tcp   WS for Devices Secured
//wsdapi-s        5358/udp   WS for Devices Secured
//#                          Henry Rawas <henryr&microsoft.com> August 2005
//ms-alerter	5359/tcp   Microsoft Alerter
//ms-alerter	5359/udp   Microsoft Alerter
//#			   Marc McClure <marcmcc&microsoft.com> 07 August 2007
//ms-sideshow     5360/tcp   Protocol for Windows SideShow
//ms-sideshow     5360/udp   Protocol for Windows SideShow
//ms-s-sideshow   5361/tcp   Secure Protocol for Windows SideShow
//ms-s-sideshow   5361/udp   Secure Protocol for Windows SideShow
//#                          Dan Polivy <dpolivy&microsoft.com> 12 March 2008
//serverwsd2      5362/tcp   Microsoft Windows Server WSD2 Service
//serverwsd2      5362/udp   Microsoft Windows Server WSD2 Service
//#                          Erhan Soyer-Osman <erhanso&microsoft.com> 26 March 2008
//net-projection  5363/tcp   Windows Network Projection
5363,//net-projection  5363/udp   Windows Network Projection
//#                          Rob Williams <rob.williams&microsoft.com> 17 February 2009
//#     	        5364-5396  Unassigned
5397,//stresstester    5397/tcp   StressTester(tm) Injector
//stresstester    5397/udp   StressTester(tm) Injector
//#                          Graham Parsons <graham.parsons&reflective.com> August 2005
//elektron-admin  5398/tcp   Elektron Administration
//elektron-admin  5398/udp   Elektron Administration
//#                          Chris Hawk <chris&corriente.net> August 2005
//securitychase   5399/tcp   SecurityChase
//securitychase   5399/udp   SecurityChase
//#                          Daisuke Shinomiya <shinomiya.daisu&jp.fujitsu.com> August 2005
//excerpt		5400/tcp   Excerpt Search
//excerpt		5400/udp   Excerpt Search
//excerpts	5401/tcp   Excerpt Search Secure
//excerpts  	5401/udp   Excerpt Search Secure
//#		           John Hinsdale <hin&alma.com>
//mftp		5402/tcp   OmniCast MFTP
//mftp		5402/udp   OmniCast MFTP
//#			   Steve Bannister <sbannister&stratacache.com> 
//hpoms-ci-lstn   5403/tcp   HPOMS-CI-LSTN
//hpoms-ci-lstn	5403/udp   HPOMS-CI-LSTN
//hpoms-dps-lstn  5404/tcp   HPOMS-DPS-LSTN
//hpoms-dps-lstn  5404/udp   HPOMS-DPS-LSTN
//#			               Harold Froehling <hrf&cup.hp.com>
//netsupport	5405/tcp   NetSupport
//netsupport	5405/udp   NetSupport
//#		           Paul Sanders <pe77&dial.pipex.com>
//systemics-sox	5406/tcp   Systemics Sox
//systemics-sox	5406/udp   Systemics Sox
//#		           Gary Howland <gary&systemics.com>
//foresyte-clear  5407/tcp   Foresyte-Clear
//foresyte-clear  5407/udp   Foresyte-Clear
//foresyte-sec    5408/tcp   Foresyte-Sec
//foresyte-sec	5408/udp   Foresyte-Sec
//#			   Jorge Aldana <operator&foresyte.com>
//salient-dtasrv  5409/tcp   Salient Data Server
//salient-dtasrv  5409/udp   Salient Data Server
//salient-usrmgr  5410/tcp   Salient User Manager
//salient-usrmgr  5410/udp   Salient User Manager
//#                          Richard Farnham <rfarnham&salient.com> 
//actnet		5411/tcp   ActNet
//actnet		5411/udp   ActNet
//#		           Simon Robillard <RobillardS&actresearch.com>
//continuus	5412/tcp   Continuus
//continuus   	5412/udp   Continuus
//#		           Steven Holtsberg <steveh&continuus.com>
//wwiotalk	5413/tcp   WWIOTALK
//wwiotalk	5413/udp   WWIOTALK
//#		           Roger Knobbe <RogerK&Wonderware.COM>
//statusd		5414/tcp   StatusD
//statusd		5414/udp   StatusD
//#		           Stephen Misel <steve&satelnet.org>
//ns-server  	5415/tcp   NS Server
//ns-server	5415/udp   NS Server
//#		           Jeffrey Chiao <chiaoj&netsoft.com>
//sns-gateway	5416/tcp   SNS Gateway
//sns-gateway	5416/udp   SNS Gateway
//sns-agent	5417/tcp   SNS Agent
//sns-agent  	5417/udp   SNS Agent
//#	    	           Mary Holstage <holstege&firstfloor.com>
//mcntp		5418/tcp   MCNTP
//mcntp		5418/udp   MCNTP
//#		           Heiko Rupp <hwr&pilhuhn.de>
//dj-ice		5419/tcp   DJ-ICE
//dj-ice		5419/udp   DJ-ICE
//#		           Don Tyson <don.tyson&cor.dowjones.com>
//cylink-c	5420/tcp   Cylink-C
//cylink-c	5420/udp   Cylink-C
//#		           John Jobe <jjobe&cylink.com>
//netsupport2	5421/tcp   Net Support 2
//netsupport2	5421/udp   Net Support 2
//#		           Paul Sanders <p.sanders&dial.pipex.com>
//salient-mux     5422/tcp   Salient MUX
//salient-mux     5422/udp   Salient MUX
//#                          Richard Farnham <rfarnham&salient.com>
//virtualuser     5423/tcp   VIRTUALUSER
//virtualuser     5423/udp   VIRTUALUSER
//#                          Chad Williams <chad&apple.com>
//beyond-remote   5424/tcp   Beyond Remote
//beyond-remote   5424/udp   Beyond Remote
//#                          Michael Berg <mike&dataapples.com> November 2004
//br-channel      5425/tcp   Beyond Remote Command Channel
//br-channel      5425/udp   Beyond Remote Command Channel
//#                          Michael Berg <mike&dataapples.com> August 2005
//devbasic        5426/tcp   DEVBASIC
//devbasic        5426/udp   DEVBASIC
//#                          Curtis Smith <curtis.smith&vsin.com>
//sco-peer-tta    5427/tcp   SCO-PEER-TTA
//sco-peer-tta    5427/udp   SCO-PEER-TTA
//#                          Andrew Shire <sndrewsh&sco.com>
//telaconsole     5428/tcp   TELACONSOLE
//telaconsole     5428/udp   TELACONSOLE
//#                          Joseph M. Newcomer <newcomer&flounder.com>
//base            5429/tcp   Billing and Accounting System Exchange
//base            5429/udp   Billing and Accounting System Exchange
//#                          Odo Maletzki <Odo.Maletzki&ioag.de>
//radec-corp      5430/tcp   RADEC CORP
//radec-corp      5430/udp   RADEC CORP
//#                          David Chell <david&softlife.co.nz>
//park-agent      5431/tcp   PARK AGENT
//park-agent      5431/udp   PARK AGENT
//#                          John Clifford <John.Clifford&veritas.com>
//postgresql      5432/tcp   PostgreSQL Database
//postgresql      5432/udp   PostgreSQL Database
//#                          Tom Lane <tgl&sss.pgh.pa.us>
//pyrrho          5433/tcp   Pyrrho DBMS
//pyrrho          5433/udp   Pyrrho DBMS
//#                          Malcolm Crowe <malcolm.crowe&paisley.ac.uk> November 2005
//sgi-arrayd      5434/tcp   SGI Array Services Daemon
//sgi-arrayd      5434/udp   SGI Array Services Daemon
//#                          Karl Feind <kaf&sgi.com> October 2005
//sceanics        5435/tcp   SCEANICS situation and action notification
5435,//sceanics        5435/udp   SCEANICS situation and action notification
//#                          Richard Olsen <olsen.richard&yahoo.com>
//#               5436-5442  Unassigned
5443,//spss            5443/tcp   Pearson HTTPS
5443,//spss            5443/udp   Pearson HTTPS
//#                          Pearson <chad.smith&pearson.com> 17 January 2008
//#               5444-5452  Unassigned
5453,//surebox         5453/tcp   SureBox
//surebox         5453/udp   SureBox
//#                          Emin BORU <emin&danismanlik.net> November 2004
//apc-5454        5454/tcp   APC 5454
//apc-5454        5454/udp   APC 5454
//apc-5455        5455/tcp   APC 5455
//apc-5455        5455/udp   APC 5455
//apc-5456        5456/tcp   APC 5456
5456,//apc-5456        5456/udp   APC 5456
//#                          American Power Conversion <ports&apcc.com>
//#               5457-5460  Unassigned
5461,//silkmeter       5461/tcp   SILKMETER
//silkmeter       5461/udp   SILKMETER
//#                          Klaus Fellner <webmaster&segue.com> <kfellner&segue.com>
//ttl-publisher   5462/tcp   TTL Publisher
//ttl-publisher   5462/udp   TTL Publisher
//#                          Peter Jacobs <pjacobs&tullib.com>
//ttlpriceproxy   5463/tcp   TTL Price Proxy
//ttlpriceproxy   5463/udp   TTL Price Proxy
//#                          Peter Jacobs <pjacobs&tullib.com>
//quailnet	5464/tcp   Quail Networks Object Broker
//quailnet	5464/udp   Quail Networks Object Broker
//#			   Craig N. Bissell <craig&quailnetworks.com> April 2006
//netops-broker   5465/tcp   NETOPS-BROKER
5465,//netops-broker   5465/udp   NETOPS-BROKER
//#                          John R. Deuel <kink&netops.com>
//#		5466-5499  Unassigned
5500,//fcp-addr-srvr1  5500/tcp   fcp-addr-srvr1
//fcp-addr-srvr1  5500/udp   fcp-addr-srvr1
//fcp-addr-srvr2  5501/tcp   fcp-addr-srvr2
//fcp-addr-srvr2  5501/udp   fcp-addr-srvr2
//fcp-srvr-inst1  5502/tcp   fcp-srvr-inst1
//fcp-srvr-inst1  5502/udp   fcp-srvr-inst1
//fcp-srvr-inst2  5503/tcp   fcp-srvr-inst2
//fcp-srvr-inst2  5503/udp   fcp-srvr-inst2
//fcp-cics-gw1    5504/tcp   fcp-cics-gw1
//fcp-cics-gw1    5504/udp   fcp-cics-gw1
//#			   Ken Wittmer <kenneth.m.wittmer&accenture.com>
//checkoutdb	5505/tcp   Checkout Database
5505,//checkoutdb	5505/udp   Checkout Database
//#			   Dirk Stoop <dirk&madebysofa.com> April 2007
//#               5506-5552  Unassigned
5552,//sgi-eventmond   5553/tcp   SGI Eventmond Port
//sgi-eventmond   5553/udp   SGI Eventmond Port
//#                          Andrei Vilkotski <andreiv&sgi.com> June 2003
//sgi-esphttp     5554/tcp   SGI ESP HTTP
//sgi-esphttp     5554/udp   SGI ESP HTTP
//#                          Vladimir Legalov <legalov&sgi.com>
//############Port 5555 also used by HP Omniback#####################
//###UNAUTHORIZED USE: port 5555 by Intermec UDPPlus#################
//personal-agent  5555/tcp   Personal Agent
//personal-agent  5555/udp   Personal Agent
//#			               Jackie Wu <jackiew&infoseek.com>
//###################################################################
//freeciv         5556/tcp   Freeciv gameplay
5556,//freeciv         5556/udp   Freeciv gameplay
//#			   Reinier Post, Paul Zastoupil <freeciv&freeciv.org> January 2006
//#		5557-5565  Unassigned
5566,//westec-connect  5566/tcp   Westec Connect
//#                          Previous contact: Kaushlesh Chandel <kchandel&annetsite.com> 03 March 2009
//#                          Current contact: Jon Bolen <jon.bolen&westec.net> 18 March 2009
//#               5566/udp   Unassigned
//m-oap		5567/tcp   Multicast Object Access Protocol
//m-oap		5567/udp   Multicast Object Access Protocol
//#                          Bryant Eastham <protocols&pewla.us.pewg.panasonic.com> November 2004
//sdt		5568/tcp   Session Data Transport Multicast
5568,//sdt		5568/udp   Session Data Transport Multicast
//#			   Daniel W. Antonuk <dantonuk&etcconnect.com> May 2006
//#               5569-5572  Unassigned
5573,//sdmmp		5573/tcp   SAS Domain Management Messaging Protocol
//sdmmp		5573/udp   SAS Domain Management Messaging Protocol
//#			   Ron Zuckerman <ron.zuckerman&lsi.com> 30 August 2007
//lsi-bobcat      5574/tcp   SAS IO Forwarding
//#                          Mandar Joshi <mandar.joshi&lsi.com> 09 February 2009 
5574,//#               5574/udp   Reserved
//#               5575-5578  Unassigned
5579,//fdtracks        5579/tcp   FleetDisplay Tracking Service
//#                          Henrik Woffinden <hw&nitramlexa.com> 22 September 2008
//#               5579/udp   Unassigned
//tmosms0		5580/tcp   T-Mobile SMS Protocol Message 0
//tmosms0		5580/udp   T-Mobile SMS Protocol Message 0
//tmosms1		5581/tcp   T-Mobile SMS Protocol Message 1
//tmosms1		5581/udp   T-Mobile SMS Protocol Message 1
//#			   Ezinne Oji <ezinne.oji&t-mobile.com> June 2006
//fac-restore     5582/tcp   T-Mobile SMS Protocol Message 3
//fac-restore     5582/udp   T-Mobile SMS Protocol Message 3
//#                          Jessica Yan <jessica.yan2&t-mobile.com> 19 February 2008
//tmo-icon-sync   5583/tcp   T-Mobile SMS Protocol Message 2
//tmo-icon-sync   5583/udp   T-Mobile SMS Protocol Message 2
//#                          Donghwan Lim <donghwan.lim&t-mobile.com> 22 January 2008
//bis-web         5584/tcp   BeInSync-Web
//bis-web         5584/udp   BeInSync-Web
//bis-sync        5585/tcp   BeInSync-sync
5585,//bis-sync        5585/udp   BeInSync-sync
//#                          Adi Ruppin <adi.ruppin&data-pod.com> August 2005
//#               5586-5596  Unassigned
5597,//ininmessaging   5597/tcp   inin secure messaging
//ininmessaging   5597/udp   inin secure messaging
//#			   Mike Gagle <mikeg&inin.com> May 2006
//mctfeed		5598/tcp   MCT Market Data Feed
//mctfeed		5598/udp   MCT Market Data Feed
//#			   Stephane Touizer <touizer&microcaptrade.com> May 2006
//esinstall	5599/tcp   Enterprise Security Remote Install
//esinstall	5599/udp   Enterprise Security Remote Install
//esmmanager 	5600/tcp   Enterprise Security Manager
//esmmanager	5600/udp   Enterprise Security Manager
//esmagent	5601/tcp   Enterprise Security Agent
//esmagent   	5601/udp   Enterprise Security Agent
//#		           Kimberly Gibbs <kimgib&CCGATE-UT.AXENT.COM>
//a1-msc		5602/tcp   A1-MSC
//a1-msc		5602/udp   A1-MSC
//a1-bs		5603/tcp   A1-BS
//a1-bs  		5603/udp   A1-BS
//a3-sdunode	5604/tcp   A3-SDUNode
//a3-sdunode	5604/udp   A3-SDUNode
//a4-sdunode	5605/tcp   A4-SDUNode
5604,//a4-sdunode	5605/udp   A4-SDUNode
//#		           Mike Dolan <MDolan&ihcmail.ih.lucent.com>
//#               5606-5626  Unassigned
5627,//ninaf		5627/tcp   Node Initiated Network Association Forma
//ninaf		5627/udp   Node Initiated Network Association Forma
//#			   Thomas Scholl <tscholl&spf.is-is.ca> March 2006
//htrust          5628/tcp   HTrust API
//htrust          5628/udp   HTrust API
//#                          Karl Olafsson <Karl.Olafsson&covariant-systems.com> 24 October 2008
//symantec-sfdb	5629/tcp   Symantec Storage Foundation for Database
//symantec-sfdb	5629/udp   Symantec Storage Foundation for Database
//#			   Quang Thoi <quang_thoi&symantec.com> November 2006
//precise-comm	5630/tcp   PreciseCommunication
//precise-comm	5630/udp   PreciseCommunication
//#			   Alon Tamir <alon_tamir&symantec.com> April 2006
//pcanywheredata  5631/tcp   pcANYWHEREdata
//pcanywheredata  5631/udp   pcANYWHEREdata
//pcanywherestat  5632/tcp   pcANYWHEREstat
//pcanywherestat  5632/udp   pcANYWHEREstat
//#                          Jon Rosarky <JRosarky&symantec.com>
//beorl           5633/tcp   BE Operations Request Listener
//beorl           5633/udp   BE Operations Request Listener
//#			   chirag desai <Chirag_Desai&symantec.com> February 2006
//xprtld		5634/tcp   SF Message Service
//xprtld		5634/udp   SF Message Service
//#			   VR Satish <vr_satish&symantec.com> 16 August 2007
//sfmsso          5635/tcp   SFM Authentication Subsystem
//#                          De-Chih Chien <de-chih_chien&symantec.com> 15 September 2008
//#               5635/udp   Reserved
//sfm-db-server   5636/tcp   SFMdb - SFM DB server
//#                          De-Chih Chien <de-chih_chien&symantec.com> 06 October 2008
5636,//#               5636/udp   Reserved
//#               5637-5670  Unassigned
5670,//amqps           5671/tcp   amqp protocol over TLS/SSL
//amqps           5671/udp   amqp protocol over TLS/SSL
//#                          Ted Ross <tross&redhat.com> 26 March 2008
//amqp		5672/tcp   AMQP
//amqp		5672/udp   AMQP
//#			   Pieter Hintjens <ph&imatix.com> January 2006
//amqp		5672/sctp  AMQP
//#			   Martin Sustrik <sustrik&imatix.com> March 2007
//jms             5673/tcp   JACL Message Server
//jms             5673/udp   JACL Message Server
//#                          Stuart Allen <stuart&jacl.animats.net> February 2002
//hyperscsi-port  5674/tcp   HyperSCSI Port
//hyperscsi-port  5674/udp   HyperSCSI Port
//#                          Data Storage Institute, Singapore 
//#                          <Patrick&dsi.nus.edu.sg> February 2002
//v5ua            5675/tcp   V5UA application port
//v5ua            5675/udp   V5UA application port
//v5ua            5675/sctp  V5UA application port
//#                          RFC3807 June 2004
//raadmin         5676/tcp   RA Administration
//raadmin         5676/udp   RA Administration
//#                          Sergei Zjaikin <serge&previo.ee> February 2002
//questdb2-lnchr  5677/tcp   Quest Central DB2 Launchr
//questdb2-lnchr  5677/udp   Quest Central DB2 Launchr
//#                          Robert M. Mackowiak <rmackowiak&quest.com> February 2002
//rrac            5678/tcp   Remote Replication Agent Connection  
//rrac            5678/udp   Remote Replication Agent Connection  
//dccm            5679/tcp   Direct Cable Connect Manager
//dccm            5679/udp   Direct Cable Connect Manager
//#                          Mark Miller <mmiller&MICROSOFT.com>
//auriga-router   5680/tcp   Auriga Router Service
//auriga-router   5680/udp   Auriga Router Service
//#			   Vincent Gaudeul <technique&auriga.fr> February 2006
//ncxcp 		5681/tcp   Net-coneX Control Protocol
5681,//ncxcp 		5681/udp   Net-coneX Control Protocol
//#			   Ryan Werber <ryan&ncxti.com> June 2006
//#               5682-5687  Unassigned
5688,//ggz             5688/tcp   GGZ Gaming Zone
//ggz             5688/udp   GGZ Gaming Zone
//#                          Josef Spillner <admin&ggzgamingzone.org> January 2003  
//qmvideo		5689/tcp   QM video network management protocol
5689,//qmvideo		5689/udp   QM video network management protocol
//#			   Jamie Lokier <jamie&jlokier.co.uk> May 2006
//#               5690-5712  Unassigned
5713,//proshareaudio   5713/tcp   proshare conf audio
//proshareaudio   5713/udp   proshare conf audio
//prosharevideo   5714/tcp   proshare conf video
//prosharevideo   5714/udp   proshare conf video
//prosharedata    5715/tcp   proshare conf data 
//prosharedata    5715/udp   proshare conf data 
//prosharerequest 5716/tcp   proshare conf request
//prosharerequest 5716/udp   proshare conf request
//prosharenotify  5717/tcp   proshare conf notify 
//prosharenotify  5717/udp   proshare conf notify 
//#                          <gunner&ibeam.intel.com>
//dpm		5718/tcp   DPM Communication Server
//dpm		5718/udp   DPM Communication Server
//dpm-agent	5719/tcp   DPM Agent Coordinator
//dpm-agent	5719/udp   DPM Agent Coordinator
//#			   Sundar Srinivasan <sundars&microsoft.com> Vinay Badami <VinayB&microsoft.com> May 2006
//ms-licensing    5720/tcp   MS-Licensing
//ms-licensing    5720/udp   MS-Licensing 
//#                          Thomas Lindeman <tlinde&microsoft.com> November 2002
//dtpt            5721/tcp   Desktop Passthru Service
//dtpt            5721/udp   Desktop Passthru Service
//#                          Dan Leising <dleising&microsoft.com> January 2005
//msdfsr		5722/tcp   Microsoft DFS Replication Service
//msdfsr		5722/udp   Microsoft DFS Replication Service
//#			   Guhan Suriyanarayanan <guhans&microsoft.com> March 2006
//omhs		5723/tcp   Operations Manager - Health Service
//omhs		5723/udp   Operations Manager - Health Service
//omsdk		5724/tcp   Operations Manager - SDK Service
//omsdk		5724/udp   Operations Manager - SDK Service
//#			   Gerardo Dilillo <MOMIANA&microsoft.com> August 2006
//ms-ilm          5725/tcp   Microsoft Identity Lifecycle Manager
//#               5725/udp   Reserved
//#                          Rob Ward <RobWard&microsoft.com> 02 May 2008
//ms-ilm-sts      5726/tcp   Microsoft Lifecycle Manager Secure Token Service 
5726,//#               5726/udp   Reserved
//#                          Rob Ward <RobWard&microsoft.com> 02 May 2008
//#               5727       Unassigned (Removed 24 December 2008)
//#               5728-5728  Unassigned
5729,//openmail        5729/tcp   Openmail User Agent Layer
//openmail        5729/udp   Openmail User Agent Layer
//#                          OpenMail Encyclopedia <opencyc&hpopd.pwd.hp.com>
//#                          Don Loughry <DON_LOUGHRY&hp-cupertino-om4.om.hp.com>
//unieng          5730/tcp   Steltor's calendar access
5730,//unieng          5730/udp   Steltor's calendar access
//#                          Bernard Desruisseaux <bernard&steltor.com>
//#               5731-5740  Unassigned           
5741,//ida-discover1   5741/tcp   IDA Discover Port 1
//ida-discover1   5741/udp   IDA Discover Port 1
//ida-discover2   5742/tcp   IDA Discover Port 2
//ida-discover2   5742/udp   IDA Discover Port 2
//#                          MPITech Support <morten.christensen&I-DATA.COM>
//watchdoc-pod    5743/tcp   Watchdoc NetPOD Protocol
//watchdoc-pod    5743/udp   Watchdoc NetPOD Protocol
//#                          Christophe Chevalier <chevalier&archimed.fr> August 2005
//watchdoc        5744/tcp   Watchdoc Server
//watchdoc        5744/udp   Watchdoc Server
//#                          Christophe Chevalier <chevalier&archimed.fr> November 2004
//fcopy-server    5745/tcp   fcopy-server
//fcopy-server    5745/udp   fcopy-server
//fcopys-server   5746/tcp   fcopys-server
//fcopys-server   5746/udp   fcopys-server
//#                          Moshe Leibovitch <moshe&softlinkusa.com>
//tunatic         5747/tcp   Wildbits Tunatic
//tunatic         5747/udp   Wildbits Tunatic
//tunalyzer       5748/tcp   Wildbits Tunalyzer
5748,//tunalyzer       5748/udp   Wildbits Tunalyzer
//#                          Sylvain Demongeot <sylvain.demongeot&wildbits.com> August 2005
//#               5749       Unassigned
5750,//rscd            5750/tcp   Bladelogic Agent Service
//rscd            5750/udp   Bladelogic Agent Service
//#                          Previous contact: Brian Trevor <btrevor&bladelogic.com> 07 January 2008
//#                          Current contact: Brian Trevor <btrevor&bmc.com> 24 October 2008
//#               5751-5754  Unassigned
5755,//openmailg       5755/tcp   OpenMail Desk Gateway server
//openmailg       5755/udp   OpenMail Desk Gateway server
//x500ms          5757/tcp   OpenMail X.500 Directory Server
//x500ms          5757/udp   OpenMail X.500 Directory Server
//openmailns      5766/tcp   OpenMail NewMail Server
//openmailns      5766/udp   OpenMail NewMail Server
//s-openmail      5767/tcp   OpenMail Suer Agent Layer (Secure)
//s-openmail      5767/udp   OpenMail Suer Agent Layer (Secure)
//openmailpxy     5768/tcp   OpenMail CMTS Server
//openmailpxy     5768/udp   OpenMail CMTS Server
//#                          OpenMail Encyclopedia <opencyc&hpopd.pwd.hp.com>
//#                          Don Loughry <DON_LOUGHRY&hp-cupertino-om4.om.hp.com>
//spramsca	5769/tcp   x509solutions Internal CA
//spramsca	5769/udp   x509solutions Internal CA
//spramsd		5770/tcp   x509solutions Secure Data
//spramsd		5770/udp   x509solutions Secure Data
//#			   Brendan Fay <brendan.fay&x509solutions.com> February 2006
//netagent        5771/tcp   NetAgent
5771,//netagent        5771/udp   NetAgent
//#                          Bradley Birnbaum <bradley.birnbaum&eshare.com>
//#               5772-5776  Unassigned
5777,//dali-port       5777/tcp   DALI Port
5777,//dali-port       5777/udp   DALI Port
//#                          Wayne Morrow / Michael Melio <wmorrow&starfieldcorp.com> / <meliomd&comcast.net> October 2003
//#               5778-5780  Unassigned
5781,//3par-evts       5781/tcp   3PAR Event Reporting Service
//3par-evts       5781/udp   3PAR Event Reporting Service
//#                          Sushil Thomas <iana-comm&3par.com> 10 March 2008
//3par-mgmt       5782/tcp   3PAR Management Service
//3par-mgmt       5782/udp   3PAR Management Service
//3par-mgmt-ssl   5783/tcp   3PAR Management Service with SSL
5783,//3par-mgmt-ssl   5783/udp   3PAR Management Service with SSL
//#                          Don Marselle <don.marselle&3par.com> 19 March 2008
//#               5784       Unassigned
5785,//3par-rcopy      5785/tcp   3PAR Inform Remote Copy
5785,//3par-rcopy      5785/udp   3PAR Inform Remote Copy
//#                          Don Marselle <don.marselle&3Par.com> 09 April 2008
//#               5786-5792  Unassigned
5793,//xtreamx		5793/tcp   XtreamX Supervised Peer message
5793,//xtreamx		5793/udp   XtreamX Supervised Peer message
//#			   Ahmad Tajuddin Samsudin <tajuddin&tmrnd.com.my> February 2007
//#               5794-5812  Unassigned
5813,//icmpd           5813/tcp   ICMPD
//icmpd           5813/udp   ICMPD
//#                          Shane O'Donnell <shane&opennms.org> 
//spt-automation  5814/tcp   Support Automation
5814,//spt-automation  5814/udp   Support Automation
//#                          Joshua Hawkins <joshua.hawkins&hp.com> November 2003
//#               5815-5858  Unassigned 
5859,//wherehoo        5859/tcp   WHEREHOO
5859,//wherehoo        5859/udp   WHEREHOO
//#                          Jim Youll <jim&media.mit.edu>
//#               5860-5862  Unassigned
5863,//ppsuitemsg	5863/tcp   PlanetPress Suite Messeng
5863,//ppsuitemsg	5863/udp   PlanetPress Suite Messeng
//#			   Yannick Fortin <fortiny&ca.objectiflune.com> February 2006
//#               5864-5899  Unassigned
5900,//vnc-server	5900/tcp   VNC Server
5900,//vnc-server	5900/udp   VNC Server
//#			   Tristan Richardson <iana&realvnc.com> March 2006
//#               5901-5909  Unassigned
5910,//cm              5910/tcp   Context Management
//cm              5910/udp   Context Management
//cpdlc           5911/tcp   Controller Pilot Data Link Communication
//cpdlc           5911/udp   Controller Pilot Data Link Communication
//fis             5912/tcp   Flight Information Services
//fis             5912/udp   Flight Information Services
//ads-c           5913/tcp   Automatic Dependent Surveillance
5913,//ads-c           5913/udp   Automatic Dependent Surveillance
//#                          Eivan Cerasi <eivan.cerasi&eurocontrol.int> 10 October 2008
//#               5914-5962  Unassigned
5963,//indy            5963/tcp   Indy Application Server
5963,//indy            5963/udp   Indy Application Server
//#                          Bjorn Lantz <bjorn.lantz&encode.se> November 2004
//#               5964-5967  Unassigned
5968,//mppolicy-v5     5968/tcp   mppolicy-v5
//mppolicy-v5     5968/udp   mppolicy-v5
//mppolicy-mgr    5969/tcp   mppolicy-mgr
5969,//mppolicy-mgr	5969/udp   mppolicy-mgr
//#                          Yutaka Ono <ono&saint.nm.fujitsu.co.jp>
//#               5970-5983  Unassigned
5984,//couchdb         5984/tcp   CouchDB
//couchdb         5984/udp   CouchDB
//#			   Noah Slater <nslater&bytesexual.org> 27 November 2007
//wsman		5985/tcp   WBEM WS-Management HTTP
//wsman		5985/udp   WBEM WS-Management HTTP
//wsmans		5986/tcp   WBEM WS-Management HTTP over TLS/SSL
//wsmans		5986/udp   WBEM WS-Management HTTP over TLS/SSL
//#			   Jim Davis <jim.davis&wbemsolutions.com> November 2006
//wbem-rmi        5987/tcp   WBEM RMI
//wbem-rmi        5987/udp   WBEM RMI
//wbem-http       5988/tcp   WBEM CIM-XML (HTTP)
//wbem-http       5988/udp   WBEM CIM-XML (HTTP)
//#                          Jim Davis <jim.davis&wbemsolutions.com>
//wbem-https      5989/tcp   WBEM CIM-XML (HTTPS)
//wbem-https      5989/udp   WBEM CIM-XML (HTTPS)
//#                          Jim Davis <jim.davis&wbemsolutions.com>
//wbem-exp-https  5990/tcp   WBEM Export HTTPS
//wbem-exp-https  5990/udp   WBEM Export HTTPS
//#                          Denise Eckstein <denise.eckstein&hp.com> November 2004
//nuxsl           5991/tcp   NUXSL
//nuxsl           5991/udp   NUXSL
//#                          Kai Kretschmann <K.Kretschmann&security-gui.de> March 2002
//consul-insight  5992/tcp   Consul InSight Security
5992,//consul-insight  5992/udp   Consul InSight Security
//#                          Arthur Hillenaar <arthur.hillenaar&consul.com> January 2006
//#               5993-5998  Unassigned
5999,//cvsup           5999/tcp   CVSup
//cvsup           5999/udp   CVSup
//#                          Randall Atkinson <rja&inet.org>
//x11             6000-6063/tcp   X Window System
//x11             6000-6063/udp   X Window System
//#                          Stephen Gildea <gildea&lcs.mit.edu>
//ndl-ahp-svc     6064/tcp   NDL-AHP-SVC
//ndl-ahp-svc     6064/udp   NDL-AHP-SVC
//#                          John Richmond <john&ndl.co.uk>
//winpharaoh      6065/tcp   WinPharaoh
//winpharaoh      6065/udp   WinPharaoh
//#	                   Basil Lee <basil.lee&gnnettest.com>
//ewctsp          6066/tcp   EWCTSP
6066,//ewctsp          6066/udp   EWCTSP
//#                          Mark Bailon <mark.bailon&ericsson.com>
//#               6067       Unassigned (Removed on 2007-07-17)
6068,//gsmp            6068/tcp   GSMP
//gsmp            6068/udp   GSMP
//#                          Avri Doria <avri.doria&nokia.com>
//trip            6069/tcp   TRIP
//trip            6069/udp   TRIP
//#                          Hussein F. Salama <hsalama&cisco.com>
//messageasap     6070/tcp   Messageasap
//messageasap     6070/udp   Messageasap
//#                          Murray Freeman <murray&officedomain.com>
//ssdtp           6071/tcp   SSDTP
//ssdtp           6071/udp   SSDTP
//#                          Michael Shearson <mikes&softsys-inc.com> 
//diagnose-proc   6072/tcp   DIAGNOSE-PROC
//diagnose-proc   6072/udp   DIAGNOSE-PROC
//#                          Allan Miller <amiller&handsfreenetworks.com>
//directplay8     6073/tcp   DirectPlay8
//directplay8     6073/udp   DirectPlay8
//#                          John Kane <johnkan&microsoft.com>
//max		6074/tcp   Microsoft Max
//max		6074/udp   Microsoft Max
6074,//#			   Jay Beavers <Jay.Beavers&Microsoft.Com> February 2006
//#               6075-6083  Unassigned
6084,//p2p-sip         6084/tcp   Peer to Peer Infrastructure Protocol
//#                          Cullen Jennings <fluffy&cisco.com> 29 January 2009
//#               6084/udp   Reserved
//konspire2b      6085/tcp   konspire2b p2p network
//konspire2b      6085/udp   konspire2b p2p network
//#                          Jason Rohrer <rohrer&cse.ucsc.edu> October 2002
//pdtp		6086/tcp   PDTP P2P
//pdtp		6086/udp   PDTP P2P
//#			   Tony Arcieri <bascule&gmail.com> March 2006
//ldss		6087/tcp   Local Download Sharing Service
6087,//ldss		6087/udp   Local Download Sharing Service
//#			   Clifford Heath <cjh&managesoft.com> May 2006
//#               6088-6099  Unassigned
6100,//synchronet-db   6100/tcp   SynchroNet-db
//synchronet-db   6100/udp   SynchroNet-db
//synchronet-rtc  6101/tcp   SynchroNet-rtc
//synchronet-rtc  6101/udp   SynchroNet-rtc
//synchronet-upd  6102/tcp   SynchroNet-upd
//synchronet-upd  6102/udp   SynchroNet-upd
//#                          Arne Haugland <Arne.Haugland&parasoldev.com>    
//rets            6103/tcp   RETS
//rets            6103/udp   RETS
//#                          Bruce Toback <btoback&optc.com>
//dbdb            6104/tcp   DBDB
//dbdb            6104/udp   DBDB
//#                          Aaron Brick <aa&lithic.org>
//primaserver     6105/tcp   Prima Server
//primaserver     6105/udp   Prima Server
//mpsserver       6106/tcp   MPS Server
//mpsserver       6106/udp   MPS Server
//#                          Prima Designs Systems Ltd. <info&prima.com.hk>
//etc-control     6107/tcp   ETC Control
//etc-control     6107/udp   ETC Control
//#                          Steve Polishinski <spolishinski&etcconnect.com>  
//sercomm-scadmin 6108/tcp   Sercomm-SCAdmin
//sercomm-scadmin 6108/udp   Sercomm-SCAdmin
//#                          Melinda Tsao <melinda_tsao&mail.sercomm.com.tw>
//globecast-id    6109/tcp   GLOBECAST-ID
//globecast-id    6109/udp   GLOBECAST-ID
//#                          Piers Scannell <piers&globecastne.com>
//softcm          6110/tcp   HP SoftBench CM
//softcm          6110/udp   HP SoftBench CM
//spc             6111/tcp   HP SoftBench Sub-Process Control
//spc             6111/udp   HP SoftBench Sub-Process Control
//#                          Scott A. Kramer <sk&tleilaxu.sde.hp.com>
//dtspcd          6112/tcp   dtspcd
6112,//dtspcd          6112/udp   dtspcd   
//#                          Doug Royer <Doug&Royer.com>
//#               6113-6121  Unassigned
6122,//bex-webadmin    6122/tcp   Backup Express Web Server
//bex-webadmin    6122/udp   Backup Express Web Server
//#                          Chi Shih Chang <cchang&syncsort.com> November 2005
//backup-express  6123/tcp   Backup Express
//backup-express  6123/udp   Backup Express
//#			   Chi Shih Chang <cchang&syncsort.com>
//pnbs            6124/tcp   Phlexible Network Backup Service
6124,//pnbs            6124/udp   Phlexible Network Backup Service
//#                          William R. Lear <wlear&phlexible.com> 23 October 2008
//#               6125-6132  Unassigned
6133,//nbt-wol         6133/tcp   New Boundary Tech WOL
6133,//nbt-wol         6133/udp   New Boundary Tech WOL
//#                          Elizabeth Zilen <ezilen&newboundary.com> November 2004
//#               6134-6139  Unassigned
6140,//pulsonixnls     6140/tcp   Pulsonix Network License Service
//pulsonixnls     6140/udp   Pulsonix Network License Service
//#                          David Manns <davidm&pulsonix.com> 28 February 2008
//meta-corp       6141/tcp   Meta Corporation License Manager
//meta-corp       6141/udp   Meta Corporation License Manager
//#                          Osamu Masuda <--none--->
//aspentec-lm     6142/tcp   Aspen Technology License Manager
//aspentec-lm     6142/udp   Aspen Technology License Manager
//#                          Kevin Massey <massey&aspentec.com>
//watershed-lm    6143/tcp   Watershed License Manager
//watershed-lm    6143/udp   Watershed License Manager
//#                          David Ferrero <david&zion.com>
//statsci1-lm     6144/tcp   StatSci License Manager - 1
//statsci1-lm     6144/udp   StatSci License Manager - 1
//statsci2-lm     6145/tcp   StatSci License Manager - 2
//statsci2-lm     6145/udp   StatSci License Manager - 2
//#                          Scott Blachowicz <scott&statsci.com>
//lonewolf-lm     6146/tcp   Lone Wolf Systems License Manager
//lonewolf-lm     6146/udp   Lone Wolf Systems License Manager
//#                          Dan Klein <dvk&lonewolf.com>
//montage-lm      6147/tcp   Montage License Manager
//montage-lm      6147/udp   Montage License Manager
//#                          Michael Ubell <michael&montage.com>
//ricardo-lm      6148/tcp   Ricardo North America License Manager
//ricardo-lm      6148/udp   Ricardo North America License Manager
//#                          M Flemming <mflemming&aol.com>
//tal-pod         6149/tcp   tal-pod 
6149,//tal-pod         6149/udp   tal-pod 
//#                          Steven Loomis <srl&taligent.com>
//#               6150-6160  Unassigned 
6161,//patrol-ism      6161/tcp   PATROL Internet Srv Mgr
//patrol-ism      6161/udp   PATROL Internet Srv Mgr
//patrol-coll     6162/tcp   PATROL Collector
//patrol-coll     6162/udp   PATROL Collector
//#                          Portnoy Boxman <portnoy_boxman&bmc.com> January 2005
//pscribe         6163/tcp   Precision Scribe Cnx Port
6163,//pscribe         6163/udp   Precision Scribe Cnx Port
//#                          Robert W Hodges <iana&precdata.com> January 2005
//#               6164-6199  Unassigned 
6200,//lm-x		6200/tcp   LM-X License Manager by X-Formation
//lm-x		6200/udp   LM-X License Manager by X-Formation
//#			   Henrik Goldman <hg&x-formation.com> October 2006
//#               6201-6221  Unassigned 
6222,//radmind		6222/tcp   Radmind Access Protocol
//radmind		6222/udp   Radmind Access Protocol
//#			   Patrick M McNeal <mcneal&umich.edu> March 2006
//#               6223-6240  Unassigned 
6241,//jeol-nsdtp-1    6241/tcp   JEOL Network Services Data Transport Protocol 1
//jeol-nsddp-1    6241/udp   JEOL Network Services Dynamic Discovery Protocol 1
//jeol-nsdtp-2    6242/tcp   JEOL Network Services Data Transport Protocol 2
//jeol-nsddp-2    6242/udp   JEOL Network Services Dynamic Discovery Protocol 2
//jeol-nsdtp-3    6243/tcp   JEOL Network Services Data Transport Protocol 3
//jeol-nsddp-3    6243/udp   JEOL Network Services Dynamic Discovery Protocol 3
//jeol-nsdtp-4    6244/tcp   JEOL Network Services Data Transport Protocol 4
6244,//jeol-nsddp-4    6244/udp   JEOL Network Services Dynamic Discovery Protocol 4
//#                          Kevin Wellwood <wellwood&jeol.com> 17 April 2008
//#               6245-6250  Unassigned
6251,//tl1-raw-ssl     6251/tcp   TL1 Raw Over SSL/TLS
//tl1-raw-ssl     6251/udp   TL1 Raw Over SSL/TLS
//#                          Jim Humphreys <jhumphre&ciena.com> 29 January 2008
//tl1-ssh         6252/tcp   TL1 over SSH
//tl1-ssh         6252/udp   TL1 over SSH
//#                          Jim Humphreys <jhumphre&ciena.com> 25 January 2008
//crip            6253/tcp   CRIP
6253,//crip            6253/udp   CRIP
//#                          Mike Rodbell <mrodbell&ciena.com> 
//#               6254-6267  Unassigned
6268,//grid		6268/tcp   Grid Authentication 
//grid		6268/udp   Grid Authentication 
//grid-alt	6269/tcp   Grid Authentication Alt
6269,//grid-alt	6269/udp   Grid Authentication Alt
//#			   Jason Hamilton <JHamilton&griddatasecurity.com> June 2006
//#               6270-6299  Unassigned
6300,//bmc-grx         6300/tcp   BMC GRX
//bmc-grx         6300/udp   BMC GRX
//#                          Portnoy Boxman <portnoy_boxman&bmc.com>
//bmc_ctd_ldap	6301/tcp   BMC CONTROL-D LDAP SERVER
6301,//bmc_ctd_ldap	6301/udp   BMC CONTROL-D LDAP SERVER
//#			   Portnoy Boxman <Portnoy_Boxman&bmc.com> September 2006
//#               6302-6315  Unassigned
6316,//abb-escp        6316/tcp   Ethernet Sensor Communications Protocol
6316,//abb-escp        6316/udp   Ethernet Sensor Communications Protocol
//#                          Jaime Antolin <jaime.antolin&ie.abb.com> 25 September 2008
//#               6317-6319  Unassigned
6320,//repsvc		6320/tcp   Double-Take Replication Service
//repsvc		6320/udp   Double-Take Replication Service
//#			   James Wilkinson <jwilkinson&doubletake.com> April 2006
//emp-server1     6321/tcp   Empress Software Connectivity Server 1
//emp-server1     6321/udp   Empress Software Connectivity Server 1   
//emp-server2     6322/tcp   Empress Software Connectivity Server 2  
6322,//emp-server2     6322/udp   Empress Software Connectivity Server 2  
//#                          Srdjan Holovac <srdjan&empress.com>
//#               6323-6342  Unassigned
6343,//sflow           6343/tcp   sFlow traffic monitoring
6343,//sflow           6343/udp   sFlow traffic monitoring
//#                          Peter Phaal <peter.phaal&inmon.com> June 2003
//#               6344-6345  Unassigned
6346,//gnutella-svc    6346/tcp   gnutella-svc
//gnutella-svc    6346/udp   gnutella-svc
//gnutella-rtr    6347/tcp   gnutella-rtr
6347,//gnutella-rtr    6347/udp   gnutella-rtr
//#                          Serguei Osokine <osokin&paragraph.com>
//#               6348-6354  Unassigned
6355,//pmcs		6355/tcp   PMCS applications
6356,//pmcs		6355/udp   PMCS applications
//#			   Pavel Mendl <pavel_mendl&centrum.cz> March 2007
//#               6356-6359  Unassigned
6360,//metaedit-mu	6360/tcp   MetaEdit+ Multi-User
6360,//metaedit-mu	6360/udp   MetaEdit+ Multi-User
//#			   Steven Kelly <stevek&metacase.com> 12 November 2007
//#               6361-6369  Unassigned
6370,//metaedit-se	6370/tcp   MetaEdit+ Server Administration
6370,//metaedit-se	6370/udp   MetaEdit+ Server Administration
//#			   Steven Kelly <stevek&metacase.com> 12 November 2007
//#               6371-6381  Unassigned
6382,//metatude-mds    6382/tcp   Metatude Dialogue Server
6382,//metatude-mds    6382/udp   Metatude Dialogue Server
//#                          Menno Zweistra <m.zweistra&metatude.com> 
//#               6383-6388  Unassigned
6389,//clariion-evr01  6389/tcp   clariion-evr01
//clariion-evr01  6389/udp   clariion-evr01
//#                          Dave DesRoches <ddesroches&clariion.com>
//metaedit-ws	6390/tcp   MetaEdit+ WebService API
6390,//metaedit-ws	6390/udp   MetaEdit+ WebService API
//#			   Steven Kelly <stevek&metacase.com> 12 November 2007
//#               6391-6399  Unassigned
6400,//boe-cms         6400       Business Objects CMS contact port
//boe-was         6401       boe-was
//boe-eventsrv    6402       boe-eventsrv
//boe-cachesvr    6403       boe-cachesvr
//boe-filesvr     6404       Business Objects Enterprise internal server
//boe-pagesvr     6405       Business Objects Enterprise internal server
//boe-processsvr  6406       Business Objects Enterprise internal server
//boe-resssvr1    6407       Business Objects Enterprise internal server
//boe-resssvr2    6408       Business Objects Enterprise internal server
//boe-resssvr3    6409       Business Objects Enterprise internal server
6410,//boe-resssvr4    6410       Business Objects Enterprise internal server
//#                          Previous contact: Wade Richards <Wade.Richards&Seagatesoftware.com>
//#                          Current contact: Wade Richards <wade.richards&sap.com> 05 May 2008
//#               6411-6416  Unassigned
6417,//faxcomservice	6417/tcp   Faxcom Message Service
6417,//faxcomservice	6417/udp   Faxcom Message Service
//#			   Albert Leung <aleung&biscom.com> April 2006
//#               6418-6419  Unassigned
6420,//nim-vdrshell    6420/tcp   NIM_VDRShell
//nim-vdrshell    6420/udp   NIM_VDRShell
//nim-wan         6421/tcp   NIM_WAN
6421,//nim-wan         6421/udp   NIM_WAN
//#			   Rik Ditter <managers&generationtechnologies.com> February 2006
//#               6422-6431  Unassigned
6432,//pgbouncer       6432/tcp   PgBouncer
//#                          Marko Kreen <markokr&gmail.com> 13 February 2009
6432,//#               6432/udp   Reserved
//#               6433-6442  Unassigned
6443,//sun-sr-https	6443/tcp   Service Registry Default HTTPS Domain
6443,//sun-sr-https	6443/udp   Service Registry Default HTTPS Domain
//#			   Paul Sterk <paul.sterk&sun.com> March 2006
//sge_qmaster	6444/tcp   Grid Engine Qmaster Service
//sge_qmaster	6444/udp   Grid Engine Qmaster Service
//sge_execd	6445/tcp   Grid Engine Execution Service
//sge_execd	6445/udp   Grid Engine Execution Service
//#			   Andreas Haas <andreas.haas&sun.com> August 2006
//mysql-proxy     6446/tcp   MySQL Proxy
6446,//mysql-proxy     6446/udp   MySQL Proxy
//#                          Kay Roepke <Kay.Roepke&Sun.COM> 22 April 2009
//#               6447-6454  Unassigned
6455,//skip-cert-recv  6455/tcp   SKIP Certificate Receive
6456,//skip-cert-send  6456/udp   SKIP Certificate Send
//#                          Tom Markson <markson&osmosys.incog.com>
//#               6457-6470  Unassigned
6471,//lvision-lm	6471/tcp   LVision License Manager
6471,//lvision-lm	6471/udp   LVision License Manager
//#			   Brian McKinnon <bmk&lvision.com>
//#		6472-6479  Unassigned
6480,//sun-sr-http	6480/tcp   Service Registry Default HTTP Domain
//sun-sr-http	6480/udp   Service Registry Default HTTP Domain
//#			   Paul Sterk <paul.sterk&sun.com> March 2006
//servicetags	6481/tcp   Service Tags
//servicetags	6481/udp   Service Tags
//#			   Peter Schow <Peter.Schow&Sun.COM> January 2007
//ldoms-mgmt      6482/tcp   Logical Domains Management Interface
//ldoms-mgmt      6482/udp   Logical Domains Management Interface
//#                          Eric Sharakan <ldoms-iana-ports&sun.com> 14 February 2008
//SunVTS-RMI	6483/tcp   SunVTS RMI
//SunVTS-RMI	6483/udp   SunVTS RMI
//#			   Sumit Arora <sumit.arora&sun.com> June 2007
//sun-sr-jms	6484/tcp   Service Registry Default JMS Domain
//sun-sr-jms	6484/udp   Service Registry Default JMS Domain
//sun-sr-iiop	6485/tcp   Service Registry Default IIOP Domain
//sun-sr-iiop	6485/udp   Service Registry Default IIOP Domain
//sun-sr-iiops	6486/tcp   Service Registry Default IIOPS Domain
//sun-sr-iiops	6486/udp   Service Registry Default IIOPS Domain
//sun-sr-iiop-aut	6487/tcp   Service Registry Default IIOPAuth Domain
//sun-sr-iiop-aut	6487/udp   Service Registry Default IIOPAuth Domain
//sun-sr-jmx	6488/tcp   Service Registry Default JMX Domain
//sun-sr-jmx	6488/udp   Service Registry Default JMX Domain
//sun-sr-admin	6489/tcp   Service Registry Default Admin Domain
6489,//sun-sr-admin	6489/udp   Service Registry Default Admin Domain
//#			   Paul Sterk <paul.sterk&sun.com> March 2006
//#		6490-6499  Unassigned
6500,//boks		6500/tcp   BoKS Master
//boks		6500/udp   BoKS Master
//boks_servc	6501/tcp   BoKS Servc
//boks_servc	6501/udp   BoKS Servc
//boks_servm	6502/tcp   BoKS Servm
//boks_servm	6502/udp   BoKS Servm
//boks_clntd	6503/tcp   BoKS Clntd
6503,//boks_clntd	6503/udp   BoKS Clntd
//#                          Magnus Nystrom <magnus&dynas.se> 
//#           	6504       Unassigned
6505,//badm_priv	6505/tcp   BoKS Admin Private Port
//badm_priv	6505/udp   BoKS Admin Private Port
//badm_pub 	6506/tcp   BoKS Admin Public Port
//badm_pub  	6506/udp   BoKS Admin Public Port
//bdir_priv 	6507/tcp   BoKS Dir Server, Private Port
//bdir_priv   	6507/udp   BoKS Dir Server, Private Port
//bdir_pub	6508/tcp   BoKS Dir Server, Public Port
//bdir_pub  	6508/udp   BoKS Dir Server, Public Port
//#			   Magnus Nystrom <magnus&dynas.se>
//mgcs-mfp-port   6509/tcp   MGCS-MFP Port
//mgcs-mfp-port   6509/udp   MGCS-MFP Port
//#                          Minoru Ozaki <Minoru.Ozaki&rdmg.mgcs.mei.co.jp>
//mcer-port       6510/tcp   MCER Port
6510,//mcer-port       6510/udp   MCER Port
//#                          Portnoy Boxman <portnoy_boxman&bmc.com>
//#               6511-6512  Unassigned
6513,//netconf-tls     6513/tcp   NETCONF over TLS
//#               6513/udp   Reserved
//#                          [RFC5539]
//syslog-tls      6514/tcp   Syslog over TLS
//#                          [RFC5425]
//#               6514/udp   Reserved          
//elipse-rec      6515/tcp   Elipse RPC Protocol
6515,//elipse-rec      6515/udp   Elipse RPC Protocol
//#			   Fl�vio Englert <flavio&elipse.com.br> 17 September 2007
//#               6516-6542  Unassigned
6543,//lds-distrib     6543/tcp   lds_distrib
//lds-distrib     6543/udp   lds_distrib
//#                          Jack Baker <Jack.Baker&L-3Com.com> June 2003
//lds-dump	6544/tcp   LDS Dump Service
6554,//lds-dump	6544/udp   LDS Dump Service
//#			   Jack Baker <Jack.Baker&L-3Com.com> February 2006
//#               6545-6546  Unassigned
6547,//apc-6547        6547/tcp   APC 6547
//apc-6547        6547/udp   APC 6547
//apc-6548        6548/tcp   APC 6548
//apc-6548        6548/udp   APC 6548
//apc-6549        6549/tcp   APC 6549
//apc-6549        6549/udp   APC 6549
//#                          American Power Conversion <ports&apcc.com>
//fg-sysupdate	6550/tcp   fg-sysupdate
//fg-sysupdate	6550/udp   fg-sysupdate
//#			   Mark Beyer <mbeyer&freegate.com>
//sum		6551/tcp   Software Update Manager
6551,//sum		6551/udp   Software Update Manager
//#			   Jan Dirven <jan.dirven&agfa.com> 13 December 2007
//#               6552-6557  Unassigned
6558,//xdsxdm		6558/tcp	
6558,//xdsxdm		6558/udp	
//#                          Brian Tackett <cym&acrux.net> possible contact
//#               6559-6565  Unassigned
6566,//sane-port       6566/tcp   SANE Control Port
//sane-port       6566/udp   SANE Control Port
//#                          Henning Meier-Geinitz <henning&meier-geinitz.de> October 2002
//esp		6567/tcp   eSilo Storage Protocol
//esp		6567/udp   eSilo Storage Protocol
//#			   Andrew Chernow <andrew&esilo.com> January 2007
//canit_store     6568/tcp   CanIt Storage Manager
//#                          David F. Skoll <dfs&roaringpenguin.com> 22 April 2009
6568,//#               6568/udp   Reserved
//#               6569-6578  Unassigned
6579,//affiliate	6579/tcp   Affiliate
//affiliate	6579/udp   Affiliate
//#			   David Catmull <uncommon&uncommonplace.com> January 2006
//parsec-master   6580/tcp   Parsec Masterserver
//parsec-master   6580/udp   Parsec Masterserver
//parsec-peer     6581/tcp   Parsec Peer-to-Peer
//parsec-peer     6581/udp   Parsec Peer-to-Peer
//parsec-game     6582/tcp   Parsec Gameserver
//parsec-game     6582/udp   Parsec Gameserver
//#                          Andreas Varga <sid&parsec.org>  
//joaJewelSuite   6583/tcp   JOA Jewel Suite
6583,//joaJewelSuite   6583/udp   JOA Jewel Suite
//#                          Bob Rundle <rundle&rundle.com> November 2005
//#               6584-6587  Unassigned
6588,//#               6588       Unassigned
6588,//####Unofficial use of port 6588 by AnalogX and Microsoft####
//#               6589-6599  Unassigned
6600,//mshvlm          6600/tcp   Microsoft Hyper-V Live Migration
//#                          Rajesh Dav� <rajdave&microsoft.com> 03 February 2009
//#               6600/udp   Reserved
//mstmg-sstp      6601/tcp   Microsoft Threat Management Gateway SSTP
//#                          Ori Yosefi <Ori.Yosefi&microsoft.com> 04 May 2009
6601,//#               6601/udp   Reserved
//#               6602-6618  Unassigned
6619,//odette-ftps	6619/tcp   ODETTE-FTP over TLS/SSL
//odette-ftps	6619/udp   ODETTE-FTP over TLS/SSL
//#			   Ieuan Friend <ieuan.friend&dip.co.uk> March 2006
//#                          [RFC5024]
//kftp-data       6620/tcp   Kerberos V5 FTP Data
//kftp-data       6620/udp   Kerberos V5 FTP Data
//kftp            6621/tcp   Kerberos V5 FTP Control
//kftp            6621/udp   Kerberos V5 FTP Control
//#                          Robert J. Scott <rob&hpcmo.hpc.mil> August 2005
//mcftp		6622/tcp   Multicast FTP
//mcftp		6622/udp   Multicast FTP
//#			   Bruce Lueckenhoff <bruce&scalabledesign.com> February 2006
//ktelnet         6623/tcp   Kerberos V5 Telnet
6623,//ktelnet         6623/udp   Kerberos V5 Telnet
//#                          Robert J. Scott <rob&hpcmo.hpc.mil> August 2005
//#               6624-6625  Unassigned
6626,//wago-service	6626/tcp   WAGO Service and Update
//wago-service	6626/udp   WAGO Service and Update
//#			   Wolfgang Adler <electronicc_rd&wago.com> April 2006
//nexgen          6627/tcp   Allied Electronics NeXGen
//nexgen          6627/udp   Allied Electronics NeXGen
//#                          Lou Seitchik <lou&alliedelectronics.com> August 2005 
//afesc-mc        6628/tcp   AFE Stock Channel M/C
6628,//afesc-mc        6628/udp   AFE Stock Channel M/C
//#                          K.K Ho <kk.ho&afe-solutions.com> April 2004
//#               6629-6630  Unassigned
//#               6631       Unassigned (Returned 28 May 2004)
//#               6632-6664  Unassigned
6665,//ircu		6665-6669/tcp  IRCU
//ircu		6665-6669/udp  IRCU
//#			               Brian Tackett <cym&acrux.net>
//vocaltec-gold   6670/tcp   Vocaltec Global Online Directory
//vocaltec-gold   6670/udp   Vocaltec Global Online Directory
//#                          Scott Petrack <Scott_Petrack&vocaltec.com>
//p4p-portal      6671/tcp   P4P Portal Service
//p4p-portal      6671/udp   P4P Portal Service
//#                          Chris Griffiths <chris_griffiths&cable.comcast.com> 28 July 2008
//vision_server   6672/tcp   vision_server
//vision_server   6672/udp   vision_server
//vision_elmd     6673/tcp   vision_elmd
6673,//vision_elmd     6673/udp   vision_elmd
//#                          Chris Kramer <CKramer&gis.shl.com>
//#               6674-6700  Unassigned
6701,//kti-icad-srvr	6701/tcp   KTI/ICAD Nameserver
//kti-icad-srvr	6701/udp   KTI/ICAD Nameserver
//#			               Stanley Knutson <Stanley.Knutson&KTIworld.com> 
//e-design-net    6702/tcp   e-Design network 
//e-design-net    6702/udp   e-Design network 
//e-design-web    6703/tcp   e-Design web 
6703,//e-design-web    6703/udp   e-Design web 
//#			   Janos Lerch <lerch&softic.hu> February 2006
//#               6704-6713  Unassigned
6714,//ibprotocol      6714/tcp   Internet Backplane Protocol
//ibprotocol      6714/udp   Internet Backplane Protocol
//#                          Alessandro Bassi <abassi&cs.utk.edu>
//fibotrader-com  6715/tcp   Fibotrader Communications
6715,//fibotrader-com  6715/udp   Fibotrader Communications
//#			   Robert Wetzold <robert.wetzold&fibotrader.com> January 2006
//#               6716-6766  Unassigned
6767,//bmc-perf-agent  6767/tcp   BMC PERFORM AGENT
//bmc-perf-agent  6767/udp   BMC PERFORM AGENT
//bmc-perf-mgrd   6768/tcp   BMC PERFORM MGRD   
//bmc-perf-mgrd   6768/udp   BMC PERFORM MGRD
//#                          Portnoy Boxman <portnoy_boxman&bmc.com>
//adi-gxp-srvprt  6769/tcp   ADInstruments GxP Server
//adi-gxp-srvprt  6769/udp   ADInstruments GxP Server
//#                          Mathew Pitchforth <mathew&adinstruments.co.nz> August 2005
//plysrv-http     6770/tcp   PolyServe http
//plysrv-http     6770/udp   PolyServe http
//plysrv-https    6771/tcp   PolyServe https
6771,//plysrv-https    6771/udp   PolyServe https
//#                          Mike Spitzer <mjs&polyserve.com> August 2005
//#               6772-6784  Unassigned 
6785,//dgpf-exchg	6785/tcp   DGPF Individual Exchange
//dgpf-exchg	6785/udp   DGPF Individual Exchange
//#			   Thomas Weise <weise&vs.uni-kassel.de> April 2006
//smc-jmx         6786/tcp   Sun Java Web Console JMX
//smc-jmx         6786/udp   Sun Java Web Console JMX
//smc-admin       6787/tcp   Sun Web Console Admin
//smc-admin       6787/udp   Sun Web Console Admin
//#                          Bill Edwards <bill.edwards&sun.com> August 2005
//smc-http        6788/tcp   SMC-HTTP
//smc-http        6788/udp   SMC-HTTP
//#                          Ratnadeep Bhattacharjee <ratnadeep.bhattacharjee&sun.com> November 2002
//smc-https       6789/tcp   SMC-HTTPS
//smc-https       6789/udp   SMC-HTTPS
//#                          Ratnadeep Bhattacharjee <ratnadeep.bhattacharjee&sun.com> August 2002
//hnmp            6790/tcp   HNMP
//hnmp            6790/udp   HNMP
//#                          Jude George <jude&nas.nasa.gov>
//hnm             6791/tcp   Halcyon Network Manager
6791,//hnm             6791/udp   Halcyon Network Manager
//#                          Richard Harriss <richard.harriss&halcyonsoftware.com> May 2005
//#               6792-6800  Unassigned
6801,//acnet		6801/tcp   ACNET Control System Protocol
6801,//acnet		6801/udp   ACNET Control System Protocol
//#			   Rich Neswold <neswold&fnal.gov> February 2007
//#               6802-6830  Unassigned
6831,//ambit-lm        6831/tcp   ambit-lm
6831,//ambit-lm        6831/udp   ambit-lm
//#                          Don Hejna <djhejna&ambit.com>
//#               6832-6840  Unassigned
6841,//netmo-default	6841/tcp   Netmo Default
//netmo-default	6841/udp   Netmo Default
//netmo-http	6842/tcp   Netmo HTTP
6842,//netmo-http	6842/udp   Netmo HTTP
//#			   Urs Bertschinger <urs&netmosphere.com>
//#               6843-6849   Unassigned 
6850,//iccrushmore     6850/tcp    ICCRUSHMORE
6850,//iccrushmore     6850/udp    ICCRUSHMORE
//#                           Dave Hubbard <dave&icc.net>
//#               6851-6887   Unassigned
6888,//muse            6888/tcp    MUSE
6888,//muse            6888/udp    MUSE
//#                           Muse Communications Corporation
//#                           <howard&muse3d.com>
//#               6889-6935   Unassigned
6936,//xsmsvc		6936/tcp    XenSource Management Service
//xsmsvc		6936/udp    XenSource Management Service
6936,//#			    Roger Klorese <roger&xensource.com> June 2006
//#               6937-6945   Unassigned
6946,//bioserver       6946/tcp    Biometrics Server
6946,//bioserver       6946/udp    Biometrics Server
//#			    ISHII AKIO <ishii.akio&jp.fujitsu.com> January 2006
//#               6947-6950   Unassigned
6951,//otlp		6951/tcp    OTLP
6951,//otlp		6951/udp    OTLP
//#			    Brent Foster <brent.foster&onstreamsystems.com> April 2006
//#               6952-6960   Unassigned
6961,//jmact3          6961/tcp    JMACT3
//jmact3          6961/udp    JMACT3
//jmevt2          6962/tcp    jmevt2
//jmevt2          6962/udp    jmevt2
//swismgr1        6963/tcp    swismgr1
//swismgr1    	6963/udp    swismgr1
//swismgr2        6964/tcp    swismgr2
//swismgr2        6964/udp    swismgr2
//swistrap        6965/tcp    swistrap
//swistrap        6965/udp    swistrap
//swispol         6966/tcp    swispol
6966,//swispol         6966/udp    swispol
//#                           Yutaka Ono <ono&saint.nm.fujitsu.co.jp>
//#               6967-6968   Unassigned
6969,//acmsoda         6969/tcp    acmsoda
6969,//acmsoda         6969/udp    acmsoda
//#                           Daniel Simms <dsimms&acm.uiuc.edu>
//#               6970-6996   Unassigned
6997,//MobilitySrv	6997/tcp    Mobility XE Protocol
//MobilitySrv	6997/udp    Mobility XE Protocol
//#			    Joseph T Savarese <joesa&nmwco.com> June 2007
//iatp-highpri	6998/tcp    IATP-highPri
//iatp-highpri	6998/udp    IATP-highPri
//iatp-normalpri	6999/tcp    IATP-normalPri
//iatp-normalpri	6999/udp    IATP-normalPri
//#                           John Murphy <john.m.murphy&mci.com>
//afs3-fileserver 7000/tcp    file server itself
//afs3-fileserver 7000/udp    file server itself
//afs3-callback   7001/tcp    callbacks to cache managers
//afs3-callback   7001/udp    callbacks to cache managers
//afs3-prserver   7002/tcp    users & groups database
//afs3-prserver   7002/udp    users & groups database
//afs3-vlserver   7003/tcp    volume location database
//afs3-vlserver   7003/udp    volume location database
//afs3-kaserver   7004/tcp    AFS/Kerberos authentication service
//afs3-kaserver   7004/udp    AFS/Kerberos authentication service
//afs3-volser     7005/tcp    volume managment server
//afs3-volser     7005/udp    volume managment server
//afs3-errors     7006/tcp    error interpretation service
//afs3-errors     7006/udp    error interpretation service
//afs3-bos        7007/tcp    basic overseer process
//afs3-bos        7007/udp    basic overseer process
//afs3-update     7008/tcp    server-to-server updater
//afs3-update     7008/udp    server-to-server updater
//afs3-rmtsys     7009/tcp    remote cache manager service
//afs3-rmtsys     7009/udp    remote cache manager service
//#
//ups-onlinet     7010/tcp    onlinet uninterruptable power supplies
//ups-onlinet     7010/udp    onlinet uninterruptable power supplies
//#                           Jim Thompson <jim.thompson&powerware.com>
//talon-disc      7011/tcp    Talon Discovery Port
//talon-disc      7011/udp    Talon Discovery Port
//talon-engine    7012/tcp    Talon Engine
//talon-engine    7012/udp    Talon Engine
//microtalon-dis  7013/tcp    Microtalon Discovery
//microtalon-dis  7013/udp    Microtalon Discovery
//microtalon-com  7014/tcp    Microtalon Communications
//microtalon-com  7014/udp    Microtalon Communications
//talon-webserver 7015/tcp    Talon Webserver
7015,//talon-webserver 7015/udp    Talon Webserver
//#                           Jim Thompson <jim.thompson&powerware.com>
//#               7016-7019   Unassigned
7020,//dpserve         7020/tcp    DP Serve
//dpserve         7020/udp    DP Serve
//dpserveadmin    7021/tcp    DP Serve Admin
//dpserveadmin    7021/udp    DP Serve Admin
//#                           Allan Stanley <allan&hummingbird.com>
//ctdp            7022/tcp    CT Discovery Protocol
//ctdp            7022/udp    CT Discovery Protocol
//#                           James Kirkwood <james.kirkwood&controltechniques.com> June 2005
//ct2nmcs         7023/tcp    Comtech T2 NMCS
//ct2nmcs         7023/udp    Comtech T2 NMCS
//#                           Bryan Wilcutt <bwilcutt&comtechefdata.com> June 2005
//vmsvc           7024/tcp    Vormetric service
//vmsvc           7024/udp    Vormetric service
//#                           Tom Boyle <tboyle&vormetric.com> June 2005
//vmsvc-2         7025/tcp    Vormetric Service II
7025,//vmsvc-2         7025/udp    Vormetric Service II
//#                           Tom Boyle <tboyle&vormetric.com> June 2005
//#               7026-7029   Unassigned
7030,//op-probe        7030/tcp    ObjectPlanet probe
7030,//op-probe        7030/udp    ObjectPlanet probe
//#                           Bjorn Jarle Kvande <bjorn&objectplanet.com> April 2002
//#               7031-7069   Unassigned
7070,//arcp            7070/tcp    ARCP
7070,//arcp            7070/udp    ARCP
//#                           Jude George <jude&nas.nasa.gov>
//#               7071-7079   Unassigned
7080,//empowerid       7080/tcp    EmpowerID Communication
7080,//empowerid       7080/udp    EmpowerID Communication
//#                           Matthew Whited <matt&thedotnetfactory.com> 16 January 2008
//#               7081-7098   Unassigned
7099,//lazy-ptop       7099/tcp    lazy-ptop
//lazy-ptop       7099/udp    lazy-ptop
//#                           Guy Keren <Guy_Keren&mail.stil.scitex.com>
//font-service    7100/tcp    X Font Service
//font-service    7100/udp    X Font Service
//#                           Stephen Gildea <gildea&lcs.mit.edu>
//elcn		7101/tcp    Embedded Light Control Network
//elcn		7101/udp    Embedded Light Control Network
7101,//#			    Michael Scarito <ms&mit.edu> February 2007
//#               7102-7120   Unassigned
7121,//virprot-lm      7121/tcp    Virtual Prototypes License Manager
7121,//virprot-lm      7121/udp    Virtual Prototypes License Manager
//#                           Victor Galis <galis&satchmo.virtualprototypes.ca>
//#               7122-7127   Unassigned
7128,//scenidm		7128/tcp    intelligent data manager 
//scenidm		7128/udp    intelligent data manager 
//#			    Paul Ignatius <paul.ignatius&scentric.com> March 2006
//scenccs		7129/tcp    Catalog Content Search
7129,//scenccs		7129/udp    Catalog Content Search
//#			    Anil Sharma <anil.sharma&scentric.com> April 2006
//#               7130-7160   Unassigned
7161,//cabsm-comm      7161/tcp    CA BSM Comm
//cabsm-comm      7161/udp    CA BSM Comm
//#                           Chun-Ho Chang <chun-ho.chang&ca.com> November 2004
//caistoragemgr   7162/tcp    CA Storage Manager
//caistoragemgr   7162/udp    CA Storage Manager
//#                           Emre Tunar <emre.tunar&ca.com> November 2004
//cacsambroker    7163/tcp    CA Connection Broker
//cacsambroker    7163/udp    CA Connection Broker
//#                           David Roberts <David.Roberts&ca.com> May 2005
//fsr		7164/tcp    File System Repository Agent
//fsr		7164/udp    File System Repository Agent
//#			    Micha Ben-Efraim <benmi07&ca.com> 19 July 2007
//doc-server      7165/tcp    Document WCF Server
//doc-server      7165/udp    Document WCF Server
//aruba-server    7166/tcp    Aruba eDiscovery Server
7166,//aruba-server    7166/udp    Aruba eDiscovery Server
//#                           Micha Ben-Efraim <benmi07&ca.com> 07 January 2008              
//#               7167-7173   Unassigned
7174,//clutild         7174/tcp    Clutild
7174,//clutild         7174/udp    Clutild
//#                           Cheryl Stoutenburg <cstoutenburg&vnet.ibm.com>
//#               7175-7199   Unassigned
7200,//fodms           7200/tcp    FODMS FLIP  
//fodms           7200/udp    FODMS FLIP  
//#                           David Anthony <anthony&power.amasd.anatcp.rockwell.com>
//dlip            7201/tcp    DLIP
7201,//dlip            7201/udp    DLIP
//#                           Albert Manfredi <manfredi&engr05.comsys.rockwell.com>
//#               7202-7226   Unassigned
7227,//ramp            7227/tcp    Registry A & M Protocol
7227,//ramp            7227/udp    Registry A $ M Protocol 
//#                           John Havard <jh&hxe.us> November 2003
//#               7228-7261   Unassigned
7262,//cnap            7262/tcp    Calypso Network Access Protocol
7262,//cnap            7262/udp    Calypso Network Access Protocol
//#                           Scott Halberg <eng&calypsosystems.com> 02 June 2009
//#               7263-7271   Unassigned
7272,//watchme-7272    7272/tcp    WatchMe Monitoring 7272
//watchme-7272    7272/udp    WatchMe Monitoring 7272
//#                           Oliver Heinz <heinz&arago.de> August 2005
//oma-rlp         7273/tcp    OMA Roaming Location 
//oma-rlp         7273/udp    OMA Roaming Location 
//oma-rlp-s       7274/tcp    OMA Roaming Location SEC
//oma-rlp-s       7274/udp    OMA Roaming Location SEC
//#                           Larry A. Young <Larry.A.Young&mail.Sprint.com> August 2005
//oma-ulp         7275/tcp    OMA UserPlane Location
//oma-ulp         7275/udp    OMA UserPlane Location
//#			    Larry A. Young <Larry.A.Young&Sprint.com> February 2006
//oma-ilp		7276/tcp    OMA Internal Location Protocol
//oma-ilp		7276/udp    OMA Internal Location Protocol
//oma-ilp-s	7277/tcp    OMA Internal Location Secure Protocol
//oma-ilp-s	7277/udp    OMA Internal Location Secure Protocol
//#			    Khiem Tran <Khiem.Tran&Andrew.com> 06 November 2007
//oma-dcdocbs     7278/tcp    OMA Dynamic Content Delivery over CBS
//oma-dcdocbs     7278/udp    OMA Dynamic Content Delivery over CBS
//#                           Avi Primo <aprimo&celltick.com> 29 January 2008
//ctxlic          7279/tcp    Citrix Licensing
//ctxlic          7279/udp    Citrix Licensing
//#                           Marc Binstock <marc.binstock&citrix.com> 29 January 2008
//itactionserver1 7280/tcp    ITACTIONSERVER 1
//itactionserver1 7280/udp    ITACTIONSERVER 1
//itactionserver2 7281/tcp    ITACTIONSERVER 2
//itactionserver2 7281/udp    ITACTIONSERVER 2
//#                           Brian Taylor <btaylor&imagetag.com>
//mzca-action     7282/tcp    eventACTION/ussACTION (MZCA) server
//#                           Gord Tomlin <gord.tomlin&actionsoftware.com> 30 January 2009
7282,//#               7282/udp    Reserved
//#               7283-7299   Unassigned 
7300,//swx             7300-7359   The Swiss Exchange
7359,//#                           Edgar Blum <edgar.blum&swx.ch>
//#		7360-7364   Unassigned (Removed on 2006-2-06)
7365,//lcm-server      7365/tcp    LifeKeeper Communications 
7365,//lcm-server      7365/udp    LifeKeeper Communications 
//#			    James Bottomley <James.Bottomley&SteelEye.com> February 2006
//#		7366-7390   Unassigned (Removed on 2006-2-06)
7391,//mindfilesys     7391/tcp    mind-file system server
//mindfilesys     7391/udp    mind-file system server
//mrssrendezvous  7392/tcp    mrss-rendezvous server
//mrssrendezvous  7392/udp    mrss-rendezvous server
//#                           Dave Porter <porter&mango.com>   
//nfoldman        7393/tcp    nFoldMan Remote Publish
//nfoldman        7393/udp    nFoldMan Remote Publish
//#			    Richard McDonald <ve3nvm&spamcop.net> January 2006
//fse		7394/tcp    File system export of backup images
//fse		7394/udp    File system export of backup images
//#			    Weibao Wu <weibao_wu&symantec.com> April 2006
//winqedit        7395/tcp    winqedit
7395,//winqedit        7395/udp    winqedit
//#                           David Greer <david_greer&robelle.com>
//#               7396        Unassigned
7396,//hexarc          7397/tcp    Hexarc Command Language
7397,//hexarc          7397/udp    Hexarc Command Language
//#                           George Moromisato <gpm&neurohack.com> November 2004
//#               7398-7399   Unassigned
7400,//rtps-discovery  7400/tcp    RTPS Discovery
//rtps-discovery  7400/udp    RTPS Discovery
//rtps-dd-ut      7401/tcp    RTPS Data-Distribution User-Traffic
//rtps-dd-ut      7401/udp    RTPS Data-Distribution User-Traffic
//rtps-dd-mt      7402/tcp    RTPS Data-Distribution Meta-Traffic
7402,//rtps-dd-mt      7402/udp    RTPS Data-Distribution Meta-Traffic
//#                           Gerardo Pardo-Castellote <gerardo.pardo&rti.com> October 2005
//#               7403-7409   Unassigned
7410,//ionixnetmon	7410/tcp    Ionix Network Monitor
//ionixnetmon	7410/udp    Ionix Network Monitor
//#			    Maxime Deputter <m.deputter&ionixhosting.com> April 2006
//#               7411-7420   Unassigned
7421,//mtportmon       7421/tcp    Matisse Port Monitor
7421,//mtportmon       7421/udp    Matisse Port Monitor
//#                           Didier Cabannes <Didier&matisse.com> November 2004
//#               7422-7425   Unassigned
7426,//pmdmgr          7426/tcp    OpenView DM Postmaster Manager
//pmdmgr          7426/udp    OpenView DM Postmaster Manager
//oveadmgr        7427/tcp    OpenView DM Event Agent Manager
//oveadmgr        7427/udp    OpenView DM Event Agent Manager
//ovladmgr        7428/tcp    OpenView DM Log Agent Manager
//ovladmgr        7428/udp    OpenView DM Log Agent Manager
//opi-sock        7429/tcp    OpenView DM rqt communication
//opi-sock        7429/udp    OpenView DM rqt communication
//xmpv7           7430/tcp    OpenView DM xmpv7 api pipe
//xmpv7           7430/udp    OpenView DM xmpv7 api pipe
//pmd             7431/tcp    OpenView DM ovc/xmpv3 api pipe
//pmd             7431/udp    OpenView DM ovc/xmpv3 api pipe
//#                           Dave Lamb <rdl&rdl.cnd.hp.com>
//faximum         7437/tcp    Faximum
7437,//faximum         7437/udp    Faximum
//#                           George Pajari <George.Pajari&faximum.com>
//#               7438-7442   Unassigned
7443,//oracleas-https  7443/tcp    Oracle Application Server HTTPS
7443,//oracleas-https  7443/udp    Oracle Application Server HTTPS
//#			    David McMarlin <david.mcmarlin&oracle.com> August 2006
//#               7444-7472   Unassigned
7473,//rise		7473/tcp    Rise: The Vieneo Province
7473,//rise		7473/udp    Rise: The Vieneo Province
//#			    Jason Reskin <iana&unistellar.com> March 2007
//#               7474-7490   Unassigned
7491,//telops-lmd      7491/tcp    telops-lmd
7491,//telops-lmd      7491/udp    telops-lmd
//#                           David Spencer <dspencer&telops.com>
//#               7492-7499   Unassigned
7500,//silhouette      7500/tcp    Silhouette User
//silhouette      7500/udp    Silhouette User
//#                           Anthony Payne <opayne&pacbell.net> February 2004    
//ovbus           7501/tcp    HP OpenView Bus Daemon
7501,//ovbus           7501/udp    HP OpenView Bus Daemon
//#                           David M. Rhodes <davidrho&cnd.hp.com>
//#               7502-7509   Unassigned
7510,//ovhpas          7510/tcp    HP OpenView Application Server
//ovhpas          7510/udp    HP OpenView Application Server
//#                           Jeff Conrad <jeff_conrad&hp.com>
//pafec-lm        7511/tcp    pafec-lm
7511,//pafec-lm        7511/udp    pafec-lm
//#                           Billy Dhillon <bdsos&pafec.co.uk>
//#               7512-7541   Unassigned
7542,//saratoga	7542/tcp    Saratoga Transfer Protocol
//saratoga	7542/udp    Saratoga Transfer Protocol
//#			    Lloyd Wood <lwood&cisco.com> May 2007
//atul            7543/tcp    atul server
//atul            7543/udp    atul server
//#			    Mark Stapp <mjs&cisco.com> January 2006
//nta-ds          7544/tcp    FlowAnalyzer DisplayServer
//nta-ds          7544/udp    FlowAnalyzer DisplayServer
//nta-us          7545/tcp    FlowAnalyzer UtilityServer
//nta-us          7545/udp    FlowAnalyzer UtilityServer
//#                           Fred Messinger <fredm&cisco.com>
//cfs             7546/tcp    Cisco Fabric service
//cfs             7546/udp    Cisco Fabric service
//#                           Rituparna Agrawal <riagrawa&cisco.com> September 2005
//cwmp            7547/tcp    DSL Forum CWMP 
//cwmp            7547/udp    DSL Forum CWMP 
//#                           Anton Okmianski <aokmians&cisco.com> January 2006
//tidp		7548/tcp    Threat Information Distribution Protocol 
//tidp		7548/udp    Threat Information Distribution Protocol 
//#			    Chui-Tin Yen <tin&cisco.com> February 2006
//nls-tl		7549/tcp    Network Layer Signaling Transport Layer
7549,//nls-tl		7549/udp    Network Layer Signaling Transport Layer
//#			    Melinda Shore <mshore&cisco.com> May 2006
//#               7550-7559   Unassigned
7560,//sncp            7560/tcp    Sniffer Command Protocol
7560,//sncp            7560/udp    Sniffer Command Protocol
//#                           Dominick Cafarelli <dominick.cafarelli&networkgeneral.com> August 2005
//#               7561-7565   Unassigned
7566,//vsi-omega       7566/tcp    VSI Omega	
7566,//vsi-omega       7566/udp    VSI Omega
//#                           Curtis Smith <curtis.smith&vsin.com>
//#               7567-7569   Unassigned
7570,//aries-kfinder   7570/tcp    Aries Kfinder
7570,//aries-kfinder   7570/udp    Aries Kfinder
//#                           James King, III <jking&ariessys.com>
//#               7571-7587   Unassigned
7588,//sun-lm          7588/tcp    Sun License Manager
7588,//sun-lm          7588/udp    Sun License Manager
//#                           Sophie Deng <Sophie.Deng&Eng.Sun.COM>
//#               7589-7623   Unassigned
7624,//indi            7624/tcp    Instrument Neutral Distributed Interface
7624,//indi            7624/udp    Instrument Neutral Distributed Interface
//#                           Elwood Downey <ecdowney&clearskyinstitute.com> April 2002
//#               7625        Unassigned
7626,//simco           7626/tcp    SImple Middlebox COnfiguration (SIMCO) Server
//#                           RFC4540
//#               7626/udp    De-registered (30 January 2006)
//simco           7626/sctp   SImple Middlebox COnfiguration (SIMCO)
//#			    Sebastian Kiesel <kiesel&ikr.uni-stuttgart.de> January 2006
//soap-http       7627/tcp    SOAP Service Port
//soap-http       7627/udp    SOAP Service Port
//#                           Donald Dylla <donald.dylla&hp.com> December 2004
//zen-pawn	7628/tcp    Primary Agent Work Notification
//zen-pawn	7628/udp    Primary Agent Work Notification
//#			    Ty Ellis <tellis&novell.com> May 2006
//xdas		7629/tcp    OpenXDAS Wire Protocol
7629,//xdas		7629/udp    OpenXDAS Wire Protocol
//#			    John Calcote <jcalcote&novell.com> October 2006
//#               7630-7632   Unassigned 
7633,//pmdfmgt         7633/tcp    PMDF Management
7633,//pmdfmgt         7633/udp    PMDF Management
//#                           Hunter Goatley <goathunter&goatley.com>
//#               7634-7647   Unassigned
7648,//cuseeme		7648/tcp    bonjour-cuseeme
7648,//cuseeme		7648/udp    bonjour-cuseeme
//#			    Marc Manthey <codewarrior&cuseeme.de> July 2006
//#               7649-7671   Unassigned
7672,//imqstomp        7672/tcp    iMQ STOMP Server
//#                           Amy Kang <amy.kang&sun.com> 10 March 2009
//#               7672/udp    Reserved
//imqstomps       7673/tcp    iMQ STOMP Server over SSL
//#                           Amy Kang <amy.kang&sun.com> 10 March 2009
//#               7673/udp    Reserved
//imqtunnels      7674/tcp    iMQ SSL tunnel
//imqtunnels      7674/udp    iMQ SSL tunnel
//imqtunnel       7675/tcp    iMQ Tunnel
//imqtunnel       7675/udp    iMQ Tunnel
//#                           Shailesh S. Bavadekar <shailesh.bavadekar&sun.com> April 2002
//imqbrokerd      7676/tcp    iMQ Broker Rendezvous
//imqbrokerd      7676/udp    iMQ Broker Rendezvous
//#                           Joseph Di Pol <joe.dipol&sun.com> April 2002
//sun-user-https  7677/tcp    Sun App Server - HTTPS
7677,//sun-user-https  7677/udp    Sun App Server - HTTPS
//#                           Abhijit Kumar <as-iana-ports&sun.com> November 2005
//#               7678-7679   Unassigned
7680,//pando-pub       7680/tcp    Pando Media Public Distribution
7680,//pando-pub       7680/udp    Pando Media Public Distribution
//#                           Laird Popkin <laird&pando.com> 27 February 2008
//#               7681-7688   Unassigned
7689,//collaber	7689/tcp    Collaber Network Service
7689,//collaber	7689/udp    Collaber Network Service
//#			    Rajesh Akkineni <rajesh&vimukti.com> January 2007
//#               7690-7696   Unassigned
7697,//klio            7697/tcp    KLIO communications
7697,//klio            7697/udp    KLIO communications
//#                           Helmut Giritzer <helmut.giritzer&o.roteskreuz.at> August 2005
//#               7698-7699   Unassigned
7700,//em7-secom       7700/tcp    EM7 Secure Communications
7700,//#                           Christopher Cordray <ccordray&sciencelogic.com> 05 June 2008
//#               7700/udp    Reserved
//#               7701-7706   Unassigned
7707,//sync-em7        7707/tcp    EM7 Dynamic Updates
//sync-em7        7707/udp    EM7 Dynamic Updates
//#                           Christopher Cordray <ccordray&sciencelogic.com> November 2004
//scinet          7708/tcp    scientia.net
7708,//scinet          7708/udp    scientia.net
//#			    Christoph Anton Mitterer <calestyo&scientia.net> January 2006
//#               7709-7719   Unassigned
7720,//medimageportal  7720/tcp    MedImage Portal
7720,//medimageportal  7720/udp    MedImage Portal
//#                           Robert Helton <bob_helton&medimage.com> October 2003
//#               7721-7723   Unassigned
7724,//nsdeepfreezectl 7724/tcp    Novell Snap-in Deep Freeze Control
//nsdeepfreezectl 7724/udp    Novell Snap-in Deep Freeze Control
//#                           David Crowe <dcrowe&faronics.com> 07 January 2008
//nitrogen        7725/tcp    Nitrogen Service
//nitrogen        7725/udp    Nitrogen Service
//#                           Randy Lomnes <rlomnes&faronics.com> November 2004
//freezexservice  7726/tcp    FreezeX Console Service
//freezexservice  7726/udp    FreezeX Console Service
//#                           David Crowe <dcrowe&faronics.com> June 2005
//trident-data    7727/tcp    Trident Systems Data
7727,//trident-data    7727/udp    Trident Systems Data
//#                           Jeremy McClintock <jeremy&tridsys.com>  August 2005
//#               7728-7733   Unassigned
7734,//smip		7734/tcp    Smith Protocol over IP
7734,//smip		7734/udp    Smith Protocol over IP
//#			    Jim Pettinato <jim_pettinato&fmcti.com> April 2007
//#               7735-7737   Unassigned
7738,//aiagent         7738/tcp    HP Enterprise Discovery Agent
7738,//aiagent         7738/udp    HP Enterprise Discovery Agent
//#                           Matthew Darwin <matthew.darwin&hp.com> August 2005
//#               7739-7741   Unassigned
7742,//msss            7742/tcp    Mugginsoft Script Server Service
//#                           Jonathan Mitchell <jonathan&mugginsoft.com> 08 September 2008
//#               7742/udp    Reserved
//sstp-1          7743/tcp    Sakura Script Transfer Protocol
//sstp-1          7743/udp    Sakura Script Transfer Protocol
//#                           Kouichi Takeda <KHBO5271&nifty.com>
//raqmon-pdu      7744/tcp    RAQMON PDU
7744,//raqmon-pdu      7744/udp    RAQMON PDU
//#                           RFC4712
//#               7745-7746   Unassigned
7747,//prgp            7747/tcp    Put/Run/Get Protocol
7747,//prgp            7747/udp    Put/Run/Get Protocol
//#                           Jayasooriah <jayasooriah&cast.com.au> 22 February 2008
//#               7748-7776   Unassigned
7777,//cbt             7777/tcp    cbt
//cbt             7777/udp    cbt
//#                           Tony Ballardie <A.Ballardie&cs.ucl.ac.uk>
//interwise       7778/tcp    Interwise
//interwise       7778/udp    Interwise
//#                           Joseph Gray <gray&interwise.co.il>
//vstat           7779/tcp    VSTAT
7779,//vstat           7779/udp    VSTAT
//#                           Vinh Nguyn <vinh&sportvision.com>
//#               7780        Unassigned
7781,//accu-lmgr       7781/tcp    accu-lmgr
7781,//accu-lmgr       7781/udp    accu-lmgr
//#                           Moises E. Hernandez <moises&accugraph.com>
//#               7782-7785   Unassigned
7786,//minivend        7786/tcp    MINIVEND
//minivend        7786/udp    MINIVEND
//#                           Mike Heins <mike&minivend.com>
//popup-reminders 7787/tcp    Popup Reminders Receive
7787,//popup-reminders 7787/udp    Popup Reminders Receive 
//#			    Robert Harvey <robert&officetoolspro.com> January 2006
//#               7788        Unassigned
7789,//office-tools    7789/tcp    Office Tools Pro Receive
7789,//office-tools    7789/udp    Office Tools Pro Receive
//#			    Robert Harvey <robert&officetoolspro.com> January 2006
//#               7790-7793   Unassigned
7794,//q3ade           7794/tcp    Q3ADE Cluster Service
7794,//q3ade           7794/udp    Q3ADE Cluster Service
//#                           Uffe Harksen <uh&uhcommunications.com> August 2005
//#               7795-7796   Unassigned
7797,//pnet-conn       7797/tcp    Propel Connector port
//pnet-conn       7797/udp    Propel Connector port
//pnet-enc        7798/tcp    Propel Encoder port
//pnet-enc        7798/udp    Propel Encoder port
//#                           Leif Hedstrom <leif&propel.com> April 2002
//altbsdp		7799/tcp    Alternate BSDP Service
//altbsdp		7799/udp    Alternate BSDP Service
//#			    Dieter Siegmund <dieter&apple.com> 22 October 2007
//asr		7800/tcp    Apple Software Restore
//asr		7800/udp    Apple Software Restore
//#			    Jim Kateley <asr-dev&group.apple.com> January 2006
//ssp-client	7801/tcp    Secure Server Protocol - client
7801,//ssp-client	7801/udp    Secure Server Protocol - client
//#			    Rick Macchio <rmacchio&juniper.net> November 2006
//#               7802-7809   Unassigned
7810,//rbt-wanopt	7810/tcp    Riverbed WAN Optimization Protocol
7810,//rbt-wanopt	7810/udp    Riverbed WAN Optimization Protocol
//#			   Vladimir Legalov <vlegalov&riverbed.com> 04 September 2007
//#               7811-7844   Unassigned
7845,//apc-7845        7845/tcp    APC 7845
//apc-7845        7845/udp    APC 7845
//apc-7846        7846/tcp    APC 7846
7846,//apc-7846        7846/udp    APC 7846
//#                           American Power Conversion <ports&apcc.com>
//#               7847-7868   Unassigned
7869,//mobileanalyzer  7869/tcp    MobileAnalyzer& MobileMonitor
//#                           Jonas Gyllensvaan <jonas&conceivium.com> 27 April 2009
//#               7869/udp    Reserved    
//rbt-smc         7870/tcp    Riverbed Steelhead Mobile Service
//#                           Gabriel Levy <glevy&riverbed.com> 29 August 2008
7870,//#               7870/udp    Reserved
//#               7871-7879   Unassigned
7880,//pss             7880/tcp    Pearson
7880,//pss             7880/udp    Pearson
//#                           Pearson <chad.smith&pearson.com> 17 January 2008
//#               7881-7886   Unassigned
7887,//ubroker         7887/tcp    Universal Broker
7887,//ubroker         7887/udp    Universal Broker
//#                           Nathan Hammond <nathan.hammond&stonebranch.com> October 2005
//#               7888-7899   Unassigned
7900,//mevent		7900/tcp    Multicast Event
//mevent		7900/udp    Multicast Event
//#			    YoonSoo Kim <ys71.kim&samsung.com> May 2006
//tnos-sp         7901/tcp    TNOS Service Protocol
//tnos-sp         7901/udp    TNOS Service Protocol
//tnos-dp         7902/tcp    TNOS shell Protocol
//tnos-dp         7902/udp    TNOS shell Protocol
//tnos-dps        7903/tcp    TNOS Secure DiaguardProtocol
7903,//tnos-dps        7903/udp    TNOS Secure DiaguardProtocol
//#                           Rene Kurt <rene.kurt&adasoft.ch> August 2005
//#               7904-7912   Unassigned
7913,//qo-secure       7913/tcp    QuickObjects secure port
7913,//qo-secure       7913/udp    QuickObjects secure port
//#                           Jonas Bovin <jonas.bovin&quickobjects.com>  
//#               7914-7931   Unassigned
7932,//t2-drm          7932/tcp    Tier 2 Data Resource Manager
//t2-drm          7932/udp    Tier 2 Data Resource Manager
//t2-brm          7933/tcp    Tier 2 Business Rules Manager
7933,//t2-brm          7933/udp    Tier 2 Business Rules Manager
//#                           Peter Carlson <pcarlson&tier2.com>
//#               7934-7966   Unassigned
7967,//supercell       7967/tcp    Supercell
7967,//supercell       7967/udp    Supercell
//#                           Kevin Nakagawa <nakagawa&sigsci.com>
//#               7968-7978   Unassigned     
7979,//micromuse-ncps  7979/tcp    Micromuse-ncps
//micromuse-ncps  7979/udp    Micromuse-ncps
//#                           Hing Wing To <wing.to&mircromuse.com>
//quest-vista     7980/tcp    Quest Vista
7980,//quest-vista     7980/udp    Quest Vista
//#                           Preston Bannister <pbannister&quests.com>
//#               7981-7998   Unassigned
7999,//irdmi2          7999/tcp    iRDMI2
//irdmi2          7999/udp    iRDMI2
//irdmi           8000/tcp    iRDMI
//irdmi           8000/udp    iRDMI
//#                           Gil Shafriri <shafriri&ilccm1.iil.intel.com>
//vcom-tunnel	8001/tcp    VCOM Tunnel
//vcom-tunnel	8001/udp    VCOM Tunnel
//#			    Mark Lewandowski <mlewan0&us.ibm.com>
//teradataordbms	8002/tcp    Teradata ORDBMS
//teradataordbms	8002/udp    Teradata ORDBMS
//#			    Curt Ellmann <curt.ellmann&ncr.com>
//mcreport        8003/tcp    Mulberry Connect Reporting Service
8003,//mcreport        8003/udp    Mulberry Connect Reporting Service
//#                           Dave Stoneham <dave&mulberry-consultants.co.uk> 10 March 2008
//#               8004        Unassigned 
8005,//mxi		8005/tcp    MXI Generation II for z/OS
8005,//mxi		8005/udp    MXI Generation II for z/OS
//#			    Rob Scott <rscott&rs.com> May 2007
//#               8006-8007   Unassigned
8008,//http-alt	8008/tcp    HTTP Alternate
8008,//http-alt	8008/udp    HTTP Alternate
//#		            James Gettys <jg&w3.org>
//#               8009-8018   Unassigned
8019,//qbdb            8019/tcp    QB DB Dynamic Port
//qbdb            8019/udp    QB DB Dynamic Port
//#                           Sridhar Krishnamurthy <Sridhar_Krishnamurthy&intuit.com> 15 February 2008
//intu-ec-svcdisc 8020/tcp    Intuit Entitlement Service and Discovery
//intu-ec-svcdisc 8020/udp    Intuit Entitlement Service and Discovery
//intu-ec-client  8021/tcp    Intuit Entitlement Client
//intu-ec-client  8021/udp    Intuit Entitlement Client
//#                           Daniel C. McGloin <daniel_mcgloin&intuit.com> May 2005
//oa-system       8022/tcp    oa-system
8022,//oa-system       8022/udp    oa-system 
//#                           Marie-France Dubreuil <Marie-France.Dubreuil&evidian.com>
//#               8023-8024   Unassigned
8025,//ca-audit-da	8025/tcp    CA Audit Distribution Agent
//ca-audit-da	8025/udp    CA Audit Distribution Agent
//ca-audit-ds	8026/tcp    CA Audit Distribution Server
8026,//ca-audit-ds	8026/udp    CA Audit Distribution Server
//#			    Henning Smith <henning.smith&ca.com> July 2006
//#               8027-8031   Unassigned
8032,//pro-ed		8032/tcp    ProEd
//pro-ed		8032/udp    ProEd
//mindprint	8033/tcp    MindPrint
//mindprint	8033/udp    MindPrint
//#		            Larry Tusoni <larry&goldrush.com>
//vantronix-mgmt  8034/tcp    .vantronix Management
8034,//vantronix-mgmt  8034/udp    .vantronix Management
//#                           Reyk Floeter <reyk&vantronix.net> 27 February 2008
//#               8035-8041   Unassigned
8042,//fs-agent        8042/tcp    FireScope Agent
//#                           Matt Rogers <mrogers&firescope.com> 16 October 2008
//#               8042/udp    Reserved
//fs-server       8043/tcp    FireScope Server
//#                           Matt Rogers <mrogers&firescope.com> 16 October 2008
//#               8043/udp    Reserved
8044,//fs-mgmt         8044/tcp    FireScope Management Interface
//#                           Matt Rogers <mrogers&firescope.com> 16 October 2008
//#               8044/udp    Reserved
//#               8045-8051   Unassigned
8052,//senomix01	8052/tcp    Senomix Timesheets Server
//senomix01	8052/udp    Senomix Timesheets Server
//senomix02	8053/tcp    Senomix Timesheets Client [1 year assignment]
//senomix02	8053/udp    Senomix Timesheets Client [1 year assignment]
//senomix03	8054/tcp    Senomix Timesheets Server [1 year assignment]
//senomix03	8054/udp    Senomix Timesheets Server [1 year assignment]
//senomix04	8055/tcp    Senomix Timesheets Server [1 year assignment]
//senomix04	8055/udp    Senomix Timesheets Server [1 year assignment]
//senomix05	8056/tcp    Senomix Timesheets Server [1 year assignment]
//senomix05	8056/udp    Senomix Timesheets Server [1 year assignment]
//senomix06	8057/tcp    Senomix Timesheets Client [1 year assignment]
//senomix06	8057/udp    Senomix Timesheets Client [1 year assignment]
//senomix07	8058/tcp    Senomix Timesheets Client [1 year assignment]
//senomix07	8058/udp    Senomix Timesheets Client [1 year assignment]
//senomix08	8059/tcp    Senomix Timesheets Client [1 year assignment]
8059,//senomix08	8059/udp    Senomix Timesheets Client [1 year assignment]
//#			    Charles O'Dale <codale&hfx.andara.com> July 2006
//#               8060-8073   Unassigned
8074,//gadugadu	8074/tcp    Gadu-Gadu
8074,//gadugadu	8074/udp    Gadu-Gadu
//#			    Marcin Gozdalik <gozdal&gadu-gadu.pl> May 2006
//#               8075-8079   Unassigned
8080,//http-alt	8080/tcp    HTTP Alternate (see port 80)
//http-alt	8080/udp    HTTP Alternate (see port 80)
//#		            Stephen Casner <casner&precpt.com>
//sunproxyadmin   8081/tcp    Sun Proxy Admin Service
//sunproxyadmin   8081/udp    Sun Proxy Admin Service
//#                           Arvind Srinivasan <arvind.srinivasan&sun.com> August 2005
//us-cli          8082/tcp    Utilistor (Client)
//us-cli          8082/udp    Utilistor (Client)
//us-srv          8083/tcp    Utilistor (Server)
8083,//us-srv          8083/udp    Utilistor (Server)
//#                           Andy Brewerton <andy.brewerton&otium.co.uk> August 2005
//#               8084-8085   Unassigned
8086,//d-s-n           8086/tcp    Distributed SCADA Networking Rendezvous Port
//d-s-n           8086/udp    Distributed SCADA Networking Rendezvous Port
//#                           Gary Hampton <GH&2HTI.com> 27 February 2008
//simplifymedia   8087/tcp    Simplify Media SPP Protocol
//simplifymedia   8087/udp    Simplify Media SPP Protocol
//#                           Emmanuel Saint-Loubert <emmanuel&simplifymedia.com> 08 August 2008
//radan-http      8088/tcp    Radan HTTP
8088,//radan-http      8088/udp    Radan HTTP
//#                           Previous contact: Steve Hay <Steve.Hay&uk.radan.com> April 2002
//#                           Current contact: Steve Hay <SteveHay&planit.com> 13 June 2008
//#               8089-8096   Unassigned
8097,//sac		8097/tcp    SAC Port Id
8097,//sac		8097/udp    SAC Port Id
//#			    Girish Bhat <gbhat&cranite.com> April 2006
//#               8098-8099   Unassigned
8100,//xprint-server   8100/tcp    Xprint Server
//xprint-server   8100/udp    Xprint Server
//#                           John McKernan <John.McKernan&sun.com>
//ldoms-migr      8101/tcp    Logical Domains Migration
//#                           Liam Merwick <ldoms-iana-ports&sun.com> 16 January 2009
//#               8101/udp    Reserved
//#               8102-8114   Unassigned
//mtl8000-matrix  8115/tcp    MTL8000 Matrix
//mtl8000-matrix  8115/udp    MTL8000 Matrix
//#                           David Pinch <dpinch&mtl-inst.com> April 2002
//cp-cluster      8116/tcp    Check Point Clustering
8116,//cp-cluster      8116/udp    Check Point Clustering
//#                           Roni Moshitzky <rmosh&checkpoint.com>
//#               8117        Unassigned
8118,//privoxy         8118/tcp    Privoxy HTTP proxy
8118,//privoxy         8118/udp    Privoxy HTTP proxy
//#                           Andreas Oesterhelt <oes&privoxy.org> June 2002
//#               8119-8120   Unassigned
8121,//apollo-data     8121/tcp    Apollo Data Port
//apollo-data     8121/udp    Apollo Data Port
//#                           Anthony Carrabino <anthonyc&vistasoftware.com> August 2003
//apollo-admin    8122/tcp    Apollo Admin Port
8122,//apollo-admin    8122/udp    Apollo Admin Port
//#                           Anthony Carrabino <anthonyc&vistasoftware.com> August 2003
//#               8123-8127   Unassigned
8128,//paycash-online  8128/tcp    PayCash Online Protocol
//paycash-online  8128/udp    PayCash Online Protocol
//paycash-wbp     8129/tcp    PayCash Wallet-Browser
//paycash-wbp     8129/udp    PayCash Wallet-Browser
//#                           MegaZone <megazone&paycash.us> August 2005
//indigo-vrmi     8130/tcp    INDIGO-VRMI
//indigo-vrmi     8130/udp    INDIGO-VRMI
//indigo-vbcp     8131/tcp    INDIGO-VBCP
//indigo-vbcp     8131/udp    INDIGO-VBCP
//#                           Colin Caughie <cfc&indigo-avs.com>
//dbabble         8132/tcp    dbabble
8132,//dbabble	        8132/udp    dbabble
//#                           Chris Pugmire <chrisp&netwinsite.com>        
//#               8133-8147   Unassigned
8148,//isdd            8148/tcp    i-SDD file transfer
8148,//isdd            8148/udp    i-SDD file transfer
//#                           Frank Waarsenburg <frank&eye-display.nl> November 2004
//#               8149-8159   Unassigned
8160,//patrol		8160/tcp    Patrol
//patrol		8160/udp    Patrol
//patrol-snmp	8161/tcp    Patrol SNMP
8161,//patrol-snmp	8161/udp    Patrol SNMP
//#			    Portnoy Boxman <portnoy_boxman&bmc.com>
//#               8162-8191   Unassigned
8192,//spytechphone	8192/tcp    SpyTech Phone Service
8192,//spytechphone	8192/udp    SpyTech Phone Service
//#			    Bill Kay <bkay&spy-tec.com> April 2006
//#               8193        Unassigned
8194,//blp1		8194/tcp    Bloomberg data API
//blp1		8194/udp    Bloomberg data API
//blp2		8195/tcp    Bloomberg feed 
8195,//blp2		8195/udp    Bloomberg feed 
//#			    Albert Hou <ahou1&bloomberg.com> May 2006
//#               8196-8198   Unassigned
8199,//vvr-data        8199/tcp    VVR DATA
//vvr-data        8199/udp    VVR DATA
//#                           Ming Xu <ming&veritas.com>
//trivnet1	8200/tcp    TRIVNET
//trivnet1	8200/udp    TRIVNET
//trivnet2  	8201/tcp    TRIVNET
8201,//trivnet2	8201/udp    TRIVNET
//#			                Saar Wilf <saar&trivnet.com>
//#               8202-8203   Unassigned
8204,//lm-perfworks	8204/tcp    LM Perfworks
//lm-perfworks	8204/udp    LM Perfworks
//lm-instmgr	8205/tcp    LM Instmgr
//lm-instmgr	8205/udp    LM Instmgr
//lm-dta	        8206/tcp    LM Dta
//lm-dta		8206/udp    LM Dta
//lm-sserver	8207/tcp    LM SServer
//lm-sserver	8207/udp    LM SServer
//lm-webwatcher	8208/tcp    LM Webwatcher
8208,//lm-webwatcher	8208/udp    LM Webwatcher
//#			                Chris Flynn <cflynn&landmark.com>
//#               8209-8229   Unassigned
8230,//rexecj          8230/tcp    RexecJ Server
8230,//rexecj          8230/udp    RexecJ Server
//#                           Curtiss Howard <cjhoward&unity.ncsu.edu> November 2004
//#               8231-8242   Unassigned
8243,//synapse-nhttps  8243/tcp    Synapse Non Blocking HTTPS
8243,//synapse-nhttps  8243/udp    Synapse Non Blocking HTTPS
//#                           Ruwan Linton <ruwan&wso2.com> 10 July 2008
//#               8244-8275   Unassigned
8276,//pando-sec       8276/tcp    Pando Media Controlled Distribution
8276,//pando-sec       8276/udp    Pando Media Controlled Distribution
//#                           Laird Popkin <laird&pando.com> 27 February 2008
//#               8277-8279   Unassigned
8280,//synapse-nhttp   8280/tcp    Synapse Non Blocking HTTP
8280,//synapse-nhttp   8280/udp    Synapse Non Blocking HTTP
//#                           Ruwan Linton <ruwan&wso2.com> 05 June 2008
//#               8281-8291   Unassigned
8292,//blp3		8292/tcp    Bloomberg professional
8292,//blp3		8292/udp    Bloomberg professional
//#               8293        Unassigned
8294,//blp4		8294/tcp    Bloomberg intelligent client
8294,//blp4		8294/udp    Bloomberg intelligent client
//#			    Albert Hou <ahou1&bloomberg.com> May 2006
//#               8295-8299   Unassigned
8300,//tmi		8300/tcp    Transport Management Interface
//tmi		8300/udp    Transport Management Interface
//#			    Steve Kneizys <skneizys&erpdata.com> November 2006
//amberon		8301/tcp    Amberon PPC/PPS
8301,//amberon		8301/udp    Amberon PPC/PPS
//#			    Ronald Snyder <pugaroni&sssnet.com> March 2006
//#               8302-8319   Unassigned
8320,//tnp-discover	8320/tcp    Thin(ium) Network Protocol
//tnp-discover	8320/udp    Thin(ium) Network Protocol
//tnp		8321/tcp    Thin(ium) Network Protocol
8321,//tnp		8321/udp    Thin(ium) Network Protocol
//#			    Aly Orady, Atto Devices, Inc. <aly.orady&attodevices.com> 07 August 2007
//#               8322-8350   Unassigned
8351,//server-find	8351/tcp    Server Find
8351,//server-find	8351/udp    Server Find
//#			                Chris Brown <chrisb&chancery.com>
//#               8352-8375   Unassigned
8376,//cruise-enum	8376/tcp    Cruise ENUM
//cruise-enum	8376/udp    Cruise ENUM
//cruise-swroute	8377/tcp    Cruise SWROUTE
//cruise-swroute	8377/udp    Cruise SWROUTE
//cruise-config	8378/tcp    Cruise CONFIG
//cruise-config	8378/udp    Cruise CONFIG
//cruise-diags	8379/tcp    Cruise DIAGS
//cruise-diags	8379/udp    Cruise DIAGS
//cruise-update	8380/tcp    Cruise UPDATE
8380,//cruise-update	8380/udp    Cruise UPDATE
//#			                Steve Husak <portmaster&cruisetech.com>   
//#               8381-8382   Unassigned
8383,//m2mservices     8383/tcp    M2m Services
8383,//m2mservices     8383/udp    M2m Services
//#                           Carlos Arteaga <carteaga&adelphia.net> November 2004
//#               8384-8399   Unassigned
8400,//cvd		8400/tcp    cvd
//cvd		8400/udp    cvd
//sabarsd  	8401/tcp    sabarsd
//sabarsd		8401/udp    sabarsd
//abarsd		8402/tcp    abarsd
//abarsd		8402/udp    abarsd
//admind		8403/tcp    admind
8403,//admind 		8403/udp    admind
//#			                Aaron Bilbrey <abilbrey&commvault.com>
//#               8404-8415   Unassigned
8416,//espeech         8416/tcp    eSpeech Session Protocol
//espeech         8416/udp    eSpeech Session Protocol
//#                           Scott Tarone <starone&proactivethought.com> November 2002
//espeech-rtp     8417/tcp    eSpeech RTP Protocol
8418,//espeech-rtp     8417/udp    eSpeech RTP Protocol
//#                           Scott Tarone <starone&proactivethought.com> April 2003
//#               8418-8441   Unassigned
8442,//cybro-a-bus	8442/tcp    CyBro A-bus Protocol
//cybro-a-bus	8442/udp    CyBro A-bus Protocol
//#			    Damir Skrjanec <damir.skrjanec&cybrotech.co.uk> May 2007
//pcsync-https    8443/tcp    PCsync HTTPS
//pcsync-https    8443/udp    PCsync HTTPS
//pcsync-http     8444/tcp    PCsync HTTP
8444,//pcsync-http     8444/udp    PCsync HTTP
//#                           Katy Lynn McCullough <KatyM&LapLink.com>
//#               8445-8449   Unassigned 
8450,//npmp            8450/tcp    npmp
8450,//npmp            8450/udp    npmp
//#                           Ian Chard <ian&tanagra.demon.co.uk>
//#               8451-8469   Unassigned
8470,//cisco-avp       8470/tcp    Cisco Address Validation Protocol
//#                           Cullen Jennings <fluffy&cisco.com> 13 February 2009
//#               8470/udp    Reserved
//pim-port        8471/tcp    PIM over Reliable Transport
//pim-port        8471/sctp   PIM over Reliable Transport
//#                           Dino Farinacci <dino&cisco.com> 21 August 2008
//#               8471/udp    Reserved
//otv             8472/tcp    Overlay Transport Virtualization (OTV)
//otv             8472/udp    Overlay Transport Virtualization (OTV)
//#                           Dino Farinacci <dino&cisco.com> 07 January 2008
//vp2p            8473/tcp    Virtual Point to Point
//vp2p            8473/udp    Virtual Point to Point
//#                           Jerome Grimbert <jerome.grimbert&atosorigin.com>
//noteshare       8474/tcp    AquaMinds NoteShare
8474,//noteshare       8474/udp    AquaMinds NoteShare
//#                           Michael McNabb <michael&aquaminds.com> October 2005
//#               8475-8499   Unassigned
8500,//fmtp            8500/tcp    Flight Message Transfer Protocol
8500,//fmtp            8500/udp    Flight Message Transfer Protocol
//#                           Eivan Cerasi <eivan.cerasi&eurocontrol.int> December 2003
//#               8501-8553   Unassigned
8554,//rtsp-alt        8554/tcp    RTSP Alternate (see port 554)
//rtsp-alt        8554/udp    RTSP Alternate (see port 554)
//#                           Stephen Casner <casner&precept.com>
//d-fence         8555/tcp    SYMAX D-FENCE
8555,//d-fence         8555/udp    SYMAX D-FENCE
//#                           Thomas Geisel <tgeisel&symax.de> January 2003
//#               8556-8566   Unassigned
8567,//oap-admin	8567/tcp    Object Access Protocol Administration
8567,//oap-admin	8567/udp    Object Access Protocol Administration
//#                           Bryant Eastham <protocols&pewla.us.pewg.panasonic.com> August 2005
//#               8568-8599   Unassigned
8600,//asterix         8600/tcp    Surveillance Data 
8600,//asterix         8600/udp    Surveillance Data 
//#                           Eivan Cerasi <eivan.cerasi&eurocontrol.int> November 2005
//#               8601-8609   Unassigned
8610,//canon-mfnp      8610/tcp    Canon MFNP Service
//canon-mfnp      8610/udp    Canon MFNP Service
//#                           Ritsuto Sako <sakou.ritsuto&canon.co.jp> 04 May 2009
//canon-bjnp1     8611/tcp    Canon BJNP Port 1
//canon-bjnp1     8611/udp    Canon BJNP Port 1
//#                           Atsushi Nakamura <nakamura.atsushi318&canon.co.jp> November 2003
//canon-bjnp2     8612/tcp    Canon BJNP Port 2
//canon-bjnp2     8612/udp    Canon BJNP Port 2
//#                           Atsushi Nakamura <nakamura.atsushi318&canon.co.jp> November 2003
//canon-bjnp3     8613/tcp    Canon BJNP Port 3
//canon-bjnp3     8613/udp    Canon BJNP Port 3
//#                           Atsushi Nakamura <nakamura.atsushi318&canon.co.jp> November 2003
//canon-bjnp4     8614/tcp    Canon BJNP Port 4
8614,//canon-bjnp4     8614/udp    Canon BJNP Port 4
//#                           Atsushi Nakamura <nakamura.atsushi318&canon.co.jp> November 2003
//#               8615-8685   Unassigned
8686,//sun-as-jmxrmi   8686/tcp    Sun App Server - JMX/RMI
8686,//sun-as-jmxrmi   8686/udp    Sun App Server - JMX/RMI
//#                           Abhijit Kumar <as-iana-ports&sun.com> November 2005
//#               8687-8698   Unassigned
8699,//vnyx            8699/tcp    VNYX Primary Port
8699,//vnyx            8699/udp    VNYX Primary Port
//#                           Gregg Green <legal&vnyx.net> November 2004
//#               8700-8731   Unassigned
8732,//#               8732/tcp    Reserved
//dtp-net         8732/udp    DASGIP Net Services
//#                           Dr. Matthias Arnold <m.arnold&dasgip.de> 23 March 2009
//ibus		8733/tcp    iBus
8733,//ibus		8733/udp    iBus
//#		            Silvano Maffeis <maffeis&softwired.ch>
//#               8734-8762   Unassigned
8763,//mc-appserver    8763/tcp    MC-APPSERVER
//mc-appserver    8763/udp    MC-APPSERVER
//#                           Romeo Kasanwidjojo <romeo&microcomgroup.com>       
//openqueue       8764/tcp    OPENQUEUE
//openqueue       8764/udp    OPENQUEUE
//#                           Matt Jensen <mattj&newsblip.com>                   
//ultraseek-http	8765/tcp    Ultraseek HTTP
8765,//ultraseek-http	8765/udp    Ultraseek HTTP
//#			                Walter Underwood <wunder&infoseek.com>
//#               8766-8769   Unassigned
8770,//dpap            8770/tcp    Digital Photo Access Protocol
8770,//dpap            8770/udp    Digital Photo Access Protocol
//#                           Amandeep Jawa <dpap&apple.com> November 2004
//#               8771-8785   Unassigned
8786,//msgclnt         8786/tcp    Message Client
//msgclnt         8786/udp    Message Client
//msgsrvr         8787/tcp    Message Server
8787,//msgsrvr         8787/udp    Message Server
//#                           Michael O'Brien <mobrien02&comcast.net> March 2003
//#               8788-8799   Unassigned
8800,//sunwebadmin     8800/tcp    Sun Web Server Admin Service
8800,//sunwebadmin     8800/udp    Sun Web Server Admin Service
//#                           Jyri J. Virkki <jyri.virkki&sun.com> December 2005
//#               8801-8803   Unassigned
8804,//truecm          8804/tcp    truecm
8804,//truecm          8804/udp    truecm
//#                           Scott Kramer <scottk&truebluesoftware.com>
//#               8805-8872   Unassigned
8873,//dxspider        8873/tcp    dxspider linking protocol
8873,//dxspider        8873/udp    dxspider linking protocol
//#                           Dirk Koopman <djk&tobit.co.uk> August 2005
//#               8874-8879   Unassigned         
8880,//cddbp-alt	8880/tcp    CDDBP
8880,//cddbp-alt	8880/udp    CDDBP
//#		            Steve Scherf <steve&moonsoft.com>
//#               8881-8882   Unassigned
8883,//secure-mqtt     8883/tcp    Secure MQTT
8883,//secure-mqtt     8883/udp    Secure MQTT
//#                           Arthur Barr <arthur.barr&uk.ibm.com> 27 February 2008
//#               8884-8887   Unassigned
8888,//ddi-tcp-1       8888/tcp    NewsEDGE server TCP (TCP 1)
//ddi-udp-1       8888/udp    NewsEDGE server UDP (UDP 1)
//ddi-tcp-2       8889/tcp    Desktop Data TCP 1
//ddi-udp-2       8889/udp    NewsEDGE server broadcast
//ddi-tcp-3       8890/tcp    Desktop Data TCP 2
//ddi-udp-3       8890/udp    NewsEDGE client broadcast
//ddi-tcp-4       8891/tcp    Desktop Data TCP 3: NESS application
//ddi-udp-4       8891/udp    Desktop Data UDP 3: NESS application
//ddi-tcp-5       8892/tcp    Desktop Data TCP 4: FARM product
//ddi-udp-5       8892/udp    Desktop Data UDP 4: FARM product
//ddi-tcp-6       8893/tcp    Desktop Data TCP 5: NewsEDGE/Web application
//ddi-udp-6       8893/udp    Desktop Data UDP 5: NewsEDGE/Web application
//ddi-tcp-7       8894/tcp    Desktop Data TCP 6: COAL application
8894,//ddi-udp-7       8894/udp    Desktop Data UDP 6: COAL application
//#                           Fred Yao <Fred_Yao&DDIGATE2.desktopdata.com>
//#               8895-8898   Unassigned 
8899,//ospf-lite       8899/tcp    ospf-lite
//ospf-lite       8899/udp    ospf-lite
//#                           Matthew Thomas <mrthom&essex.ac.uk> 07 January 2008
//jmb-cds1        8900/tcp    JMB-CDS 1
//jmb-cds1        8900/udp    JMB-CDS 1
//jmb-cds2        8901/tcp    JMB-CDS 2
8901,//jmb-cds2        8901/udp    JMB-CDS 2
//#			    Curtis Bray <CurtisB&creativedesign.com>
//#               8902-8909   Unassigned
8910,//manyone-http    8910/tcp    manyone-http
//manyone-http    8910/udp    manyone-http
//manyone-xml     8911/tcp    manyone-xml
//manyone-xml     8911/udp    manyone-xml
//#                           Matt King <m&manyone.net> April 2002
//wcbackup        8912/tcp    Windows Client Backup
//wcbackup        8912/udp    Windows Client Backup
//#                           Jim Lyon <JimLyon&Microsoft.Com> November 2005
//dragonfly       8913/tcp    Dragonfly System Service
8913,//dragonfly       8913/udp    Dragonfly System Service
//#                           Paul Hodara <phodara&netwave.com> November 2005
//#               8914-8953   Unassigned
8954,//cumulus-admin   8954/tcp    Cumulus Admin Port
8954,//cumulus-admin   8954/udp    Cumulus Admin Port
//#                           Thomas Schleu <tschleu&canto.de>
//#               8955-8988   Unassigned
8989,//sunwebadmins    8989/tcp    Sun Web Server SSL Admin Service
8989,//sunwebadmins    8989/udp    Sun Web Server SSL Admin Service
//#                           Jyri J. Virkki <jyri.virkki&sun.com> December 2005
//http-wmap	8990/tcp    webmail HTTP service
//http-wmap	8990/udp    webmail HTTP service
//https-wmap	8991/tcp    webmail HTTPS service
8991,//https-wmap	8991/udp    webmail HTTPS service
//#			    Fred Batty <fredb&sun.com> 03 December 2007
//#               8992-8998   Unassigned
8999,//bctp            8999/tcp    Brodos Crypto Trade Protocol
//bctp            8999/udp    Brodos Crypto Trade Protocol
//#                           Alexander Sahler <alexander.sahler&brodos.de> February 2002
//cslistener      9000/tcp    CSlistener
//cslistener      9000/udp    CSlistener
//#                           David Jones <djones&cincom.com>
//etlservicemgr   9001/tcp    ETL Service Manager
//etlservicemgr   9001/udp    ETL Service Manager
//#                           Stephen McCrea <smccrea&etlelectronique.com> March 2002
//dynamid         9002/tcp    DynamID authentication
9002,//dynamid         9002/udp    DynamID authentication
//#                           Jerome Dusautois <jdusautois&scrypto.fr> March 2002
//#               9003-9005   Unassigned
9006,//#               9006        De-Commissioned Port 02/24/00, ms
//#               9007/tcp    Reserved
//ogs-client      9007/udp    Open Grid Services Client
//#                           Gareth Nelson <gareth&litesim.com> 22 August 2008
//ogs-server      9008/tcp    Open Grid Services Server
//#                           Gareth Nelson <gareth&litesim.com> 22 August 2008
//#               9008/udp    Reserved
//pichat          9009/tcp    Pichat Server
//pichat          9009/udp    Pichat Server
//#                           Mark Seuffert <captain2004&pirate.de> November 2004
//sdr             9010/tcp    Secure Data Replicator Protocol
//#                           Sufyan Almajali <sufyan.almajali&sdrlive.com> 27 June 2008
9010,//#               9010/udp    Reserved
//#               9011-9019   Unassigned
9020,//tambora         9020/tcp    TAMBORA
//tambora         9020/udp    TAMBORA
//#                           Jason van Zyl <jvanzyl&zenplex.com> March 2002
//panagolin-ident 9021/tcp    Pangolin Identification
//panagolin-ident 9021/udp    Pangolin Identification
//#                           William Benner <bill&pangolin.com> March 2002
//paragent        9022/tcp    PrivateArk Remote Agent
//paragent        9022/udp    PrivateArk Remote Agent
//#                           Gal Cucuy <galc&cyber-ark.com> March 2002
//swa-1           9023/tcp    Secure Web Access - 1
//swa-1           9023/udp    Secure Web Access - 1
//swa-2           9024/tcp    Secure Web Access - 2
//swa-2           9024/udp    Secure Web Access - 2
//swa-3           9025/tcp    Secure Web Access - 3
//swa-3           9025/udp    Secure Web Access - 3
//swa-4           9026/tcp    Secure Web Access - 4
9026,//swa-4           9026/udp    Secure Web Access - 4
//#                           Tim McGranaghan <tim_mcgranaghan&mech.disa.mil>
//#               9027-9079   Unassigned
9080,//glrpc           9080/tcp    Groove GLRPC
9080,//glrpc           9080/udp    Groove GLRPC
//#                           Adrian Popescu <Adrian_Popescu&groove.net> September 2002
//#               9081-9083   Unassigned
9084,//aurora          9084/tcp    IBM AURORA Performance Visualizer
//aurora          9084/udp    IBM AURORA Performance Visualizer
//aurora          9084/sctp   IBM AURORA Performance Visualizer
//#                           Jeroen Massar <jma&zurich.ibm.com> 21 August 2008
//ibm-rsyscon     9085/tcp    IBM Remote System Console
//ibm-rsyscon     9085/udp    IBM Remote System Console
//#                           William LePera <lepera&us.ibm.com> 18 June 2008
//net2display     9086/tcp    Vesa Net2Display
//net2display     9086/udp    Vesa Net2Display
//#                           Kenneth B. Ocheltree <kennetho&us.ibm.com> 07 January 2008
//classic		9087/tcp    Classic Data Server
//classic		9087/udp    Classic Data Server
//#			    Paul Cadarette <pcadaret&us.ibm.com> January 2007
//sqlexec		9088/tcp    IBM Informix SQL Interface
//sqlexec		9088/udp    IBM Informix SQL Interface
//sqlexec-ssl     9089/tcp    IBM Informix SQL Interface - Encrypted
//sqlexec-ssl     9089/udp    IBM Informix SQL Interface - Encrypted
//#                           Jonathan Leffler <jleffler&us.ibm.com> December 2005
//websm           9090/tcp    WebSM
//websm           9090/udp    WebSM
//#                           I-Hsing Tsao <itsao&austin.ibm.com>
//xmltec-xmlmail  9091/tcp    xmltec-xmlmail
//xmltec-xmlmail  9091/udp    xmltec-xmlmail
//#                           Mitch Kaufman <mk&weconnectyou.com>
//XmlIpcRegSvc    9092/tcp    Xml-Ipc Server Reg
9092,//XmlIpcRegSvc    9092/udp    Xml-Ipc Server Reg
//#                           Casey Harrington <charrington&isxinc.com> January 2006
//#               9093-9099   Unassigned
9100,//hp-pdl-datastr  9100/tcp    PDL Data Streaming Port
//hp-pdl-datastr  9100/udp    PDL Data Streaming Port
//#                           Shivaun Albright <shivaun_albright&hp.com> April 2002
//#### The protocol name "pdl-datastream" is primarily registered for use #### 
//#### in DNS SRV records (RFC 2782). DNS SRV records allow a protocol to run on ####
//#### any port number, but the default port for this protocol is 9100 ####.
//pdl-datastream  9100/tcp    Printer PDL Data Stream 
//pdl-datastream  9100/udp    Printer PDL Data Stream 
//#                           Stuart Cheshire <pdl-datastream&apple.com> September 2002
//bacula-dir      9101/tcp    Bacula Director
//bacula-dir      9101/udp    Bacula Director
//bacula-fd       9102/tcp    Bacula File Daemon  
//bacula-fd       9102/udp    Bacula File Daemon
//bacula-sd       9103/tcp    Bacula Storage Daemon
//bacula-sd       9103/udp    Bacula Storage Daemon
//#                           Kern Sibbald <kern&sibbald.com>  January 2002
//peerwire        9104/tcp    PeerWire
//peerwire        9104/udp    PeerWire
//#                           Steven Gerhardt <sgerhardt&ixiononline.com> February 2004
//xadmin          9105/tcp    Xadmin Control Service
9105,//xadmin          9105/udp    Xadmin Control Service
//#                           Ari�n Huisken <xadmin&huisken-systems.nl> 15 June 2009
//#               9106-9118   Unassigned
9119,//mxit		9119/tcp    MXit Instant Messaging
9119,//mxit		9119/udp    MXit Instant Messaging
//#			    Marnus Freeman <marnus&swistgroup.com> February 2006
//#               9120-9130   Unassigned
9131,//dddp            9131/tcp    Dynamic Device Discovery
9131,//dddp            9131/udp    Dynamic Device Discovery
//#                           Shane Dick <shane.dick&amx.com> August 2005
//#               9132-9159   Unassigned
9160,//apani1		9160/tcp    apani1
//apani1		9160/udp    apani1
//apani2		9161/tcp    apani2
//apani2		9161/udp    apani2
//apani3		9162/tcp    apani3
//apani3		9162/udp    apani3
//apani4		9163/tcp    apani4
//apani4		9163/udp    apani4
//apani5		9164/tcp    apani5
9164,//apani5		9164/udp    apani5
//#		            Neal Taylor <ianareg&apani.com>
//#               9165-9190   Unassigned
9191,//sun-as-jpda     9191/tcp    Sun AppSvr JPDA
9191,//sun-as-jpda     9191/udp    Sun AppSvr JPDA
//#                           Abhijit Kumar <as-iana-ports&sun.com> November 2005
//#               9192-9199   Unassigned
9200,//wap-wsp	    	9200/tcp    WAP connectionless session service
//wap-wsp		9200/udp    WAP connectionless session service
//wap-wsp-wtp	9201/tcp    WAP session service
//wap-wsp-wtp	9201/udp    WAP session service
//wap-wsp-s	9202/tcp    WAP secure connectionless session service
//wap-wsp-s	9202/udp    WAP secure connectionless session service
//wap-wsp-wtp-s	9203/tcp    WAP secure session service
//wap-wsp-wtp-s	9203/udp    WAP secure session service
//wap-vcard	9204/tcp    WAP vCard
//wap-vcard	9204/udp    WAP vCard
//wap-vcal	9205/tcp    WAP vCal
//wap-vcal	9205/udp    WAP vCal
//wap-vcard-s	9206/tcp    WAP vCard Secure
//wap-vcard-s	9206/udp    WAP vCard Secure
//wap-vcal-s	9207/tcp    WAP vCal Secure
//wap-vcal-s	9207/udp    WAP vCal Secure
//#                           WAP Forum <wap-feedback&mail.wapforum.org>	
//#                           WAP Forum <pg&uplanet.com>
//rjcdb-vcards    9208/tcp    rjcdb vCard 
//rjcdb-vcards    9208/udp    rjcdb vCard
//#			    Robert John Churchill <rjc&rjcdb.com> January 2006
//almobile-system 9209/tcp    ALMobile System Service
//almobile-system 9209/udp    ALMobile System Service
//#			    Rob Graber <r.graber&austinlane.com> January 2006
//oma-mlp         9210/tcp    OMA Mobile Location Protocol
//oma-mlp         9210/udp    OMA Mobile Location Protocol
//oma-mlp-s       9211/tcp    OMA Mobile Location Protocol Secure
//oma-mlp-s       9211/udp    OMA Mobile Location Protocol Secure
//#                           Hans Rohnert <hans.rohnert&siemens.com> April 2002
//serverviewdbms  9212/tcp    Server View dbms access [January 2005]
//serverviewdbms  9212/udp    Server View dbms access [January 2005]
//#                           Detlef Rothe <detlef.rothe&ts.fujitsu.com> 15 May 2009
//serverstart     9213/tcp    ServerStart RemoteControl [August 2005]
//serverstart     9213/udp    ServerStart RemoteControl [August 2005]
//#                           Detlef Rothe <detlef.rothe&ts.fujitsu.com> 15 May 2009
//ipdcesgbs       9214/tcp    IPDC ESG BootstrapService
//ipdcesgbs       9214/udp    IPDC ESG BootstrapService
//#			    Joerg Heuer <Joerg.Heuer&siemens.com> February 2006
//insis           9215/tcp    Integrated Setup and Install Service
//insis           9215/udp    Integrated Setup and Install Service
//#			    Markus Treinen <markus.treinen&siemens.com> February 2006
//acme		9216/tcp    Aionex Communication Management Engine
//acme		9216/udp    Aionex Communication Management Engine
//#			    Mark Sapp <mark.sapp&aionex.com> April 2006
//fsc-port        9217/tcp    FSC Communication Port
9217,//fsc-port        9217/udp    FSC Communication Port
//#                           Teijo Mustonen <Teijo.Mustonen&F-Secure.com> March 2002
//#               9218-9221   Unassigned
9222,//teamcoherence   9222/tcp    QSC Team Coherence
9222,//teamcoherence   9222/udp    QSC Team Coherence
//#                           Ewan McNab <ewan&qsc.co.uk> November 2004
//#               9223-9254   Unassigned
9255,//mon		9255/tcp    Manager On Network
9255,//mon		9255/udp    Manager On Network
//#			    David Rouchet <david.rouchet&medialon.com> May 2007
//#               9256-9277   Unassigned
9278,//pegasus         9278/tcp    Pegasus GPS Platform
//pegasus         9278/udp    Pegasus GPS Platform
//#                           Nestor A. Diaz <nestor&tiendalinux.com> 12 May 2009
//pegasus-ctl     9279/tcp    Pegaus GPS System Control Interface
//pegasus-ctl     9279/udp    Pegaus GPS System Control Interface
//#                           Nestor A. Diaz <nestor&tiendalinux.com> 12 May 2009
//pgps            9280/tcp    Predicted GPS
//pgps            9280/udp    Predicted GPS
//#                           Jeremy Freeman <jeremy&rxnetworks.ca> 14 February 2008
//swtp-port1      9281/tcp    SofaWare transport port 1
//swtp-port1      9281/udp    SofaWare transport port 1
//swtp-port2      9282/tcp    SofaWare transport port 2
//swtp-port2      9282/udp    SofaWare transport port 2
//#                           Amir Rapson <rapson&sofaware.com> February 2002
//callwaveiam     9283/tcp    CallWaveIAM
//callwaveiam     9283/udp    CallWaveIAM
//#                           Colin Kelley <cdk&callwave.com> 
//visd            9284/tcp    VERITAS Information Serve
//visd            9284/udp    VERITAS Information Serve
//#                           Ravi Tavakely <ravi.tavakley&veritas.com> February 2002
//n2h2server      9285/tcp    N2H2 Filter Service Port
9285,//n2h2server      9285/udp    N2H2 Filter Service Port
//#                           Jim Irwin <jirwin&n2h2.com> February 2002
//#               9286        Unassigned
9287,//cumulus         9287/tcp    Cumulus
9287,//cumulus		9287/udp    Cumulus
//#                           Thomas Schleu <tschleu&canto.de>                  
//#               9288-9291   Unassigned
9292,//armtechdaemon   9292/tcp    ArmTech Daemon
//armtechdaemon   9292/udp    ArmTech Daemon
//#                           Rohan Story <rohan&aurema.com>
//storview	9293/tcp    StorView Client
//storview	9293/udp    StorView Client
//#			    Ryan Smith <ryans&nstor.com> July 2006
//armcenterhttp	9294/tcp    ARMCenter http Service
//armcenterhttp	9294/udp    ARMCenter http Service
//armcenterhttps	9295/tcp    ARMCenter https Service
9295,//armcenterhttps	9295/udp    ARMCenter https Service
//#			    Eric Thiebaut-George <erict&aurema.com> April 2006
//#               9296-9299   Unassigned
9300,//vrace		9300/tcp    Virtual Racing Service
9300,//vrace		9300/udp    Virtual Racing Service
//#			    Pete Loeffen, President, Digital Rowing Inc. <peterl&digitalrowing.com> October 2006
//#               9301-9317   Unassigned
9318,//secure-ts       9318/tcp    PKIX TimeStamp over TLS
9318,//secure-ts       9318/udp    PKIX TimeStamp over TLS
//#                           Niklas Weiss <n.weiss&d-trust.net> November 2004
//#               9319-9320   Unassigned
9321,//guibase		9321/tcp    guibase
9321,//guibase		9321/udp    guibase
//#			    Yutaka Ono <ono&saint.nm.fujitsu.co.jp>
//#               9322-9342   Unassigned
9343,//mpidcmgr    	9343/tcp    MpIdcMgr
//mpidcmgr 	9343/udp    MpIdcMgr
//mphlpdmc	9344/tcp    Mphlpdmc
9344,//mphlpdmc	9344/udp    Mphlpdmc
//#			    Yutaka Ono <ono&saint.nm.fujitsu.co.jp>
//#               9345        Unassigned    
9346,//ctechlicensing  9346/tcp    C Tech Licensing
9346,//ctechlicensing  9346/udp    C Tech Licensing
//#                           Reed Copsey, Jr. <reedc&ctech.com>       
//#               9347-9373   Unassigned
9374,//fjdmimgr	9374/tcp    fjdmimgr
9374,//fjdmimgr	9374/udp    fjdmimgr
//#			                Yutaka Ono <ono&saint.nm.fujitsu.co.jp>
//#               9375-9379   Unassigned
9380,//boxp		9380/tcp    Brivs! Open Extensible Protocol
9380,//boxp		9380/udp    Brivs! Open Extensible Protocol
//#			    Danko Alexeyev <virtuall&virtuall.info> 08 August 2007
//#               9381-9386   Unassigned
9367,//d2dconfig       9387/tcp    D2D Configuration Service
//#                           Pete Camble <pete.camble&hp.com> 24 December 2008
//#               9387/udp    Reserved
//d2ddatatrans    9388/tcp    D2D Data Transfer Service
//#                           Pete Camble <pete.camble&hp.com> 24 December 2008
//#               9388/udp    Reserved
//adws            9389/tcp    Active Directory Web Services
//#                           Nitin Gupta <ngupt&microsoft.com> 24 December 2008
//#               9389/udp    Reserved
//otp             9390/tcp    OpenVAS Transfer Protocol
//#                           Tim Brown <timb&openvas.org> 24 December 2008
9390,//#               9390/udp    Reserved
//#               9391-9395   Unassigned
9396,//fjinvmgr	9396/tcp    fjinvmgr
//fjinvmgr	9396/udp    fjinvmgr
//mpidcagt	9397/tcp    MpIdcAgt
9397,//mpidcagt	9397/udp    MpIdcAgt
//#		            Yutaka Ono <ono&saint.nm.fujitsu.co.jp>
//#               9398-9399   Unassigned
9400,//sec-t4net-srv	9400/tcp    Samsung Twain for Network Server
//sec-t4net-srv	9400/udp    Samsung Twain for Network Server
//sec-t4net-clt	9401/tcp    Samsung Twain for Network Client
//sec-t4net-clt	9401/udp    Samsung Twain for Network Client
//#			    Dongkeun Kim <dongkeun70.kim&samsung.com> February 2007
//sec-pc2fax-srv  9402/tcp    Samsung PC2FAX for Network Server
9402,//sec-pc2fax-srv  9402/udp    Samsung PC2FAX for Network Server
//#                           HyeongBae Yu <hyeongbae.yu&samsung.com> 31 July 2008 
//#               9403-9417   Unassigned
9418,//git             9418/tcp    git pack transfer service
9418,//git             9418/udp    git pack transfer service
//#                           Linus Torvalds <torvalds&osdl.org> September 2005
//#               9419-9442   Unassigned
9443,//tungsten-https	9443/tcp    WSO2 Tungsten HTTPS
//tungsten-https	9443/udp    WSO2 Tungsten HTTPS
//#			    Afkham Azeez <azeez&wso2.com> June 2006
//wso2esb-console 9444/tcp    WSO2 ESB Administration Console HTTPS
9444,//wso2esb-console 9444/udp    WSO2 ESB Administration Console HTTPS
//#                           Ruwan Linton <ruwan&wso2.com> 20 August 2008
//#               9445-9449   Unassigned
9450,//sntlkeyssrvr    9450/tcp    Sentinel Keys Server
9450,//sntlkeyssrvr    9450/udp    Sentinel Keys Server
//#                           Martin Ziskind <ziskind&us.ibm.com> 21 August 2008
//#               9451-9499   Unassigned
9500,//ismserver	9500/tcp    ismserver
9500,//ismserver   	9500/udp    ismserver
//#		            Ian Gordon <iang&micromuse.co.uk>
//#               9501-9534   Unassigned
9535,//mngsuite        9535/tcp    Management Suite Remote Control
//mngsuite        9535/udp    Management Suite Remote Control
//#                           Alan Butt <alan.butt&landesk.com>
//laes-bf		9536/tcp    Surveillance buffering function
9536,//laes-bf		9536/udp    Surveillance buffering function
//#			    Glen Myers <glen.myers&ipfabrics.com> May 2007
//#               9537-9554   Unassigned
9555,//trispen-sra     9555/tcp    Trispen Secure Remote Access
9555,//trispen-sra     9555/udp    Trispen Secure Remote Access
//#                           Jaco Botha <jaco.botha&trispen.com> November 2004
//#               9556-9591   Unassigned
9592,//ldgateway	9592/tcp    LANDesk Gateway
//ldgateway	9592/udp    LANDesk Gateway
//#			    Alan Butt <alan.butt&landesk.com> March 2006
//cba8            9593/tcp    LANDesk Management Agent
//cba8            9593/udp    LANDesk Management Agent
//#                           Alan Butt <alan.butt&landesk.com> November 2004
//msgsys          9594/tcp    Message System
//msgsys          9594/udp    Message System
//pds             9595/tcp    Ping Discovery Service
//pds             9595/udp    Ping Discovery Service
//#                           Alan Butt <alan.butt&landesk.com>
//mercury-disc    9596/tcp    Mercury Discovery
//mercury-disc    9596/udp    Mercury Discovery
//#                           Paul Mclachlan <pmclachlan&mercury.com> November 2005
//pd-admin        9597/tcp    PD Administration
//pd-admin        9597/udp    PD Administration
//#                           Duk Loi <dloi&peerdirect.com> November 2005
//vscp            9598/tcp    Very Simple Ctrl Protocol
//vscp            9598/udp    Very Simple Ctrl Protocol
//#                           Ake Hedman <akhe&eurosource.se> November 2005
//robix           9599/tcp    Robix
//robix           9599/udp    Robix
//#                           Evan Rosen <evan&robix.com> November 2005
//micromuse-ncpw  9600/tcp    MICROMUSE-NCPW
9600,//micromuse-ncpw  9600/udp    MICROMUSE-NCPW
//#                           Hing Wing To <wing.to&micromuse.com>
//#               9601-9611   Unassigned
9612,//streamcomm-ds   9612/tcp    StreamComm User Directory
9612,//streamcomm-ds	9612/udp    StreamComm User Directory
//#                           Brian C. Wiles <brian&streamcomm.com>
//#               9613        Unassigned
9614,//iadt-tls        9614/tcp    iADT Protocol over TLS
//#                           Paul A. Suhler <paul.suhler&quantum.com> 05 February 2009
9614,//#               9614/udp    Reserved
//#               9615        Unassigned
9616,//erunbook_agent  9616/tcp    eRunbook Agent 
//#                           Gerhard Wagner <gw&nova-ratio.de> 10 March 2009
//#               9616/udp    Reserved
//erunbook_server 9617/tcp    eRunbook Server
//#                           Gerhard Wagner <gw&nova-ratio.de> 10 March 2009
//#               9617/udp    Reserved
//condor          9618/tcp    Condor Collector Service
9618,//condor          9618/udp    Condor Collector Service
//#                           Todd Tannenbaum <tannenba&cs.wisc.edu> 03 April 2008
//#               9619-9627   Unassigned
9628,//odbcpathway	9628/tcp    ODBC Pathway Service
//odbcpathway	9628/udp    ODBC Pathway Service
//#			    Adrian Hungate <adrian&haqa.co.uk> May 2007
//uniport		9629/tcp    UniPort SSO Controller
9629,//uniport		9629/udp    UniPort SSO Controller
//#			    Adrian Hungate <adrian&haqa.co.uk> 05 September 2007
//#               9630-9666   Unassigned
9667,//xmms2           9667/tcp    Cross-platform Music Multiplexing System
//xmms2           9667/udp    Cross-platform Music Multiplexing System
//#                           Juho V�h�-Herttua <juhovh&iki.fi> 14 April 2009
//tec5-sdctp      9668/tcp    tec5 Spectral Device Control Protocol
9668,//tec5-sdctp      9668/udp    tec5 Spectral Device Control Protocol
//#                           Michael Muth <m.muth&tec5.com> 11 May 2009
//#               9669-9699   Unassigned
9700,//board-roar      9700/tcp    Board M.I.T. Service
9700,//board-roar      9700/udp    Board M.I.T. Service
//#			    Francesco Rosi <frosi&orenburg.com> January 2006
//#               9701-9746   Unassigned
9747,//l5nas-parchan   9747/tcp    L5NAS Parallel Channel
9747,//l5nas-parchan   9747/udp    L5NAS Parallel Channel
//#                           Lawrence J. Dickson - Land-5 Corporation
//#                           <ldickson&land-5.com> March 2002             
//#               9748-9749   Unassigned
9750,//board-voip      9750/tcp    Board M.I.T. Synchronous Collaboration
9750,//board-voip      9750/udp    Board M.I.T. Synchronous Collaboration
//#			    Francesco Rosi <frosi&orenburg.com> January 2006
//#               9751-9752   Unassigned
9753,//rasadv		9753/tcp    rasadv
9753,//rasadv		9753/udp    rasadv
//#		            Dave Thaler <dthaler&microsoft.com>
//#               9754-9761   Unassigned
9762,//tungsten-http	9762/tcp    WSO2 Tungsten HTTP
9762,//tungsten-http	9762/udp    WSO2 Tungsten HTTP
//#			    Afkham Azeez <azeez&wso2.com> June 2006
//#               9763-9799   Unassigned
9800,//davsrc          9800/tcp    WebDav Source Port
//davsrc          9800/udp    WebDav Source Port
//#                           Ethan Fremen <mindlace&digicool.com>
//sstp-2          9801/tcp    Sakura Script Transfer Protocol-2
//sstp-2          9801/udp    Sakura Script Transfer Protocol-2
//#                           Kouichi Takeda <KHB05271&nifty.com>
//davsrcs         9802/tcp    WebDAV Source TLS/SSL
9802,//davsrcs         9802/udp    WebDAV Source TLS/SSL
//#                           Rob Isaac <rob&automagic.org> July 2003
//#               9803-9874   Unassigned
9875,//sapv1           9875/tcp    Session Announcement v1
//sapv1           9875/udp    Session Announcement v1
//#                           RFC 2974 <ftp://ftp.isi.edu/in-notes/rfc2974.txt>
//sd              9876/tcp    Session Director
//sd              9876/udp    Session Director
//#                           Van Jacobson <van&ee.lbl.gov>
//#		9877-9887   Unassigned
//cyborg-systems	9888/tcp    CYBORG Systems
9888,//cyborg-systems	9888/udp    CYBORG Systems
//#		            Malcolm Graham <Malcolm_Graham&CYBORG.COM>
//#		9889-9897   Unassigned
9898,//monkeycom	9898/tcp    MonkeyCom
//monkeycom       9898/udp    MonkeyCom
//#		            Yuji Kuwabara <HHG01200&niftyserve.or.jp>
//sctp-tunneling  9899/tcp    SCTP TUNNELING
//sctp-tunneling  9899/udp    SCTP TUNNELING
//iua             9900/tcp    IUA
//iua             9900/udp    IUA
//iua             9900/sctp   IUA  
//#                           Lyndon Ong <Lyong&ciena.com>
//enrp		9901/udp    enrp server channel
//enrp-sctp	9901/sctp   enrp server channel
//#			    [RFC5353]
9902,//enrp-sctp-tls	9902/sctp   enrp/tls server channel 
//#			    [RFC5353]
//#		9903-9908   Unassigned
9909,//domaintime      9909/tcp   domaintime
9909,//domaintime      9909/udp   domaintime
//#                          Jeffry Dwight <jeffryd&greyware.com>
//#               9910       Unassigned
9911,//sype-transport  9911/tcp   SYPECom Transport Protocol
9911,//sype-transport  9911/udp   SYPECom Transport Protocol
//#                          Sylvain Pedneault <sylvain&sypecom.qc.ca> March 2003    
//#               9912-9949  Unassigned
9950,//apc-9950        9950/tcp   APC 9950
//apc-9950        9950/udp   APC 9950
//apc-9951        9951/tcp   APC 9951 
//apc-9951        9951/udp   APC 9951
//apc-9952        9952/tcp   APC 9952
//apc-9952        9952/udp   APC 9952
//#                          American Power Conversion <ports&apcc.com>
//acis		9953/tcp   9953
9953,//acis		9953/udp   9953
//#			   Thomas Guth <t.guth&zeiss.de> January 2006
//#		9954-9965  Unassigned
9966,//odnsp		9966/tcp   OKI Data Network Setting Protocol
9966,//odnsp		9966/udp   OKI Data Network Setting Protocol
//#			   Masato Sato <satou203&oki.com> May 2006
//#		9967-9986  Unassigned
9987,//dsm-scm-target	9987/tcp   DSM/SCM Target Interface
//dsm-scm-target	9987/udp   DSM/SCM Target Interface
//#			   Mike Dyslin <mike.dyslin&hp.com> August 2006
//nsesrvr         9988/tcp   Software Essentials Secure HTTP server
//#                          Narayanan Raju <narayanan.raju&hp.com> 05 February 2009
9988,//#               9988/udp   Reserved  
//#		9989-9989  Unassigned
9990,//osm-appsrvr     9990/tcp   OSM Applet Server
//osm-appsrvr     9990/udp   OSM Applet Server
//#                          Vinay Gupta <vinay.gupta&hp.com> August 2003
//osm-oev         9991/tcp   OSM Event Server
//osm-oev         9991/udp   OSM Event Server
//#                          Vinay Gupta <vinay.gupta&hp.com> August 2003
//palace-1        9992/tcp   OnLive-1
//palace-1        9992/udp   OnLive-1
//palace-2        9993/tcp   OnLive-2
//palace-2        9993/udp   OnLive-2
//palace-3        9994/tcp   OnLive-3
//palace-3        9994/udp   OnLive-3
//palace-4        9995/tcp   Palace-4
//palace-4        9995/udp   Palace-4
//palace-5        9996/tcp   Palace-5
//palace-5        9996/udp   Palace-5
//palace-6	9997/tcp   Palace-6
//palace-6	9997/udp   Palace-6
//#			   Douglas Crockford <douglas&crockford.com>
//distinct32      9998/tcp   Distinct32
//distinct32      9998/udp   Distinct32
//distinct        9999/tcp   distinct
//distinct        9999/udp   distinct
//#                          Anoop Tewari <anoop&next.distinct.com>
//ndmp            10000/tcp  Network Data Management Protocol
//ndmp            10000/udp  Network Data Management Protocol
//#                          Brian Ehrmantraut <bae&netapp.com>
//scp-config      10001/tcp  SCP Configuration Port
//scp-config      10001/udp  SCP Configuration Port
//#                          Brad Strand <brad.strand&3ware.com>
//documentum	10002/tcp  EMC-Documentum Content Server Product
//documentum	10002/udp  EMC-Documentum Content Server Product
//documentum_s	10003/tcp  EMC-Documentum Content Server Product
//documentum_s	10003/udp  EMC-Documentum Content Server Product
//#			   Reza Bagherian <bagherian_reza&emc.com> 19 July 2007
//emcrmirccd      10004/tcp  EMC Replication Manager Client
//#                          Robert Boudrie <boudrie_rob&emc.com> 09 June 2008
//#               10004/udp  Reserved
//emcrmird        10005/tcp  EMC Replication Manager Server
//#                          Robert Boudrie <boudrie_rob&emc.com> 09 June 2008
10005,//#               10005/udp  Reserved
//#               10006      Unassigned
10007,//mvs-capacity	10007/tcp  MVS Capacity
//mvs-capacity	10007/udp  MVS Capacity
//#                          Donna Dillenberger <engd&us.ibm.com>
//octopus         10008/tcp  Octopus Multiplexer
//octopus         10008/udp  Octopus Multiplexer
//#                          Chris Koeritz <fred&gruntose.com> October 2002
//swdtp-sv	10009/tcp  Systemwalker Desktop Patrol
10009,//swdtp-sv	10009/udp  Systemwalker Desktop Patrol
//#			   Akira Ide <ide.akira&jp.fujitsu.com> March 2006
//#               10010-10049 Unassigned
10050,//zabbix-agent    10050/tcp  Zabbix Agent
//zabbix-agent    10050/udp  Zabbix Agent
//zabbix-trapper  10051/tcp  Zabbix Trapper
10051,//zabbix-trapper  10051/udp  Zabbix Trapper
//#			   Alexei Vladishev <alexei.vladishev&zabbix.com> February 2006
//#               10052-10079 Unassigned
10080,//amanda          10080/tcp  Amanda 
//amanda          10080/udp  Amanda 
//#                          John Jackson <jrj&gandalf.cc.purdue.edu>
//#                          <amanda-core&amanda.org>
//famdc		10081/tcp  FAM Archive Server
//famdc		10081/udp  FAM Archive Server
10082,//#			   Frode Randers <Frode.Randers&tietoenator.com> January 2006
//#               10082-10099 Unassigned
10100,//itap-ddtp       10100/tcp  VERITAS ITAP DDTP
//itap-ddtp       10100/udp  VERITAS ITAP DDTP
//#                          Saugata Guha <sguha&veritas.com> May 2004
//ezmeeting-2     10101/tcp  eZmeeting
//ezmeeting-2     10101/udp  eZmeeting
//ezproxy-2       10102/tcp  eZproxy
//ezproxy-2       10102/udp  eZproxy
//ezrelay         10103/tcp  eZrelay
//ezrelay         10103/udp  eZrelay
//#                          Albert C. Yang <albert.yang&eZmeeting.com> March 2002
//swdtp		10104/tcp  Systemwalker Desktop Patrol
10104,//swdtp		10104/udp  Systemwalker Desktop Patrol
//#			   Akira Ide <ide.akira&jp.fujitsu.com> September 2006
//#               10105-10106 Unassigned
//bctp-server     10107/tcp  VERITAS BCTP, server
10107,//bctp-server     10107/udp  VERITAS BCTP, server
//#                          Saugata Guha <sguha&veritas.com> May 2004
//#               10108-10109 Unassigned
10110,//nmea-0183       10110/tcp  NMEA-0183 Navigational Data
10110,//nmea-0183       10110/udp  NMEA-0183 Navigational Data
//#                          Meindert Sprang <ms&customware.nl> 18 February 2009
//#               10111-10112 Unassigned
10113,//netiq-endpoint  10113/tcp  NetIQ Endpoint
//netiq-endpoint  10113/udp  NetIQ Endpoint
//netiq-qcheck    10114/tcp  NetIQ Qcheck
//netiq-qcheck    10114/udp  NetIQ Qcheck
//#                          John Wood <John.Wood&netiq.com> 
//netiq-endpt     10115/tcp  NetIQ Endpoint
//netiq-endpt	10115/udp  NetIQ Endpoint
//#		           Gary Weichinger <gary.weichinger&netiq.com>
//netiq-voipa     10116/tcp  NetIQ VoIP Assessor
10116,//netiq-voipa     10116/udp  NetIQ VoIP Assessor
//#                          Gary Weichinger <gary.weichinger&netiq.com>
//#		10117-10127 Unassigned
10128,//bmc-perf-sd     10128/tcp  BMC-PERFORM-SERVICE DAEMON
10128,//bmc-perf-sd     10128/udp  BMC-PERFORM-SERVICE DAEMON
//#                          Portnoy Boxman <portnoy_boxman&bmc.com>
//#               10129-10159 Unassigned
10160,//qb-db-server    10160/tcp  QB Database Server
10160,//qb-db-server    10160/udp  QB Database Server
//#			   Wei Wang <Wei_Wang&intuit.com> November 2005
//#               10161-10199 Unassigned
10200,//trisoap		10200/tcp  Trigence AE Soap Service
//trisoap		10200/udp  Trigence AE Soap Service
//#			   Brigitte Gagne <bgagne&trigence.com> August 2006
//rsms            10201/tcp  Remote Server Management Service
10201,//rscs            10201/udp  Remote Server Control and Test Service
//#                          Patrick H. Piper <ppiper&netlinxinc.com> 06 March 2009
//#               10202-10251 Unassigned
10252,//apollo-relay    10252/tcp  Apollo Relay Port
10252,//apollo-relay    10252/udp  Apollo Relay Port
//#                          Anthony Carrabino <anthonyc&vistasoftware.com> August 2003 
//#               10253-10259 Unassigned
10260,//axis-wimp-port  10260/tcp  Axis WIMP Port
10260,//axis-wimp-port  10260/udp  Axis WIMP Port
//#                          Stefan Eriksson <contact-iana&axis.com>
//#               10261-10287 Unassigned
10288,//blocks		10288/tcp  Blocks 
10288,//blocks		10288/udp  Blocks 
//#		           Carl Malamud
//#		10289-10320 Unassigned
10321,//cosir           10321/tcp   Computer Op System Information Report
//#                           Kevin C. Barber <kevin.c.barber&saic.com> 13 January 2009
10321,//#               10321/udp   Reserved
//#		10322-10539 Unassigned
10540,//MOS-lower	10540/tcp  MOS Media Object Metadata Port 
//MOS-lower	10540/udp  MOS Media Object Metadata Port
//MOS-upper	10541/tcp  MOS Running Order Port
//MOS-upper	10541/udp  MOS Running Order Port
//MOS-aux		10542/tcp  MOS Low Priority Port
//MOS-aux		10542/udp  MOS Low Priority Port
//MOS-soap	10543/tcp  MOS SOAP Default Port
//MOS-soap	10543/udp  MOS SOAP Default Port
//MOS-soap-opt	10544/tcp   MOS SOAP Optional Port
10544,///MOS-soap-opt	10544/udp   MOS SOAP Optional Port
//#			   Eric Thorniley <eric&etcomms.co.uk>   17 September 2007
//#		10545-10799 Unassigned
10800,//gap		10800/tcp  Gestor de Acaparamiento para Pocket PCs
10800,//gap		10800/udp  Gestor de Acaparamiento para Pocket PCs
//#			   Juan Carlos Olivares Rojas <jcolivares04c&cenidet.edu.mx> March 2006
//#		10801-10804 Unassigned
10805,//lpdg		10805/tcp  LUCIA Pareja Data Group
10805,//lpdg		10805/udp  LUCIA Pareja Data Group
//#			   Alvaro P. Dominguez <alpado&gmail.com> February 2006
//#		10806-10859 Unassigned
10860,//helix           10860/tcp  Helix Client/Server
10860,//helix           10860/udp  Helix Client/Server
//#                          Matthew Strange <matt&qsatoolworks.com> 06 March 2009 
//#		10861-10989 Unassigned
10990,//rmiaux          10990/tcp  Auxiliary RMI Port
10990,//rmiaux          10990/udp  Auxiliary RMI Port
//#                          Eugen Bacic <eugen&texar.com>
//#               10991-10999 Unassigned
11000,//irisa		11000/tcp  IRISA
//irisa		11000/udp  IRISA
//#		           V.A. Brauner <info&datamedia.fr>
//metasys		11001/tcp  Metasys
//metasys		11001/udp  Metasys
11001,//#		           Tobin Schuster <tobin.j.schuster&jci.com>
//#               11002-11105 Unassigned
11006,//sgi-lk          11106/tcp   SGI LK Licensing service
11006,//sgi-lk          11106/udp   SGI LK Licensing service
//#                           Michel Bourget <michel&sgi.com> 06 January 2009
//#               11107-11110 Unassigned
11111,//vce		11111/tcp  Viral Computing Environment (VCE)
//vce		11111/udp  Viral Computing Environment (VCE)
//#		           Fred Cohen <fc&all.net>
//dicom           11112/tcp   DICOM
11112,//dicom           11112/udp   DICOM
//#                           David Clunie <dclunie&dclunie.com> August 2005
//#               11113-11160 Unassigned
11161,//suncacao-snmp   11161/tcp   sun cacao snmp access point
//suncacao-snmp   11161/udp   sun cacao snmp access point
//suncacao-jmxmp  11162/tcp   sun cacao JMX-remoting access point
//suncacao-jmxmp  11162/udp   sun cacao JMX-remoting access point
//suncacao-rmi    11163/tcp   sun cacao rmi registry access point
//suncacao-rmi    11163/udp   sun cacao rmi registry access point
//suncacao-csa    11164/tcp   sun cacao command-streaming access point
//suncacao-csa    11164/udp   sun cacao command-streaming access point
//suncacao-websvc 11165/tcp   sun cacao web service access point
//suncacao-websvc 11165/udp   sun cacao web service access point
11165,//#                           Nick Stephen <nick.stephen&sun.com> August 2005
//#               11166-11200 Unassigned
11201,//smsqp           11201/tcp   smsqp
11201,//smsqp           11201/udp   smsqp
//#                           Andres Seco Hernandez <AndresSH&alamin.org>
//#               11202-11207 Unassigned
11208,//wifree		11208/tcp   WiFree Service
11208,//wifree		11208/udp   WiFree Service
//#			    Jose Luis Martin Peinado <jooe&wifree-project.net> March 2006
//#               11209-11210 Unassigned
11211,//memcache        11211/tcp   Memory cache service
11211,//memcache        11211/udp   Memory cache service
//#                           Trond Norbye <trond.norbye&sun.com> 09 February 2009
//#               11212-11318 Unassigned
11319,//imip            11319/tcp   IMIP
11319,//imip            11319/udp   IMIP
//#                           IM Unified Coalition, Len Zuvela
//#                           <imu-comments&egroups.com>
//imip-channels   11320/tcp   IMIP Channels Port
//imip-channels   11320/udp   IMIP Channels Port
//#                           Len Zuvela <lenz&microsoft.com>
//arena-server    11321/tcp   Arena Server Listen
11321,//arena-server    11321/udp   Arena Server Listen
//#                           Earl Brannigan <earl.brannigan&lindenhous.co.uk>
//#               11322-11366 Unassigned
11367,//atm-uhas        11367/tcp   ATM UHAS
11367,//atm-uhas        11367/udp   ATM UHAS
//#                           Todd Barker <toddba&attachmate.com>
//#               11368-11370 Unassigned
11371,//hkp             11371/tcp   OpenPGP HTTP Keyserver
11371,//hkp             11371/udp   OpenPGP HTTP Keyserver
//#                           David Shaw <dshaw&jabberwocky.com> May 2003 
//#               11372-11599 Unassigned
11600,//tempest-port    11600/tcp   Tempest Protocol Port
11600,//tempest-port    11600/udp   Tempest Protocol Port
//#                           Francis Cianfrocca <francis&tempest.com>
//#               11601-11719 Unassigned
11720,//h323callsigalt  11720/tcp   h323 Call Signal Alternate
11720,//h323callsigalt  11720/udp   h323 Call Signal Alternate
//#                           Chris White <cjwhite&cisco.com>
//#               11721-11750 Unassigned
11751,//intrepid-ssl    11751/tcp  Intrepid SSL
11751,//intrepid-ssl    11751/udp  Intrepid SSL
//#                          Robert Eden <reden&sieglertech.com> March 2003
//#               11752-11966 Unassigned 
11967,//sysinfo-sp      11967/tcp  SysInfo Service Protocol
11967,//sysinfo-sp      11967/udp  SysInfo Sercice Protocol
//#                          Mike Cooper <mcooper&magnicomp.com> March 2003
//#               11968-11996 Unassigned
11997,//wmereceiving	11997/sctp WorldMailExpress 
//wmedistribution 11998/sctp WorldMailExpress 
//wmereporting	11999/sctp WorldMailExpress 
//#			   Greg Foutz <gregf&adminovation.com> March 2006
//entextxid	12000/tcp  IBM Enterprise Extender SNA XID Exchange
//entextxid	12000/udp  IBM Enterprise Extender SNA XID Exchange
//entextnetwk	12001/tcp  IBM Enterprise Extender SNA COS Network Priority
//entextnetwk	12001/udp  IBM Enterprise Extender SNA COS Network Priority
//entexthigh	12002/tcp  IBM Enterprise Extender SNA COS High Priority
//entexthigh	12002/udp  IBM Enterprise Extender SNA COS High Priority
//entextmed	12003/tcp  IBM Enterprise Extender SNA COS Medium Priority
//entextmed	12003/udp  IBM Enterprise Extender SNA COS Medium Priority
//entextlow	12004/tcp  IBM Enterprise Extender SNA COS Low Priority
//entextlow	12004/udp  IBM Enterprise Extender SNA COS Low Priority
//#			   Eugene Cox <genecox&raleigh.ibm.com>
//dbisamserver1   12005/tcp  DBISAM Database Server - Regular
//dbisamserver1   12005/udp  DBISAM Database Server - Regular
//dbisamserver2   12006/tcp  DBISAM Database Server - Admin
//dbisamserver2   12006/udp  DBISAM Database Server - Admin
//#                          Tim Young <timyoung&elevatesoft.com> May 2002
//accuracer       12007/tcp  Accuracer Database System � Server
//accuracer       12007/udp  Accuracer Database System � Server
//accuracer-dbms  12008/tcp  Accuracer Database System � Admin
12008,//accuracer-dbms  12008/udp  Accuracer Database System � Admin
//#                          Alexander V. Ivanov <support&aidaim.com> December 2004 
//#               12009      Unassigned
12010,//edbsrvr         12010/tcp  ElevateDB Server
//#                          Tim Young <timyoung&elevatesoft.com> 06 May 2009
12010,//#               12010/udp  Reserved
//#               12011      Unassigned
12012,//vipera          12012/tcp  Vipera Messaging Service
//vipera          12012/udp  Vipera Messaging Service
//#                          Silvano Maffeis <maffeis&acm.org> August 2005
//vipera-ssl      12013/tcp  Vipera Messaging Service over SSL Communication
12013,//vipera-ssl      12013/udp  Vipera Messaging Service over SSL Communication
//#                          Silvano Maffeis <maffeis&acm.org> 16 January 2008
//#               12014-12108 Unassigned
12109,//rets-ssl        12109/tcp  RETS over SSL
12109,//rets-ssl        12109/udp  RETS over SSL
//#                          Bruce Toback <btoback&optc.com> February 2003 
//#               12110-12120 Unassigned
12121,//nupaper-ss      12121/tcp  NuPaper Session Service
12121,//nupaper-ss      12121/udp  NuPaper Session Service
//#                          David Warden <warden&nupaper.com> November 2005
//#               12122-12167 Unassigned
12168,//cawas           12168/tcp  CA Web Access Service
12168,//cawas           12168/udp  CA Web Access Service
//#                          Jon Press <IANA.Registions&ca.com> August 2005
//#               12169-12171 Unassigned
12172,//hivep		12172/tcp  HiveP
12172,//hivep		12172/udp  HiveP
//#			   Dick Augustsson <dick&skenbe.net>
//#               12173-12299 Unassigned
12300,//linogridengine  12300/tcp   LinoGrid Engine
12300,//linogridengine  12300/udp   LinoGrid Engine
//#                           Frans Lundberg <frans&linova.com> November 2004
//#               12301-12320 Unassigned
12321,//warehouse-sss   12321/tcp   Warehouse Monitoring Syst SSS
//warehouse-sss   12321/udp   Warehouse Monitoring Syst SSS
//warehouse       12322/tcp   Warehouse Monitoring Syst
12322,//warehouse       12322/udp   Warehouse Monitoring Syst
//#                           Craig Steffen <csteffen&ncsa.uiuc.edu> August 2005
//#               12323-12344 Unassigned
12345,//italk           12345/tcp  Italk Chat System
12345,//italk           12345/udp  Italk Chat System
//#                          Takayuki Ito <yuki&euc.jp>
//#               12346-12752 Unassigned
12753,//tsaf            12753/tcp  tsaf port   
12753,//tsaf            12753/udp  tsaf port   
//#                          Andreas Fehr <andreas&mrs.ch>
//#               12754-13159 Unassigned
13160,//i-zipqd		13160/tcp  I-ZIPQD
13160,//i-zipqd		13160/udp  I-ZIPQD
//#			   Chuck Runquist <crunquist&quarterdeck.com>
//#               13161-13215 Unassigned 
13216,//bcslogc         13216/tcp  Black Crow Software application logging 
//bcslogc         13216/udp  Black Crow Software application logging 
//#                          Ramindur Singh <Ramindur.Singh&BlackCrowSoftware.com> 04 December 2008
//rs-pias         13217/tcp  R&S Proxy Installation Assistant Service
//rs-pias         13217/udp  R&S Proxy Installation Assistant Service
//#                          Guido Kiener <Guido.Kiener&rohde-schwarz.com> 04 December 2008
//emc-vcas-tcp    13218/tcp  EMC Virtual CAS Service 
13218,//emc-vcas-udp    13218/udp  EMV Virtual CAS Service Discovery 
//#                          Mark O'Connell <oconnell_marka&emc.com> 04 December 2008
//#               13219-13222 Unassigned 
13223,//powwow-client   13223/tcp  PowWow Client
//powwow-client   13223/udp  PowWow Client
//powwow-server   13224/tcp  PowWow Server
13224,//powwow-server   13224/udp  PowWow Server
//#                          Paul K. Peterson <paul&tribal.com>
//#               13225-13719 Unassigned
13720,//bprd		13720/tcp  BPRD Protocol (VERITAS NetBackup)
//bprd		13720/udp  BPRD Protocol (VERITAS NetBackup)
//bpdbm		13721/tcp  BPDBM Protocol (VERITAS NetBackup)
//bpdbm		13721/udp  BPDBM Protocol (VERITAS NetBackup)
//#			   Jeff Holmbeck <Jeff.Holmbeck&veritas.com>
//bpjava-msvc	13722/tcp  BP Java MSVC Protocol
13722,//bpjava-msvc	13722/udp  BP Java MSVC Protocol
//#			   Tim Schmidt <Tim.Schmidt&veritas.com>
//#               13723      Unassigned
13724,//vnetd           13724/tcp  Veritas Network Utility
13724,//vnetd           13724/udp  Veritas Network Utility
//#                          Jeff Holmbeck <Jeff.Holmbeck&veritas.com> 
//#               13725-13781 Unassigned 
13782,//bpcd		13782/tcp  VERITAS NetBackup
//bpcd		13782/udp  VERITAS NetBackup
//vopied		13783/tcp  VOPIED Protocol
13783,//vopied		13783/udp  VOPIED Protocol
//#			   Jeff Holmbeck <Jeff.Holmbeck&veritas.com>
//#               13784       Unassigned
13785,//nbdb            13785/tcp   NetBackup Database
//nbdb            13785/udp   NetBackup Database
//#                           Pat Tovo <pat.tovo&veritas.com> December 2004
//nomdb           13786/tcp   Veritas-nomdb
13786,//nomdb           13786/udp   Veritas-nomdb
//#                           Clayton Haapala <clay.haapala&veritas.com> August 2005
//#               13787-13817 Unassigned
13818,//dsmcc-config    13818/tcp  DSMCC Config
//dsmcc-config	13818/udp  DSMCC Config
//dsmcc-session	13819/tcp  DSMCC Session Messages
//dsmcc-session	13819/udp  DSMCC Session Messages
//dsmcc-passthru	13820/tcp  DSMCC Pass-Thru Messages
//dsmcc-passthru	13820/udp  DSMCC Pass-Thru Messages
//dsmcc-download	13821/tcp  DSMCC Download Protocol
//dsmcc-download	13821/udp  DSMCC Download Protocol
//dsmcc-ccp	13822/tcp  DSMCC Channel Change Protocol
13822,//dsmcc-ccp	13822/udp  DSMCC Channel Change Protocol
//#			   Tim Addington <Tim.Addington&sciatl.com>
//#			   ISO/IEC 13818-6 MPEG-2 DSM-CC
//#               13823-13928 Unassigned
13929,//dta-systems     13929/tcp  D-TA SYSTEMS 
//dta-systems     13929/udp  D-TA SYSTEMS 
//#                          Alexis Bose <abose&d-ta.com> 08 December 2008
//medevolve       13930/tcp  MedEvolve Port Requester
//#                          Jon Robertson <jmrobertson&medevolve.com> 24 October 2008
13930,//#               13930/udp  Reserved 
//#               13931-13999 Unassigned
14000,//scotty-ft	14000/tcp   SCOTTY High-Speed Filetransfer
//scotty-ft	14000/udp   SCOTTY High-Speed Filetransfer
//#			    Patrick Verbeek <p.verbeek&scottygroup.com> May 2007
//sua	        14001/tcp  SUA
//sua	        14001/udp  De-Registered (2001 June 06)
14001,//sua             14001/sctp SUA
//#			   Miguel Angel Garcia <Miguel.A.Garcia&ericsson.com>
//#               14002-14032 Unassigned
14033,//sage-best-com1  14033/tcp  sage Best! Config Server 1
//sage-best-com1  14033/udp  sage Best! Config Server 1
//sage-best-com2  14034/tcp  sage Best! Config Server 2
14034,//sage-best-com2  14034/udp  sage Best! Config Server 2
//#                          Christian Rubach <Christian_Rubach&bestsoftware.com>
//#               14035-14140 Unassigned  
14141,//vcs-app         14141/tcp  VCS Application
//vcs-app         14141/udp  VCS Application
//#                          Ming Xu <ming&veritas.com>
//icpp            14142/tcp  IceWall Cert Protocol
14142,//icpp            14142/udp  IceWall Cert Protocol
//#                          Tsutomu Fujinami <tsutomu.fujinami&hp.com> August 2005
//#               14143-14144 Unassigned
14145,//gcm-app         14145/tcp  GCM Application
14145,//gcm-app         14145/udp  GCM Application
//#                          Ming Xu <ming&veritas.com>
//#               14146-14148 Unassigned
14149,//vrts-tdd        14149/tcp  Veritas Traffic Director
//vrts-tdd        14149/udp  Veritas Traffic Director
//#                          Sameer Deokule <sameer.deokule&veritas.com> March 2002
//vcscmd          14150/tcp  Veritas Cluster Server Command Server
//#                          Anand Bhalerao <anand_bhalerao&symantec.com> 02 October 2008
14150,//#               14150/udp  Reserved
//#               14151-14153 Unassigned
14154,//vad		14154/tcp  Veritas Application Director
14154,//vad		14154/udp  Veritas Application Director
//#			   Rajeev Verma <rajeev_verma&symantec.com> February 2006
//#               14155-14249 Unassigned
14250,//cps             14250/tcp  Fencing Server
14250,//cps             14250/udp  Fencing Server
//#                          Mayank Vasa <mayank_vasa&symantec.com> 03 April 2008
//#               14251-14413 Unassigned
14414,//ca-web-update	14414/tcp  CA eTrust Web Update Service
14414,//ca-web-update	14414/udp  CA eTrust Web Update Service
//#			   Robert Ciochon <robert.ciochon&ca.com> August 2006
//#               14415-14935 Unassigned
14936,//hde-lcesrvr-1   14936/tcp  hde-lcesrvr-1
//hde-lcesrvr-1   14936/udp  hde-lcesrvr-1
//hde-lcesrvr-2   14937/tcp  hde-lcesrvr-2
14937,//hde-lcesrvr-2   14937/udp  hde-lcesrvr-2
//#                          Horizon Digital Enterprise, Inc. <info&hde.co.jp>
//#               14938-14999 Unassigned
15000,//hydap           15000/tcp  Hypack Data Aquisition
15000,//hydap           15000/udp  Hypack Data Aquisition
//#                          Mircea Neacsu <mircea&videotron.ca>  
//#               15001-15344 Unassigned
15345,//xpilot          15345/tcp  XPilot Contact Port
15345,//xpilot          15345/udp  XPilot Contact Port
//#                          Bert Gijsbers <bert&xpilot.org> 
//#               15346-15362 Unassigned
15363,//3link           15363/tcp  3Link Negotiation
15363,//3link           15363/udp  3Link Negotiation
//#                          Brant Thomsen <brant_thomsen&3com.com> January 2003
//#               15364-15554 Unassigned
15555,//cisco-snat	15555/tcp  Cisco Stateful NAT
15555,//cisco-snat	15555/udp  Cisco Stateful NAT
//#			   Kaushik Biswas <kbiswas&cisco.com> March 2006
//#               15556-15659 Unassigned
15660,//bex-xr          15660/tcp  Backup Express Restore Server
15660,//bex-xr          15660/udp  Backup Express Restore Server
//#                          Chi Shih Chang <cchang&syncsort.com> 19 March 2008
//#               15661-15739 Unassigned
15740,//ptp             15740/tcp  Picture Transfer Protocol
15740,//ptp             15740/udp  Picture Transfer Protocol
//#                          Petronel Bigioi <petronel&fotonation.com> November 2004
//#               15741-16160 Unassigned
16161,//sun-sea-port    16161/tcp  Solaris SEA Port
16161,//sun-sea-port    16161/udp  Solaris SEA Port
//#                          Dana Porter <dana.porter&sun.com> October 2003
16162,//solaris-audit   16162/tcp  Solaris Audit - secure remote audit log
//#                          Jan Friedel <Jan.Friedel&Sun.COM> 07 May 2009 
16161,//#               16162/udp  Reserved
//#               16163-16308 Unassigned
16309,//etb4j           16309/tcp  etb4j
//etb4j           16309/udp  etb4j
//#                          Christopher R. Smith <csmith4&us.ibm.com> November 2004
//pduncs		16310/tcp  Policy Distribute, Update Notification
//pduncs		16310/udp  Policy Distribute, Update Notification
//#			   Diane I. Shannon <shannond&us.ibm.com> August 2006
//pdefmns		16311/tcp  Policy definition and update management
16311,//pdefmns		16311/udp  Policy definition and update management
//#			   Diane I. Shannon <shannond&us.ibm.com> April 2007
//#               16312-16359 Unassigned
16360,//netserialext1	16360/tcp  Network Serial Extension Ports One
//netserialext1	16360/udp  Network Serial Extension Ports One
//netserialext2	16361/tcp  Network Serial Extension Ports Two
16361,//netserialext2	16361/udp  Network Serial Extension Ports Two
//#                          Michael J Hoy <mhoy&canberra-abq.com>
//#               16362-16366 Unassigned
16367,//netserialext3	16367/tcp  Network Serial Extension Ports Three
//netserialext3	16367/udp  Network Serial Extension Ports Three
//netserialext4	16368/tcp  Network Serial Extension Ports Four
16368,//netserialext4   16368/udp  Network Serial Extension Ports Four
//#                          Michael J Hoy <mhoy&canberra-abq.com>
//#               16369-16383 Unassigned
16384,//connected       16384/tcp  Connected Corp
16384,//connected       16384/udp  Connected Corp
//#                          Nicole C. Ouellette <nouellette&connected.com> February 2004
//#               16385-16618 Unassigned
16619,//xoms            16619/tcp  X509 Objects Management Service
16619,//#                          Francis GASCHET / NUMLOG <fg&numlog.fr> 08 September 2008
//#               16619/udp  Reserved
//#               16620-16949 Unassigned
16650,//sgcip		16950/tcp  Simple Generic Client Interface Protocol
16650,//sgcip		16950/udp  Simple Generic Client Interface Protocol
//#			   John Aquilino <john.aquilino&maryville.com>
//#               16951-16990 Unassigned
16991,//intel-rci-mp    16991/tcp  INTEL-RCI-MP
//intel-rci-mp    16991/udp  INTEL-RCI-MP
//#                          Jane Dashevsky <jane.dashevsky&intel.com> 
//amt-soap-http   16992/tcp   Intel(R) AMT SOAP/HTTP
//amt-soap-http   16992/udp   Intel(R) AMT SOAP/HTTP
//amt-soap-https  16993/tcp   Intel(R) AMT SOAP/HTTPS
//amt-soap-https  16993/udp   Intel(R) AMT SOAP/HTTPS
//#                           David T. Hines <david.hines&intel.com> February 2005
//amt-redir-tcp   16994/tcp   Intel(R) AMT Redirection/TCP
//amt-redir-tcp   16994/udp   Intel(R) AMT Redirection/TCP
//amt-redir-tls   16995/tcp   Intel(R) AMT Redirection/TLS
16995,//amt-redir-tls   16995/udp   Intel(R) AMT Redirection/TLS
//#                           Nimrod Diamant <nimrod.diamant&intel.com> February 2005
//#               16996-17006 Unassigned
17007,//isode-dua       17007/tcp
17007,//isode-dua       17007/udp
//#               17008-17184 Unassigned
17185,//soundsvirtual   17185/tcp  Sounds Virtual
17185,//soundsvirtual   17185/udp  Sounds Virtual
//#                          Richard Snider <rsnider&sounds.com>   
//#               17186-17218 Unassigned
17219,//chipper         17219/tcp  Chipper
17219,//chipper         17219/udp  Chipper
//#                          Ronald Jimmink <Ronald.Jimmink&chipper.nl>
//#               17220-17234 Unassigned
17235,//ssh-mgmt        17235/tcp  SSH Tectia Manager
17235,//ssh-mgmt        17235/udp  SSH Tectia Manager
//#                          Ville Laurikari <vlaurika&ssh.com> August 2005
//#               17236-17728 Unassigned
17729,//ea		17729/tcp  Eclipse Aviation
17729,//ea		17729/udp  Eclipse Aviation
//#			   William Schmidt <info&eclipseaviation.com> March 2006
//#               17730-17753 Unassigned
17754,//zep             17754/tcp  Encap. ZigBee Packets
//zep             17754/udp  Encap. ZigBee Packets
//#			   Fred Fierling <fff&exegin.com> February 2006
//zigbee-ip	17755/tcp  ZigBee IP Transport Service
//zigbee-ip	17755/udp  ZigBee IP Transport Service
//zigbee-ips	17756/tcp  ZigBee IP Transport Secure Service
17756,//zigbee-ips	17756/udp  ZigBee IP Transport Secure Service
//#			   Chris Herzog <zog&stg.com> May 2006
//#               17757-17776 Unassigned
17777,//sw-orion        17777/tcp  SolarWinds Orion
//#                          Joel Dolisy <joel.dolisy&solarwinds.com> 10 September 2008
17777,//#               17777/udp  Reserved
//#               17778-17999 Unassigned
18000,//biimenu         18000/tcp  Beckman Instruments, Inc.
18000,//biimenu         18000/udp  Beckman Instruments, Inc.
//#                          R. L. Meyering <RLMEYERING&BIIVAX.DP.BECKMAN.COM>
//#               18001-18180 Unassigned
18181,//opsec-cvp       18181/tcp  OPSEC CVP 
//opsec-cvp       18181/udp  OPSEC CVP 
//opsec-ufp       18182/tcp  OPSEC UFP
//opsec-ufp       18182/udp  OPSEC UFP
//#                          Alon Kantor <alonk&checkpoint.com>
//opsec-sam       18183/tcp  OPSEC SAM
//opsec-sam       18183/udp  OPSEC SAM
//opsec-lea       18184/tcp  OPSEC LEA
//opsec-lea       18184/udp  OPSEC LEA
//opsec-omi       18185/tcp  OPSEC OMI
//opsec-omi       18185/udp  OPSEC OMI
//#                          Alon Kantor <alonk&checkpoint.com>
//ohsc            18186/tcp  Occupational Health SC
//ohsc            18186/udp  Occupational Health Sc
//#                          David Fudge <david.fudge&tssi.co.uk> August 2003
//opsec-ela       18187/tcp  OPSEC ELA
18187,//opsec-ela       18187/udp  OPSEC ELA
//#                          Alon Kantor <alonk&checkpoint.com>
//#               18188-18240 Unassigned
18241,//checkpoint-rtm  18241/tcp  Check Point RTM
18241,//checkpoint-rtm  18241/udp  Check Point RTM
//#                          Dudi Hazan <dudi&checkpoint.com>
//#               18242-18261 Unassigned
18262,//gv-pf           18262/tcp  GV NetConfig Service
18262,//gv-pf           18262/udp  GV NetConfig Service
//#                          Scott Libert <scott.libert&thomson.net> 29 January 2008
//#               18263-18462 Unassigned
18463,//ac-cluster      18463/tcp  AC Cluster
18463,//ac-cluster      18463/udp  AC Cluster
//#                          Lisa Zhong <lzhong&cup.hp.com>
//#               18464-18633 Unassigned
18634,//rds-ib          18634/tcp  Reliable Datagram Service
//rds-ib          18634/udp  Reliable Datagram Service
//#                          Andy Grover <andy.grover&oracle.com> 27 February 2009
//rds-ip          18635/tcp  Reliable Datagram Service over IP
18635,//rds-ip          18635/udp  Reliable Datagram Service over IP
//#                          Andy Grover <andy.grover&oracle.com> 20 May 2009
//#               18636-18768 Unassigned
18769,//ique            18769/tcp  IQue Protocol
18769,//ique            18769/udp  IQue Protocol
//#                          Avi Drissman <ique-protocol&harrisbaseview.com> July 2002
//#               18770-18880 Unassigned
18881,//infotos         18881/tcp   Infotos
18881,//infotos         18881/udp   Infotos
//#                           Marcel Dube <marceldube&videotron.ca> November 2004
//#               18882-18887 Unassigned
18888,//apc-necmp       18888/tcp  APCNECMP 
18888,//apc-necmp       18888/udp  APCNECMP 
//#                          Michael Yip <Michael.Yip&alcatel.com>
//#               18889-18999 Unassigned
19000,//igrid           19000/tcp   iGrid Server
19001,//igrid           19000/udp   iGrid Server
//#                           Massimo Cafaro <massimo.cafaro&unile.it> November 2004
//#               19001-19019 Unassigned
19020,//j-link          19020/tcp   J-Link TCP/IP Protocol
19020,//#                           SEGGER Microcontroller GmbH & Co. KG <info&segger.com> 16 January 2009
//#               19020/udp   Reserved
//#               19021-19190 Unassigned
19191,//opsec-uaa       19191/tcp  OPSEC UAA
19191,//opsec-uaa       19191/udp  OPSEC UAA
//#                          Reuven Harrison  <rnd_ana&checkpoint.com> 
//#               19192-19193 Unassigned
19194,//ua-secureagent  19194/tcp  UserAuthority SecureAgent
19194,//ua-secureagent  19194/udp  UserAuthority SecureAgent
//#                          Reuven Harrison <rharrison&checkpoint.com> January 2003
//#               19195-19282 Unassigned
19283,//keysrvr         19283/tcp  Key Server for SASSAFRAS
19283,//keysrvr         19283/udp  Key Server for SASSAFRAS
//#                          Mark Valence <kurash&sassafras.com>
//#               19284-19314 Unassigned
19315,//keyshadow       19315/tcp  Key Shadow for SASSAFRAS
19315,//keyshadow       19315/udp  Key Shadow for SASSAFRAS
//#                          Mark Valence <kurash&sassafras.com>
//#               19316-19397 Unassigned
19398,//mtrgtrans       19398/tcp  mtrgtrans
19398,//mtrgtrans       19398/udp  mtrgtrans
//#                          Katsuhito Muroi <muroi&pfu.co.jp>
//#               19399-19409 Unassigned
19410,//hp-sco		19410/tcp  hp-sco 
//hp-sco		19410/udp  hp-sco
//hp-sca		19411/tcp  hp-sca
//hp-sca		19411/udp  hp-sca
//#			   Larry Schwartz <lrs&cup.hp.com>
//hp-sessmon      19412/tcp  HP-SESSMON
19412,//hp-sessmon      19412/udp  HP-SESSMON
//#                          Gita Murthy <gita&cup.hp.com> 
//#               19413-19538 Unassigned
19539,//fxuptp          19539/tcp  FXUPTP
//fxuptp          19539/udp  FXUPTP
//#                          Keiji Okuma <okuma&silex.jp> August 2005
//sxuptp          19540/tcp  SXUPTP
//sxuptp          19540/udp  SXUPTP
//#                          Keiji Okuma <okuma&silex.jp> August 2002
//jcp             19541/tcp  JCP Client
19541,//jcp             19541/udp  JCP Client
//#                          Yuji Sasaki <sasaki&silex.jp>
//#               19542-19998 Unassigned
19999,//dnp-sec         19999/tcp  Distributed Network Protocol - Secure
//dnp-sec         19999/udp  Distributed Network Protocol - Secure
//#                          Grant Gilchrist <grant&enernex.com> 04 August 2008
//dnp             20000/tcp  DNP
//dnp             20000/udp  DNP
//#                          Michael Thesing <michael.thesing&acsatlanta.com>
//microsan        20001/tcp  MicroSAN
//microsan        20001/udp  MicroSAN
//#                          Thomas E. Ludwig <tom.ludwig&zetera.com> February 2004
//commtact-http   20002/tcp  Commtact HTTP
//commtact-http   20002/udp  Commtact HTTP
//commtact-https  20003/tcp  Commtact HTTPS
20003,//commtact-https  20003/udp  Commtact HTTPS
//#                          Tomas Svoboda <svoboda&infima.cz> December 2004
//#               20004      Unassigned
20005,//openwebnet      20005/tcp  OpenWebNet protocol for electric network
20005,//openwebnet      20005/udp  OpenWebNet protocol for electric network
//#                          BTicino S.p.A. <admin-myopen&myopen-bticino.it> 09 April 2008
//#               20006-20013 Unassigned
20014,//opendeploy      20014/tcp  OpenDeploy Listener 
20014,//opendeploy      20014/udp  OpenDeploy Listener 
//#                          Todd Scallan <tscallan&interwoven.com> August 2005
//#               20015-20033 Unassigned
20034,//nburn_id        20034/tcp  NetBurner ID Port
20034,//nburn_id        20034/udp  NetBurner ID Port
//#                          Paul Breed <paul&netburner.com> November 2003
//#               20035-20048 Unassigned
20049,//nfsrdma         20049/tcp  Network File System (NFS) over RDMA
//nfsrdma         20049/udp  Network File System (NFS) over RDMA
20049,//nfsrdma         20049/sctp Network File System (NFS) over RDMA
//#                          [RFC-ietf-nfsv4-rpcrdma-09.txt]
//#               20050-20166 Unassigned
20167,//tolfab		20167/tcp   TOLfab Data Change
20167,//tolfab		20167/udp   TOLfab Data Change
//#			   Pierre Couderc <pcouderc&tol.fr> March 2006
//#               20168-20201 Unassigned
20202,//ipdtp-port      20202/tcp  IPD Tunneling Port
20202,//ipdtp-port      20202/udp  IPD Tunneling Port
//#                          Vikki Yin Wei <vikki&ipdynamics.com> January 2003
//#               20203-20221 Unassigned
20222,//ipulse-ics      20222/tcp  iPulse-ICS
20222,//ipulse-ics      20222/udp  iPulse-ICS
//#                          Meggie Garica-Woodruff <ipulse&ericsson.com>
//#               20223-20479 Unassigned
20480,//emwavemsg       20480/tcp  emWave Message Service
20480,//emwavemsg       20480/udp  emWave Message Service
//#                          Harald Striepe <harald&quantumintech.com> 14 February 2008
//#               20481-20669 Unassigned
20670,//track		20670/tcp  Track
20670,//track		20670/udp  Track
//#			   Michael Sweet <msweet&ctr.nawcad.navy.mil>	
//#               20671-20998 Unassigned
20999,//athand-mmp      20999/tcp  At Hand MMP
//athand-mmp      20999/udp  AT Hand MMP
//#                          Stepan Riha <stepan.riha&hand.com> 
//irtrans         21000/tcp  IRTrans Control
21000,//irtrans         21000/udp  IRTrans Control
//#                          Marcus Mueller <marcus&irtrans.de> November 2004
//#               21001-21553 Unassigned
21554,//dfserver	21554/tcp   MineScape Design File Server
21554,//dfserver	21554/udp   MineScape Design File Server
//#			   Michael Purser <mrp&mincom.com> June 2006
//#               21555-21589 Unassigned
21590,//vofr-gateway	21590/tcp  VoFR Gateway
21590,//vofr-gateway	21590/udp  VoFR Gateway
//#			   Marty Borden <mborden&tollbridgetech.com>
//#               21591-21799 Unassigned
21800,//tvpm            21800/tcp  TVNC Pro Multiplexing
21800,//tvpm            21800/udp  TVNC Pro Multiplexing
//#                          Brian Blevins <brian.blevins&tridia.com>
//#               21801-21844 Unassigned
21845,//webphone        21845/tcp  webphone
//webphone        21845/udp  webphone
//netspeak-is     21846/tcp  NetSpeak Corp. Directory Services
//netspeak-is     21846/udp  NetSpeak Corp. Directory Services
//netspeak-cs     21847/tcp  NetSpeak Corp. Connection Services
//netspeak-cs     21847/udp  NetSpeak Corp. Connection Services
//netspeak-acd    21848/tcp  NetSpeak Corp. Automatic Call Distribution
//netspeak-acd    21848/udp  NetSpeak Corp. Automatic Call Distribution
//netspeak-cps    21849/tcp  NetSpeak Corp. Credit Processing System
21849,//netspeak-cps    21849/udp  NetSpeak Corp. Credit Processing System
//#                          Toby Hosterman <root&netspeak.com>
//#               21850-21999 Unassigned  
22000,//snapenetio	22000/tcp  SNAPenetIO
//snapenetio	22000/udp  SNAPenetIO
//optocontrol	22001/tcp  OptoControl
//optocontrol	22001/udp  OptoControl
//#			   Kevin Kuhns <kkuhns&opto22.com>
//optohost002	22002/tcp  Opto Host Port 2
//optohost002	22002/udp  Opto Host Port 2
//optohost003	22003/tcp  Opto Host Port 3
//optohost003	22003/udp  Opto Host Port 3
//optohost004	22004/tcp  Opto Host Port 4
//optohost004	22004/udp  Opto Host Port 4
//optohost004	22005/tcp  Opto Host Port 5
22005,//optohost004	22005/udp  Opto Host Port 5
//#			   Doug Leany <DLEANY&Opto22.com> September 2006
//#               22006-22124 Unassigned
22125,//dcap            22125/tcp  dCache Access Protocol
//#                          Christoph Anton Mitterer <calestyo&scientia.net> 10 March 2009
22125,//#               22125/udp  Reserved
//#               22126-22127 Unassigned
22128,//gsidcap         22128/tcp  GSI dCache Access Protocol
//#                          Christoph Anton Mitterer <calestyo&scientia.net> 10 March 2009
22128,//#               22128/udp  Reserved
//#               22129-22272 Unassigned
22273,//wnn6            22273/tcp  wnn6
22273,//wnn6            22273/udp  wnn6
//#                          Yasunari Gon Yamasita <yamasita&omronsoft.co.jp>
//#               22274-22304 Unassigned
22305,//cis		22305/tcp  CompactIS Tunnel
22305,//cis		22305/udp  CompactIS Tunnel
//#			   Justin Paupore <jpaupore&blueshiftlabs.net> 16 August 2007
//#               22306-22342 Unassigned
22343,//cis-secure	22343/tcp  CompactIS Secure Tunnel
22343,//cis-secure	22343/udp  CompactIS Secure Tunnel
//#			   Justin Paupore <jpaupore&blueshiftlabs.net> 16 August 2007
//#               22344-22346 Unassigned
22347,//WibuKey		22347/tcp  WibuKey Standard WkLan 
22347,//WibuKey		22347/udp  WibuKey Standard WkLan 
//#			   Wolfgang Voelker <wolfgang.voelker&wibu.com> June 2007
//#               22348-22349 Unassigned
22350,//CodeMeter	22350/tcp  CodeMeter Standard 
22350,//CodeMeter	22350/udp  CodeMeter Standard 
//#			   Wolfgang Voelker <wolfgang.voelker&wibu.com> June 2007
//#               22351-22554 Unassigned
22555,//vocaltec-wconf  22555/tcp  Vocaltec Web Conference
22555,//vocaltec-phone  22555/udp  Vocaltec Internet Phone
//#                          Scott Petrack <Scott_Petrack&vocaltec.com>
//#               22556-22762 Unassigned
22763,//talikaserver	22763/tcp  Talika Main Server
22763,//talikaserver	22763/udp  Talika Main Server
//#			   Laxman C. Marathe <lcmarathe&thomsonpress.com> December 2006
//#               22764-22799 Unassigned
22800,//aws-brf         22800/tcp  Telerate Information Platform LAN
22800,//aws-brf         22800/udp  Telerate Information Platform LAN
//#                          Timo Sivonen <timo.sivonen&ccmail.dowjones.com>
//#               22801-22950 Unassigned
22951,//brf-gw          22951/tcp  Telerate Information Platform WAN
22951,//brf-gw          22951/udp  Telerate Information Platform WAN
//#                          Timo Sivonen <timo.sivonen&ccmail.dowjones.com>
//#               22952-22999 Unassigned
23000,//inovaport1	23000/tcp  Inova LightLink Server Type 1
//inovaport1	23000/udp  Inova LightLink Server Type 1
//inovaport2	23001/tcp  Inova LightLink Server Type 2
//inovaport2	23001/udp  Inova LightLink Server Type 2
//inovaport3	23002/tcp  Inova LightLink Server Type 3
//inovaport3	23002/udp  Inova LightLink Server Type 3
//inovaport4	23003/tcp  Inova LightLink Server Type 4
//inovaport4	23003/udp  Inova LightLink Server Type 4
//inovaport5	23004/tcp  Inova LightLink Server Type 5
//inovaport5	23004/udp  Inova LightLink Server Type 5
//inovaport6	23005/tcp  Inova LightLink Server Type 6
23005,//inovaport6	23005/udp  Inova LightLink Server Type 6
//#			   Chris Koeritz <portmanager&inovasolutions.com> October 2006
//#               23006-23332 Unassigned
23333,//elxmgmt		23333/tcp  Emulex HBAnyware Remote Management 
23333,//elxmgmt		23333/udp  Emulex HBAnyware Remote Management 
//#			   Maziar Tamadon <maziar.tamadon&emulex.com> 06 November 2007
//#               23334-23399 Unassigned
23400,//novar-dbase	23400/tcp  Novar Data
//novar-dbase	23400/udp  Novar Data
//novar-alarm	23401/tcp  Novar Alarm 
//novar-alarm	23401/udp  Novar Alarm 
//novar-global	23402/tcp  Novar Global
23402,//novar-global	23402/udp  Novar Global
//#			   Keith Kilroy <Keith.Kilroy&novarcontrols.com> February 2006
//#               23403-23455 Unassigned
23456,//aequus          23456/tcp  Aequus Service 
//#                          James Anson <janson&bigpond.com> 12 February 2009
//#               23456/udp  Reserved
23457,//aequus-alt      23457/tcp  Aequus Service Mgmt
//#                          James Anson <janson&bigpond.com> 12 February 2009
//#               23457/udp  Reserved
//#               23458-23999 Unassigned
24000,//med-ltp		24000/tcp  med-ltp
//med-ltp		24000/udp  med-ltp
//med-fsp-rx	24001/tcp  med-fsp-rx
//med-fsp-rx	24001/udp  med-fsp-rx
//med-fsp-tx	24002/tcp  med-fsp-tx
//med-fsp-tx	24002/udp  med-fsp-tx
//med-supp	24003/tcp  med-supp
//med-supp	24003/udp  med-supp
//med-ovw		24004/tcp  med-ovw
//med-ovw		24004/udp  med-ovw
//med-ci		24005/tcp  med-ci
//med-ci		24005/udp  med-ci
24006,//med-net-svc	24006/tcp  med-net-svc
//med-net-svc	24006/udp  med-net-svc
//#			   Juergen Fischbach <juergen.fischbach&philips.com>
//#               24007-24241 Unassigned
24242,//filesphere      24242/tcp  fileSphere
24242,//filesphere      24242/udp  fileSphere
//#                          Carl Cedergren <asperon&home.se>
//#               24243-24248 Unassigned
24249,//vista-4gl       24249/tcp Vista 4GL
24249,//vista-4gl       24249/udp Vista 4GL
//#                         Mark Itzcovitz <mji&vistacomp.com>
//#               24250-24320 Unassigned
24321,//ild             24321/tcp  Isolv Local Directory
24321,//ild             24321/udp  Isolv Local Directory
//#                          Mitchell Bass <mitch&integrasolv.com> August 2005
//#               24322-24385 Unassigned
24386,//intel_rci	24386/tcp Intel RCI 
24386,//intel_rci	24386/udp Intel RCI
//#			  Mark Lewis <mark.h.lewis&intel.com> 
//#               24387-24464   Unassigned
24465,//tonidods        24465/tcp Tonido Domain Server
24465,//tonidods        24465/udp Tonido Domain Server
//#                         Madhan Kanagavel <madhan&codelathe.com> 18 July 2008
//#               24466-24553   Unassigned
24554,//binkp           24554/tcp BINKP
24554,//binkp           24554/udp BINKP
//#                         Max Masyutin <max&ritlabs.com>
//#               24555-24675 Unassigned
24676,//canditv         24676/tcp Canditv Message Service
//canditv         24676/udp Canditv Message Service
//#                         Gary Aston <Gary.Aston&DataDrivenLogistics.com> 10 March 2009
//flashfiler      24677/tcp FlashFiler
//flashfiler      24677/udp FlashFiler
//#                         Ben Oram <beno&turbopower.com>  
//proactivate     24678/tcp Turbopower Proactivate
24678,//proactivate     24678/udp Turbopower Proactivate
//#                         Ben Oram <beno&turbopower.com>
//#               24679     Unassigned
24680,//tcc-http	24680/tcp TCC User HTTP Service
24680,//tcc-http	24680/udp TCC User HTTP Service
//#			  Brian Kennedy <BrianK&TargetedConvergence.com> August 2006
//#               24681-24753 Unassigned
24754,//cslg            24754/tcp Citrix StorageLink Gateway
//#                         Mark Nijmeijer <Mark.Nijmeijer&citrix.com> 17 April 2009
24754,//#               24754/udp Reserved
//#               24755-24921 Unassigned
24922,//find            24922/tcp Find Identification of Network Devices
24922,//find            24922/udp Find Identification of Network Devices
//#                         Jean-Paul Moreaux 
//#                         <jean-paul.moreaux&airbus.com>
//#               24923-24999 Unassigned 
25000,//icl-twobase1    25000/tcp  icl-twobase1
//icl-twobase1    25000/udp  icl-twobase1
//icl-twobase2    25001/tcp  icl-twobase2
//icl-twobase2    25001/udp  icl-twobase2
//icl-twobase3    25002/tcp  icl-twobase3
//icl-twobase3    25002/udp  icl-twobase3
//icl-twobase4    25003/tcp  icl-twobase4
//icl-twobase4    25003/udp  icl-twobase4
//icl-twobase5    25004/tcp  icl-twobase5
//icl-twobase5    25004/udp  icl-twobase5
//icl-twobase6    25005/tcp  icl-twobase6
//icl-twobase6    25005/udp  icl-twobase6
//icl-twobase7    25006/tcp  icl-twobase7
//icl-twobase7    25006/udp  icl-twobase7
//icl-twobase8    25007/tcp  icl-twobase8
//icl-twobase8    25007/udp  icl-twobase8
//icl-twobase9    25008/tcp  icl-twobase9
//icl-twobase9    25008/udp  icl-twobase9
//icl-twobase10   25009/tcp  icl-twobase10
25009,//icl-twobase10   25009/udp  icl-twobase10
//#                          J. A. (Tony) Sever <J.A.Sever&bra0119.wins.icl.co.uk>
//#               25010-25792 Unassigned 
25793,//vocaltec-hos    25793/tcp  Vocaltec Address Server      
25793,//vocaltec-hos    25793/udp  Vocaltec Address Server
//#                          Scott Petrack <Scott_Petrack&vocaltec.com>
//#               25794-25899 Unassigned
25900,//tasp-net        25900/tcp  TASP Network Comm
//tasp-net        25900/udp  TASP Network Comm
//#                          Martin Ellis <martin&clanleagues.net> November 2004
//niobserver      25901/tcp  NIObserver
//niobserver      25901/udp  NIObserver
//#                          Roman Oliynyk <romano&netinst.com>
//nilinkanalyst	25902/tcp  NILinkAnalyst
//nilinkanalyst	25902/tcp  NILinkAnalyst
//#			   Roman Oliynyk <roman&netinst.com> 30 August 2007
//niprobe         25903/tcp  NIProbe
25903,//niprobe         25903/udp  NIProbe
//#                          Roman Oliynyk <romano&netinst.com>
//#               25904-25999 Unassigned
26000,//quake           26000/tcp  quake
26000,//quake           26000/udp  quake
//#                          Yasunari Gon Yamasita <yamasita&omronsoft.co.jp>  
//#               26001-26132 Unassigned
26133,//scscp		26133/tcp  Symbolic Computation Software Composability Protocol
26133,//scscp		26133/udp  Symbolic Computation Software Composability Protocol
//#			   Alexander Konovalov <konovalov&member.ams.org> 27 November 2007
//#               26134-26207 Unassigned
26208,//wnn6-ds         26208/tcp  wnn6-ds
26208,//wnn6-ds         26208/udp  wnn6-ds
//#                          Yasunari Gon Yamasita <yamasita&omronsoft.co.jp>
//#               26209-26259 Unassigned
26260,//ezproxy         26260/tcp  eZproxy
//ezproxy         26260/udp  eZproxy
//ezmeeting       26261/tcp  eZmeeting
//ezmeeting       26261/udp  eZmeeting
//#                          Albert C. Yang <albert.yang&eZmeeting.com>
//k3software-svr  26262/tcp  K3 Software-Server
//k3software-svr  26262/udp  K3 Software-Server
//k3software-cli  26263/tcp  K3 Software-Client
//k3software-cli  26263/udp  K3 Software-Client
//#                          Jim Baldridge <jimb&rpower.com>
26264,//#		26264      De-registered (6 April 2006)
//#               26265-26485 Unassigned
26486,//exoline-tcp	26486/tcp  EXOline-TCP 
//exoline-udp	26486/udp  EXOline-UDP
//#			   Previous contact: Lars Mattsson <lars.mattsson&reginexomatic.com> May 2006
//#                      Current contact: Lars Mattsson <lars.mattsson&regin.se> 24 December 2008
//exoconfig	26487/tcp  EXOconfig
26487,//exoconfig	26487/udp  EXOconfig
//#			   Previous contact: Urban Fosseus <urban.fosseus&reginexomatic.com> May 2006
//#                          Current contact: Urban Fosseus <urban.fosseus&regin.se> 24 December 2008
//#               26488      Unassigned
26489,//exonet		26489/tcp  EXOnet
26489,//exonet		26489/udp  EXOnet
//#			   Previous contact: Urban Fosseus <urban.fosseus&reginexomatic.com> May 2006
//#                          Current contact: Urban Fosseus <urban.fosseus&regin.se> 24 December 2008
//#               26490-26999 Unassigned
27000,//flex-lm		27000-27009 FLEX LM (1-10)
27009,//#			   Daniel Birns <daniel&globes.com>
//#               27010-27344 Unassigned
27345,//imagepump       27345/tcp  ImagePump
27345,//imagepump       27345/udp  ImagePump
//#                          Richard Minner <xippix.com>
//#               27346-27441 Unassigned
27442,//jesmsjc		27442/tcp  Job controller service
27442,//jesmsjc		27442/udp  Job controller service
//#			   Peter Coates <peter.coates&sun.com> April 2006
//#               27443-27503 Unassigned
27504,//kopek-httphead  27504/tcp  Kopek HTTP Head Port
27504,//kopek-httphead  27504/udp  Kopek HTTP Head Port
//#                          Sten H. Danielsen <shd&kopek.net> July 2002
//#               27505-27781 Unassigned
27782,//ars-vista       27782/tcp  ARS VISTA Application
27782,//ars-vista       27782/udp  ARS VISTA Application
//#                          Spencer Teran <steran&ars.com> November 2004
//#               27783-27998 Unassigned
27999,//tw-auth-key     27999/tcp  TW Authentication/Key Distribution and 
//tw-auth-key     27999/udp  Attribute Certificate Services
//#                          Alex Duncan <Alex.Duncan&sse.ie>
//nxlmd           28000/tcp   NX License Manager
28000,//nxlmd           28000/udp   NX License Manager
//#                           Anthony Greatorex <greatore&ugs.com> November 2004
//#               28001-28239 Unassigned
28240,//siemensgsm      28240/tcp   Siemens GSM
28240,//siemensgsm      28240/udp   Siemens GSM
//#                           David Anuszewski <david.anuszewski&siemens.com> November 2004
//#               28241-29117 Unassigned
29118,//#               29118/tcp   Reserved
//#               29118/udp   Reserved
29118,//sgsap           29118/sctp  SGsAP in 3GPP
//#                           3GPP Specifications Manager (John M Meredith)
//#                           <john.meredith&etsi.org> 11 June 2009
//#               28119-29166 Unassigned
29167,//otmp		29167/tcp   ObTools Message Protocol
//otmp		29167/udp   ObTools Message Protocol
//#			    Paul Clark <paul&xmill.com> February 2006
//#               29168/tcp   Reserved
//#               29168/udp   Reserved
//sbcap           29168/sctp  SBcAP in 3GPP
//#                           3GPP Specifications Manager (John M Meredith)
29169,//#                           <john.meredith&etsi.org> 11 June 2009
//#               29169-30000 Unassigned
30001,//pago-services1  30001/tcp   Pago Services 1
//pago-services1  30001/udp   Pago Services 1
//pago-services2  30002/tcp   Pago Services 2
//pago-services2  30002/udp   Pago Services 2
//#                           Balduin Mueller-Platz 
30002,//#                           <balduin.mueller-platz&pago.de> March 2002
//#               30003-30998 Unassigned
30999,//ovobs		30999/tcp   OpenView Service Desk Client
30999,//ovobs		30999/udp   OpenView Service Desk Client
//#			    Service Desk Product Manager <info&hp.com> May 2006
//#               31000-31019 Unassigned
31020,//autotrac-acp    31020/tcp   Autotrac ACP 245
//#                           Roberto Jorge Dino <roberto.dino&autotrac.com.br>
31020,//#               31020/udp   Reserved
//#               31021-31415 Unassigned
31416,//xqosd           31416/tcp   XQoS network monitor
31416,//xqosd           31416/udp   XQoS network monitor
//#                           Joe Elliott <joe&inetd.com> June 2002
//#               31417-31456 Unassigned
31457,//tetrinet        31457/tcp   TetriNET Protocol
31457,//tetrinet        31457/udp   TetriNET Protocol
//#                           Emmanuel Bourg <smanux&lfjr.net> November 2004
//#               31458-31619 Unassigned
31620,//lm-mon          31620/tcp   lm mon
31620,//lm-mon          31620/udp   lm mon
//#                           System Administrator <sysadmin&silvaco.com> June 2003
//#               31621-31684 Unassigned
31685,//dsx_monitor     31685/tcp   DS Expert Monitor
//#                           John Lowery, NetPro Computing, <jlowery&netpro.com> 21 August 2008
31685,//#               31685/udp   Reserved
//#               31686-31764 Unassigned
31765,//gamesmith-port  31765/tcp   GameSmith Port
31765,//gamesmith-port  31765/udp   GameSmith Port
//#                           Randy Thompson <thompr&earthlink.net> August 2002
//#               31766-31947 Unassigned
31948,//iceedcp_tx	31948/tcp   Embedded Device Configuration Protocol TX
//iceedcp_tx	31948/udp   Embedded Device Configuration Protocol TX
//iceedcp_rx	31949/tcp   Embedded Device Configuration Protocol RX
31949,//iceedcp_rx	31949/udp   Embedded Device Configuration Protocol RX
//#			    Oliver Lewis <o.lewis&icerobotics.co.uk> August 2006
//#               31950-32248 Unassigned
32034,//iracinghelper	32034/tcp   iRacing helper service
32034,//iracinghelper	32034/udp   iRacing helper service
//#			    Randy Cassidy <randy.cassidy&iracing.com> 30 August 2007
//#               31950-32248 Unassigned
32249,//t1distproc60    32249/tcp   T1 Distributed Processor
32249,//t1distproc60    32249/udp   T1 Distributed Processor
//#                           Peter Beahan <peter_beahan&technologyonecorp.com> November 2004
//#               32250-32482 Unassigned
32483,//apm-link        32483/tcp   Access Point Manager Link
32483,//apm-link        32483/udp   Access Point Manager Link
//#                           Tony Diodato <tdiodato&cyprx.com> August 2005
//#               32484-32634 Unassigned
32635,//sec-ntb-clnt    32635/tcp   SecureNotebook-CLNT
//sec-ntb-clnt    32635/udp   SecureNotebook-CLNT
//#                           Eric Cantineau <eric&securenotebook.com> November 2004
//DMExpress	32636/tcp   DMExpress
32636,//DMExpress	32636/udp   DMExpress
//#			    Arnie Farrelly <afarrelly&syncsort.com>
//#			    <gspaulding&syncsort.com> 18 July 2007
//#               32637-32766 Unassigned
32767,//filenet-powsrm  32767/tcp   FileNet BPM WS-ReliableMessaging Client 
//filenet-powsrm  32767/udp   FileNet BPM WS-ReliableMessaging Client 
//#			    Chris Adkins <cadkins&filenet.com> August 2006
//filenet-tms     32768/tcp   Filenet TMS
//filenet-tms     32768/udp   Filenet TMS
//filenet-rpc     32769/tcp   Filenet RPC
//filenet-rpc     32769/udp   Filenet RPC
//filenet-nch     32770/tcp   Filenet NCH
//filenet-nch     32770/udp   Filenet NCH
//#                           Daniel Whelan <dwhelan&filenet.com>	
//filenet-rmi     32771/tcp   FileNET RMI
//filenet-rmi     32771/udp   FileNet RMI
//#                           Chris Adkins <cadkins&filenet.com>
//filenet-pa      32772/tcp   FileNET Process Analyzer 
//filenet-pa      32772/udp   FileNET Process Analyzer
//#                           Chris Adkins <cadkins&filenet.com> January 2003
//filenet-cm      32773/tcp   FileNET Component Manager
//filenet-cm      32773/udp   FileNET Component Manager
//#                           Chris Adkins <cadkins&filenet.com> August 2003
//filenet-re      32774/tcp   FileNET Rules Engine
//filenet-re      32774/udp   FileNET Rules Engine
//#                           Chris Adkins <cadkins&filenet.com> August 2003
//filenet-pch     32775/tcp   Performance Clearinghouse
//filenet-pch     32775/udp   Performance Clearinghouse
//#                           Tim Morgan <tmorgan&filenet.com> November 2005
//filenet-peior   32776/tcp   FileNET BPM IOR 
//filenet-peior   32776/udp   FileNET BPM IOR 
//#			    Chris Adkins <cadkins&filenet.com> May 2006
//filenet-obrok	32777/tcp   FileNet BPM CORBA
32777,//filenet-obrok	32777/udp   FileNet BPM CORBA
//#			   Chris Adkins <cadkins&filenet.com> October 2006
//#               32778-32895 Unassigned
32896,//idmgratm        32896/tcp   Attachmate ID Manager
32896,//idmgratm        32896/udp   Attachmate ID Manager
//#                           George Gianelos <GeorgeGi&Attachmate.com> March 2003
//#               32897-33122 Unassigned
33123,//aurora-balaena  33123/tcp   Aurora (Balaena Ltd)
33123,//aurora-balaena  33123/udp   Aurora (Balaena Ltd)
//#                           Andrew Mather <info&balaena.com> 14 February 2008
//#               33124-33330 Unassigned
33331,//diamondport     33331/tcp   DiamondCentral Interface
33331,//diamondport     33331/udp   DiamondCentral Interface
//#                           Edward Browdy <ebrowdy&cryptek.com> July 2002
//#               33332-33433 Unassigned
33434,//traceroute      33434/tcp   traceroute use
33434,//traceroute      33434/udp   traceroute use
//#                           IANA <iana&iana.org>
//#               33435-33655 Unassigned
33656,//snip-slave      33656/tcp   SNIP Slave 
33656,//snip-slave      33656/udp   SNIP Slave 
//#                           Dr. Chris Tucker <chris.tucker&ioltd.co.uk> August 2005
//#               33657-34248 Unassigned
34249,//turbonote-2     34249/tcp   TurboNote Relay Server Default Port
34249,//turbonote-2     34249/udp   TurboNote Relay Server Default Port
//#                           Peter Hyde <peter&spis.co.nz>
//#               34250-34377 Unassigned
34378,//p-net-local     34378/tcp   P-Net on IP local 
//p-net-local     34378/udp   P-Net on IP local
//#                           Kurt Nissen <kn&proces-data.com> February 2004
//p-net-remote    34379/tcp   P-Net on IP remote
34379,//p-net-remote    34379/udp   P-Net on IP remote
//#                           Kurt Nissen <kn&proces-data.com> February 2004
//#               34380-34961 Unassigned
34962,//profinet-rt     34962/tcp   PROFInet RT Unicast
//profinet-rt     34962/udp   PROFInet RT Unicast
//profinet-rtm    34963/tcp   PROFInet RT Multicast
//profinet-rtm    34963/udp   PROFInet RT Multicast
//profinet-cm     34964/tcp   PROFInet Context Manager
34964,//profinet-cm     34964/udp   PROFInet Context Manager
//#                           Peter Wenzel <Peter.Wenzel&profibus.com> November 2004
//#               34965-34979 Unassigned
34980,//ethercat        34980/tcp   EtherCAT Port
34980,//ethercat        34980/udp   EhterCAT Port
//#                           Martin Rostan <m.rostan&beckhoff.com> November 2003
//#               34981-36000 Unassigned
36001,//allpeers	36001/tcp   AllPeers Network
36001,//allpeers	36001/udp   AllPeers Network
//#			    Cedric Maloux <cedric&allpeers.com> April 2007
//#               36002-36864 Unassigned
36865,//kastenxpipe     36865/tcp   KastenX Pipe
36865,//kastenxpipe     36865/udp   KastenX Pipe
//#                           Guy Cheng <GCHE&kastenchase.com>
//#               36866-37474 Unassigned
37475,//neckar          37475/tcp   science + computing's Venus Administration Port
37475,//neckar          37475/udp   science + computing's Venus Administration Port
//#                           Ralf Allrutz <R.Allrutz&science-computing.de> February 2002
//#               37476-37653 Unassigned
37654,//unisys-eportal  37654/tcp   Unisys ClearPath ePortal
37654,//unisys-eportal  37654/udp   Unisys ClearPath ePortal
//#			    Sung U. Ro <ePortalSupport&unisys.com> January 2006
//#               37655-38200 Unassigned
38201,//galaxy7-data    38201/tcp   Galaxy7 Data Tunnel
//galaxy7-data    38201/udp   Galaxy7 Data Tunnel
//#                           Tatham Oddie <tatham&e-oddie.com> September 2002
//fairview        38202/tcp   Fairview Message Service
//fairview        38202/udp   Fairview Message Service
//#                           Jim Lyle <jim.lyle&siliconimage.com> November 2005
//agpolicy        38203/tcp   AppGate Policy Server
38203,//agpolicy        38203/udp   AppGate Policy Server
//#                           Martin Forssen <maf&appgate.com> November 2004
//#               38204-39680 Unassigned
39681,//turbonote-1     39681/tcp   TurboNote Default Port
39681,//turbonote-1     39681/udp   TurboNote Default Port
//#                           Peter Hyde <peter&spis.co.nz>
//#               39682-39999 Unassigned
40000,//safetynetp	40000/tcp   SafetyNET p
40000,//safetynetp	40000/udp   SafetyNET p
//#			    Roland Rupp <r.rupp&pilz.de> November 2006
//#               40001-40840 Unassigned
40841,//cscp            40841/tcp   CSCP
//cscp            40841/udp   CSCP
//#                           Michael Dodge <sarge&centerspan.com>      
//csccredir       40842/tcp   CSCCREDIR
//csccredir       40842/udp   CSCCREDIR
//csccfirewall    40843/tcp   CSCCFIREWALL
40843,//csccfirewall    40843/udp   CSCCFIREWALL
//#                           Sudhir Menon <sudhir&centerspan.com>
//#               40844-41110 Unassigned
41111,//fs-qos          41111/tcp   Foursticks QoS Protocol
41111,//fs-qos          41111/udp   Foursticks QoS Protocol
//#                           Chee Kent Lam <cklam&foursticks.com> April 2002
//#               41112-41120 Unassigned
41121,//tentacle        41121/tcp   Tentacle Server
//#                           Sancho Lerena <slerena&artica.es> 02 June 2009
41121,//#               41121/udp   Reserved
//#               41122-41793 Unassigned
41794,//crestron-cip    41794/tcp   Crestron Control Port
//crestron-cip    41794/udp   Crestron Control Port
//crestron-ctp    41795/tcp   Crestron Terminal Port
41795,//crestron-ctp    41795/udp   Crestron Terminal Port
//#                           Ed Ranney <eranney&crestron.com> January 2003
//#               41796-42507 Unassigned
42508,//candp           42508/tcp   Computer Associates network discovery protocol
//candp           42508/udp   Computer Associates network discovery protocol
//#                           Jon Press <IANA.Registions&ca.com> September 2005
//candrp          42509/tcp   CA discovery response
//candrp          42509/udp   CA discovery response
//caerpc          42510/tcp   CA eTrust RPC
42510,//caerpc          42510/udp   CA eTrust RPC
//#                           Jon Press <IANA.Registions&ca.com> August 2005
//#               42511-43187 Unassigned
43188,//reachout        43188/tcp   REACHOUT
//reachout        43188/udp   REACHOUT
//ndm-agent-port  43189/tcp   NDM-AGENT-PORT
//ndm-agent-port  43189/udp   NDM-AGENT-PORT
//ip-provision    43190/tcp   IP-PROVISION
//ip-provision    43190/udp   IP-PROVISION
//#                           Roman Kriis <roman&previo.ee>
//noit-transport  43191/tcp   Reconnoiter Agent Data Transport
//#                           Theo Schlossnagle <jesus&omniti.com> 19 May 2009
43191,//#               43191/udp   Reserved
//#               43192-43439 Unassigned
43440,//ew-mgmt         43440/tcp   Cisco EnergyWise Management
//ew-disc-cmd     43440/udp   Cisco EnergyWise Discovery and Command Flooding 
//#                           John Parello <jparello&cisco.com> 19 May 2009
//ciscocsdb       43441/tcp   Cisco NetMgmt DB Ports
43441,//ciscocsdb       43441/udp   Cisco NetMgmt DB Ports
//#                           Cisco Systems <nmtg-port-numbers&cisco.com> November 2005
//#               43442-44320 Unassigned
44321,//pmcd            44321/tcp   PCP server (pmcd)
//pmcd            44321/udp   PCP server (pmcd)
//#                           Ken McDonell <kenmcd&sgi.com> June 2002
//pmcdproxy       44322/tcp   PCP server (pmcd) proxy
44322,//pmcdproxy       44322/udp   PCP server (pmcd) proxy
//#                           Ken McDonnell <kenmcd&sgi.com> July 2003
//#               44323-44552 Unassigned
44553,//rbr-debug       44553/tcp   REALbasic Remote Debug
44553,//rbr-debug       44553/udp   REALbasic Remote Debug
//#                           Aaron Ballman <aaron&realsoftware.com> November 2004
//#               44554-44817 Unassigned
44818,//EtherNet/IP-2   44818/tcp   EtherNet/IP messaging
44818,//EtherNet/IP-2   44818/udp   EtherNet/IP messaging
//#                           Brian Batke <eip.jsig&gmail.com>
//#                           New contact added for port 44818 on 2008-02-01
//#               44819-45053 Unassigned
45054,//invision-ag     45054/tcp   InVision AG 
45054,//invision-ag     45054/udp   InVision AG
//#                           Matthias Schroer <matthias.schroer&invision.de>
//#               45055-45677 Unassigned
//eba             45678/tcp   EBA PRISE
//eba             45678/udp   EBA PRISE
//#                           Patrick Kara <Patrick&EBA.NET>
//#               45679-45824 Unassigned
45825,//qdb2service	45825/tcp   Qpuncture Data Access Service
45825,//qdb2service	45825/tcp   Qpuncture Data Access Service
//#			    Michael Yun <cinnanda&gmail.com> 24 October 2007
//#               45826-45965 Unassigned
45966,//ssr-servermgr   45966/tcp   SSRServerMgr
45966,//ssr-servermgr   45966/udp   SSRServerMgr
//#                           Jeremy Gilliat <jeremy.gilliat&geac.com>
//#               45967-46998 Unassigned
46999,//mediabox        46999/tcp   MediaBox Server
//mediabox        46999/udp   MediaBox Server
//#                           Alexander Graef <alex&graef.cc> November 2004
//mbus            47000/tcp   Message Bus
//mbus            47000/udp   Message Bus
//#                           Dirk Kutscher <dku&informatik.uni-bremen.de> 
//winrm           47001/tcp   Windows Remote Management Service
//#                           Ryan Mack <rmack&microsoft.com> 29 April 2009
47001,//#               47001/udp   Reserved
//#               47002-47556 Unassigned
47557,//dbbrowse        47557/tcp   Databeam Corporation
47557,//dbbrowse        47557/udp   Databeam Corporation
//#                           Cindy Martin <cmartin&databeam.com>
//#               47558-47623 Unassigned
47624,//directplaysrvr  47624/tcp   Direct Play Server
47624,//directplaysrvr  47624/udp   Direct Play Server
//#                           Ajay Jindal <ajayj&microsoft.com>
//#               47625-47805 Unassigned
47806,//ap              47806/tcp   ALC Protocol
47806,//ap              47806/udp   ALC Protocol
//#                           Dave Robin <iana_ports&daverobin.com>
//#               47807       Unassigned
47808,//bacnet          47808/tcp   Building Automation and Control Networks
47808,//bacnet          47808/udp   Building Automation and Control Networks
//#                           H. Michael Newman <hmn2&cornell.edu>
//#               47809-47999 Unassigned
48000,//nimcontroller   48000/tcp   Nimbus Controller
//nimcontroller   48000/udp   Nimbus Controller
//nimspooler      48001/tcp   Nimbus Spooler
//nimspooler      48001/udp   Nimbus Spooler
//nimhub          48002/tcp   Nimbus Hub
//nimhub          48002/udp   Nimbus Hub
//nimgtw          48003/tcp   Nimbus Gateway
48003,//nimgtw          48003/udp   Nimbus Gateway
//#                           Carstein Seeberg <case&nimsoft.no>
//#               48004-48127 Unassigned
48128,//isnetserv	48128/tcp   Image Systems Network Services
//isnetserv	48128/udp   Image Systems Network Services
//#			    Bengt Gustafsson <bengt.gustafsson&imagesystems.se> May 2006
//blp5		48129/tcp   Bloomberg locator
48129,//blp5		48129/udp   Bloomberg locator
//#			    Albert Hou <ahou1&bloomberg.com> May 2006
//#               48130-48555 Unassigned
48556,//com-bardac-dw   48556/tcp   com-bardac-dw
48556,//com-bardac-dw   48556/udp   com-bardac-dw
//#                           Nicholas J Howes <nick&ghostwood.org>
//#               48557-48618 Unassigned 
48619,//iqobject        48619/tcp  iqobject
48619,//iqobject        48619/udp  iqobject
//#                           Bjorn de Bonnenfant <bdeb&iqobject.com> November 2003
//#               48620-49150 Unassigned
49151,//#               49151       IANA Reserved
49151,//
//DYNAMIC AND/OR PRIVATE PORTS
//
//The Dynamic and/or Private Ports are those from 49152 through 65535
49152,//
65535,//
//}