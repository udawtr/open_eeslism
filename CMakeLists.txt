cmake_minimum_required(VERSION 3.0.0)
project(OpenEESLISM VERSION 0.1.0)

include_directories(includes)

add_executable(eeslism 
    Source/func/CAT.c
    Source/func/CINC.c
    Source/func/COORDNT.c
    Source/func/DAINYUU.c
    Source/func/DATAIN.c
    Source/func/EOP.c
    Source/func/ERRPRINT.c
    Source/func/GDATA.c
    Source/func/GRPOINT.c
    Source/func/HOUSEN.c
    Source/func/INOROUT.c
    Source/func/KAUNT.c
    Source/func/KOUTEN.c
    Source/func/LPOP_placement.c
    Source/func/MAT_INIT.c
    Source/func/MONTE_CARLO.c
    Source/func/NENNKANN.c
    Source/func/OPIhor.c
    Source/func/PRA.c
    Source/func/RAND.c
    Source/func/SHADOW.c
    Source/func/STRCUT.c
    Source/func/URA.c
    Source/func/YOGEN.c
    Source/func/ZAHYOU.c
    Source/func/ZPRINT.c
    Source/bdhpri.c
    Source/bl/blhcflib.c
    Source/bl/blhelm.c
    Source/bl/blhelmlib.c
    Source/bl/blinit.c
    Source/bl/blpanel.c
    Source/bl/blpcm.c
    Source/bl/blpvsystem.c
    Source/bl/blrmaceqcf.c
    Source/bl/blrmdata.c
    Source/bl/blrmprint.c
    Source/bl/blrmqprt.c
    Source/bl/blrmresid.c
    Source/bl/blrmschd.c
    Source/bl/blrmvent.c
    Source/bl/blroom.c
    Source/bl/blroomcf.c
    Source/bl/blroomday.c
    Source/bl/blroomene.c
    Source/bl/blroomvar.c
    Source/bl/blroomvptr.c
    Source/bl/blrzone.c
    Source/bl/blsnbklib.c
    Source/bl/blsolarwall.c
    Source/bl/blsrprint.c
    Source/bl/bltcomfrt.c
    Source/bl/blwall.c
    Source/bl/dbgpri1.c
    Source/bl/dbgpri2.c
    Source/bl/dbgprip1.c
    Source/e79.c
    Source/ee/eebslib.c
    Source/ee/eecmpdat_s.c
    Source/ee/eecmpday_s.c
    Source/ee/eecmpprt_s.c
    Source/ee/eecpprint.c
    Source/ee/eedayslib.c
    Source/ee/eefiles.c
    Source/ee/eegndata.c
    Source/ee/eeinput_s.c
    Source/ee/eenvptr.c
    Source/ee/eepathdat.c
    Source/ee/eepathlib_s.c
    Source/ee/eepflow.c
    Source/ee/eeprint_s.c
    Source/ee/eepthene.c
    Source/ee/eepthprt.c
    Source/ee/eerthlib.c
    Source/ee/eespre.c
    Source/ee/eesyselmalc_s.c
    Source/ee/eesyseqv.c
    Source/ee/eesysupv_s.c
    Source/ee/eesysvar.c
    Source/ee/eettlprt.c
    Source/ee/eevcdat.c
    Source/ee/epsinput.c
    Source/esy/eschdata.c
    Source/esy/eschdlr_s.c
    Source/esy/eschval.c
    Source/esy/escntldat.c
    Source/esy/escntllb_s.c
    Source/esy/escntlsch_s.c
    Source/esy/escntrlfactor.c
    Source/esy/esidcode_s.c
    Source/ee/evcwdfl.c
    "Source/mc/cmp/mcboi.c"
    "Source/mc/cmp/mccnvrg.c"
    "Source/mc/cmp/mcdesiccant.c"
    "Source/mc/mceqpcat.c"
    "Source/mc/cmp/mcevpcooling.c"
    "Source/mc/cmp/mchcc.c"
    "Source/mc/cmp/mchcload.c"
    "Source/mc/cmp/mchex.c"
    "Source/mc/cmp/mcmecsys.c"
    "Source/mc/cmp/mcomvav.c"
    "Source/mc/cmp/mcpipe.c"
    "Source/mc/cmp/mcpump.c"
    "Source/mc/cmp/mcpv.c"
    "Source/mc/cmp/mcqmeas.c"
    "Source/mc/cmp/mcrefa.c"
    "Source/mc/cmp/mccoll.c"
    "Source/mc/cmp/mcstank.c"    
    "Source/mc/cmp/mcstheat.c"
    "Source/mc/cmp/mcthex.c"
    "Source/mc/cmp/mcvalv.c"
    "Source/mc/cmp/mcvav.c"    
    Source/memoryfree.c
    Source/lib/spline.c
    Source/lib/u_ees3lb.c
    Source/lib/u_inv.c
    Source/lib/u_minmax.c
    Source/lib/u_mlib.c
    Source/lib/u_psy.c
    Source/lib/u_sun.c
    Source/lib/valinit.c
    Source/waterandair.c
    Source/lib/wdprint.c
    Source/lib/wdread.c
 "Source/mc/ca/mcboica.c" "Source/mc/ca/mcpipeductca.c" "Source/mc/ca/mcpumpfanca.c" "Source/mc/ca/mcpvca.c" "Source/mc/ca/mcrefaca.c" "Source/mc/ca/mccollca.c" "Source/mc/ca/mcstankca.c" "Source/mc/ca/mcstheatca.c" "Source/mc/ca/mcthexca.c" "Source/mc/ca/mcvavca.c" "Source/mc/ca/mcevpcoolingca.c" "Source/mc/ca/mchccca.c" "Source/mc/ca/mcdesiccantca.c" "Source/mc/ca/mcomvavca.c" "Source/mc/ca/mchexca.c" "Source/mc/mcsyscmp.c" "Source/mc/cmp/mcflin.c" "includes/mc/cmp/mcflin.h")

target_link_libraries(eeslism)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
