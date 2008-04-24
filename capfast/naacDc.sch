[schematic2]
uniq 217
[tools]
[detail]
w 1176 2107 100 0 n#215 eapply.apply.CLID -480 1568 -772 1568 -772 2240 800 2240 800 2144 1056 2144 1056 2096 1224 2096 sysCar.sysCar#174.CLID
w 100 987 100 0 n#209 eapply.apply.OUTF -96 1184 96 1184 96 800 288 800 noOpApply.noOpApply#182.DIR
w 2 1259 100 0 n#207 eapply.apply.OUTE -96 1248 160 1248 160 1024 288 1024 stateApply.stateApply#181.DIR
w 34 1323 100 0 n#202 eapply.apply.OUTD -96 1312 224 1312 224 1248 288 1248 sysApply.sysApply#183.DIR
w 34 1387 100 0 n#201 eapply.apply.OUTC -96 1376 224 1376 224 1472 288 1472 drRoiCad.drRoiCad#180.DIR
w 18 1451 100 0 n#200 eapply.apply.OUTB -96 1440 192 1440 192 1696 288 1696 obsSetupCad.obsSetupCad#177.DIR
w 164 1707 100 0 n#199 eapply.apply.OUTA -96 1504 160 1504 160 1920 288 1920 arSetupCad.arSetupCad#175.DIR
w -62 515 100 0 n#198 eapply.apply.INMF -480 1152 -640 1152 -640 512 576 512 576 768 448 768 noOpApply.noOpApply#182.MESS
w -62 547 100 0 n#197 noOpApply.noOpApply#182.VAL 448 800 544 800 544 544 -608 544 -608 1184 -480 1184 eapply.apply.INPF
w -62 587 100 0 n#196 stateApply.stateApply#181.VAL 448 1024 512 1024 512 576 -576 576 -576 1248 -480 1248 eapply.apply.INPE
w -62 619 100 0 n#195 eapply.apply.INME -480 1216 -544 1216 -544 608 480 608 480 992 448 992 stateApply.stateApply#181.MESS
w -46 2219 100 0 n#192 sysApply.sysApply#183.MESS 448 1216 704 1216 704 2208 -736 2208 -736 1280 -480 1280 eapply.apply.INMD
w -46 2123 100 0 n#191 drRoiCad.drRoiCad#180.VAL 448 1472 608 1472 608 2112 -640 2112 -640 1376 -480 1376 eapply.apply.INPC
w -46 2187 100 0 n#190 sysApply.sysApply#183.VAL 448 1248 672 1248 672 2176 -704 2176 -704 1312 -480 1312 eapply.apply.INPD
w -46 2155 100 0 n#189 drRoiCad.drRoiCad#180.MESS 448 1440 640 1440 640 2144 -672 2144 -672 1344 -480 1344 eapply.apply.INMC
w -46 2091 100 0 n#187 obsSetupCad.obsSetupCad#177.MESS 448 1664 576 1664 576 2080 -608 2080 -608 1408 -480 1408 eapply.apply.INMB
w -46 2059 100 0 n#186 obsSetupCad.obsSetupCad#177.VAL 448 1696 544 1696 544 2048 -576 2048 -576 1440 -480 1440 eapply.apply.INPB
w -46 2027 100 0 n#185 arSetupCad.arSetupCad#175.MESS 448 1888 512 1888 512 2016 -544 2016 -544 1472 -480 1472 eapply.apply.INMA
w -46 1995 100 0 n#213 arSetupCad.arSetupCad#175.VAL 448 1920 480 1920 480 1984 -512 1984 -512 1504 -480 1504 eapply.apply.INPA
[cell use]
use elongins 896 1479 100 0 masterEnable
xform 0 1024 1552
use CBorder -952 -40 -100 0 frame
xform 0 728 1264
p 2120 92 75 1536 -1 Author:Janet E. Tvedt
p 1616 96 100 1536 1 Date:23 Apr 97
p 1720 192 300 1792 -1 Dnumber:
p 1848 176 150 1536 -1 Title:naacDc.sch
use sysApply 288 1095 100 0 sysApply#183
xform 0 368 1200
use noOpApply 288 647 100 0 noOpApply#182
xform 0 368 752
use stateApply 288 871 100 0 stateApply#181
xform 0 368 976
use drRoiCad 288 1319 100 0 drRoiCad#180
xform 0 368 1424
use obsSetupCad 288 1543 100 0 obsSetupCad#177
xform 0 368 1648
use arSetupCad 288 1767 100 0 arSetupCad#175
xform 0 368 1872
use sysCar 1220 1943 100 0 sysCar#174
xform 0 1300 2048
p 1224 1932 100 0 1 set1:top $(top)
use notes 1732 1923 100 0 notes#172
xform 0 1988 2108
p 1760 2234 100 0 -1 COMMENT1:This is the top level schematic for the
p 1760 2202 100 0 -1 COMMENT2:detector controller.  It contains the
p 1760 2172 100 0 -1 COMMENT3:Apply, CAD and CAR database records.
p 1760 2140 100 0 -1 COMMENT4:The Client ID from the top level apply
p 1760 2108 100 0 -1 COMMENT5:record is the only CLID maintained
p 1760 2076 100 0 -1 COMMENT6:throughout the system.
p 1760 2044 100 0 -1 COMMENT7:
use eapply -324 1684 100 0 apply
xform 0 -288 1328
p -424 964 65 0 1 DESC:NAAC DC top level APPLY record
p -424 944 65 0 1 PV:$(top)
[comments]
