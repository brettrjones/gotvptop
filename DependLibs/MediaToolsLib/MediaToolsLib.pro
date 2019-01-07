#-------------------------------------------------
#
# Project created by QtCreator 2012-06-02T19:53:30
#
#-------------------------------------------------

QT       += network
QT       -= gui

TARGET = MediaToolsLib
TEMPLATE = lib
CONFIG += staticlib

DEFINES += "OUTSIDE_SPEEX"
DEFINES += "HAVE_CONFIG_H"
DEFINES += "_LITTLE_ENDIAN__"

MediaToolsLib.depends += CoreLib

win32 {
    CharacterSet=2
    DEFINES -= UNICODE
    DEFINES += "TARGET_OS_WINDOWS"
    DEFINES += "WIN32"
    DEFINES += "_WINDOWS"
    DEFINES += "_CRT_SECURE_NO_WARNINGS"
    debug {
        DEFINES += "DEBUG"
    }
    release {
        DEFINES += "RELEASE"
    }
}

unix:!symbian {
    QMAKE_CXXFLAGS += -Wno-unused-parameter -O2
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    debug {
        DEFINES += "DEBUG"
    }
    release {
        DEFINES += "RELEASE"
    }
    INSTALLS += target
}

INCLUDEPATH += ../
INCLUDEPATH += ../P2PEngineLib/
INCLUDEPATH += ./OpusTools/include
INCLUDEPATH += ./include
INCLUDEPATH += ./opus/celt
INCLUDEPATH += ./opus/silk
INCLUDEPATH += ./opus/silk/float


SOURCES += ./SndDefs.cpp \
    MJPEGWriter.cpp \
    AviDefs.cpp \
    MediaTools.cpp \
    MJPEGReader.cpp \
    MyOpusHeader.cpp \
    OggBuffer.cpp \
    OggStream.cpp \
    OpusAudioDecoder.cpp \
    OpusAudioEncoder.cpp \
    OpusFileDecoder.cpp \
    OpusFileEncoder.cpp \
    SndReader.cpp \
    SndWriter.cpp \
    ogg/bitwise.c \
    ogg/framing.c \
    opus/celt/bands.c \
    opus/celt/celt.c \
    opus/celt/celt_decoder.c \
    opus/celt/celt_encoder.c \
    opus/celt/celt_lpc.c \
    opus/celt/cwrs.c \
    opus/celt/entcode.c \
    opus/celt/entdec.c \
    opus/celt/entenc.c \
    opus/celt/kiss_fft.c \
    opus/celt/laplace.c \
    opus/celt/mathops.c \
    opus/celt/mdct.c \
    opus/celt/modes.c \
    opus/celt/pitch.c \
    opus/celt/quant_bands.c \
    opus/celt/rate.c \
    opus/celt/vq.c \
    opus/silk/A2NLSF.c \
    opus/silk/ana_filt_bank_1.c \
    opus/silk/biquad_alt.c \
    opus/silk/bwexpander.c \
    opus/silk/bwexpander_32.c \
    opus/silk/check_control_input.c \
    opus/silk/CNG.c \
    opus/silk/code_signs.c \
    opus/silk/control_audio_bandwidth.c \
    opus/silk/control_codec.c \
    opus/silk/control_SNR.c \
    opus/silk/debug.c \
    opus/silk/dec_API.c \
    opus/silk/decode_core.c \
    opus/silk/decode_frame.c \
    opus/silk/decode_indices.c \
    opus/silk/decode_parameters.c \
    opus/silk/decode_pitch.c \
    opus/silk/decode_pulses.c \
    opus/silk/decoder_set_fs.c \
    opus/silk/enc_API.c \
    opus/silk/encode_indices.c \
    opus/silk/encode_pulses.c \
    opus/silk/gain_quant.c \
    opus/silk/HP_variable_cutoff.c \
    opus/silk/init_decoder.c \
    opus/silk/init_encoder.c \
    opus/silk/inner_prod_aligned.c \
    opus/silk/interpolate.c \
    opus/silk/lin2log.c \
    opus/silk/log2lin.c \
    opus/silk/LPC_analysis_filter.c \
    opus/silk/LPC_inv_pred_gain.c \
    opus/silk/LP_variable_cutoff.c \
    opus/silk/NLSF2A.c \
    opus/silk/NLSF_decode.c \
    opus/silk/NLSF_del_dec_quant.c \
    opus/silk/NLSF_encode.c \
    opus/silk/NLSF_stabilize.c \
    opus/silk/NLSF_unpack.c \
    opus/silk/NLSF_VQ.c \
    opus/silk/NLSF_VQ_weights_laroia.c \
    opus/silk/NSQ.c \
    opus/silk/NSQ_del_dec.c \
    opus/silk/pitch_est_tables.c \
    opus/silk/PLC.c \
    opus/silk/process_NLSFs.c \
    opus/silk/quant_LTP_gains.c \
    opus/silk/resampler.c \
    opus/silk/resampler_down2.c \
    opus/silk/resampler_down2_3.c \
    opus/silk/resampler_private_AR2.c \
    opus/silk/resampler_private_down_FIR.c \
    opus/silk/resampler_private_IIR_FIR.c \
    opus/silk/resampler_private_up2_HQ.c \
    opus/silk/resampler_rom.c \
    opus/silk/shell_coder.c \
    opus/silk/sigm_Q15.c \
    opus/silk/sort.c \
    opus/silk/stereo_decode_pred.c \
    opus/silk/stereo_encode_pred.c \
    opus/silk/stereo_find_predictor.c \
    opus/silk/stereo_LR_to_MS.c \
    opus/silk/stereo_MS_to_LR.c \
    opus/silk/stereo_quant_pred.c \
    opus/silk/sum_sqr_shift.c \
    opus/silk/table_LSF_cos.c \
    opus/silk/tables_gain.c \
    opus/silk/tables_LTP.c \
    opus/silk/tables_NLSF_CB_NB_MB.c \
    opus/silk/tables_NLSF_CB_WB.c \
    opus/silk/tables_other.c \
    opus/silk/tables_pitch_lag.c \
    opus/silk/tables_pulses_per_block.c \
    opus/silk/VAD.c \
    opus/silk/VQ_WMat_EC.c \
    opus/silk/float/apply_sine_window_FLP.c \
    opus/silk/float/autocorrelation_FLP.c \
    opus/silk/float/burg_modified_FLP.c \
    opus/silk/float/bwexpander_FLP.c \
    opus/silk/float/corrMatrix_FLP.c \
    opus/silk/float/encode_frame_FLP.c \
    opus/silk/float/energy_FLP.c \
    opus/silk/float/find_LPC_FLP.c \
    opus/silk/float/find_LTP_FLP.c \
    opus/silk/float/find_pitch_lags_FLP.c \
    opus/silk/float/find_pred_coefs_FLP.c \
    opus/silk/float/inner_product_FLP.c \
    opus/silk/float/k2a_FLP.c \
    opus/silk/float/levinsondurbin_FLP.c \
    opus/silk/float/LPC_analysis_filter_FLP.c \
    opus/silk/float/LPC_inv_pred_gain_FLP.c \
    opus/silk/float/LTP_analysis_filter_FLP.c \
    opus/silk/float/LTP_scale_ctrl_FLP.c \
    opus/silk/float/noise_shape_analysis_FLP.c \
    opus/silk/float/pitch_analysis_core_FLP.c \
    opus/silk/float/prefilter_FLP.c \
    opus/silk/float/process_gains_FLP.c \
    opus/silk/float/regularize_correlations_FLP.c \
    opus/silk/float/residual_energy_FLP.c \
    opus/silk/float/scale_copy_vector_FLP.c \
    opus/silk/float/scale_vector_FLP.c \
    opus/silk/float/schur_FLP.c \
    opus/silk/float/solve_LS_FLP.c \
    opus/silk/float/sort_FLP.c \
    opus/silk/float/warped_autocorrelation_FLP.c \
    opus/silk/float/wrappers_FLP.c \
    opus/src/analysis.c \
    opus/src/mlp.c \
    opus/src/mlp_data.c \
    opus/src/opus.c \
    opus/src/opus_decoder.c \
    opus/src/opus_encoder.c \
    opus/src/opus_multistream.c \
    opus/src/opus_multistream_decoder.c \
    opus/src/opus_multistream_encoder.c \
    opus/src/repacketizer.c \
    OpusTools/audio-in.c \
    OpusTools/diag_range.c \
    OpusTools/flac.c \
    OpusTools/lpc.c \
    OpusTools/opusdec.c \
    OpusTools/opusenc.c \
    OpusTools/opus_header.c \
    OpusTools/picture.c \
    OpusTools/resample.c \
    OpusTools/wave_out.c \
    OpusTools/wav_io.c


HEADERS += ./SndDefs.h \
    SndWriter.h \
    AviDefs.h \
    MediaTools.h \
    MJPEGReader.h \
    MJPEGWriter.h \
    MyOpusHeader.h \
    OggBuffer.h \
    OggStream.h \
    OpusAudioDecoder.h \
    OpusAudioEncoder.h \
    OpusCallbackInterface.h \
    OpusFileDecoder.h \
    OpusFileEncoder.h \
    SndReader.h \
    include/opus.h \
    include/opus_custom.h \
    include/opus_defines.h \
    include/opus_multistream.h \
    include/opus_types.h \
    include/ogg/ogg.h \
    include/ogg/os_types.h \
    OpusTools/include/getopt.h \
    OpusTools/arch.h \
    OpusTools/cpusupport.h \
    OpusTools/diag_range.h \
    OpusTools/flac.h \
    OpusTools/lpc.h \
    OpusTools/opusenc.h \
    OpusTools/opus_header.h \
    OpusTools/os_support.h \
    OpusTools/picture.h \
    OpusTools/resample_sse.h \
    OpusTools/speex_resampler.h \
    OpusTools/stack_alloc.h \
    OpusTools/wave_out.h \
    OpusTools/wav_io.h \
    opus/celt/arch.h \
    opus/celt/bands.h \
    opus/celt/celt.h \
    opus/celt/celt_lpc.h \
    opus/celt/cpu_support.h \
    opus/celt/cwrs.h \
    opus/celt/ecintrin.h \
    opus/celt/entcode.h \
    opus/celt/entdec.h \
    opus/celt/entenc.h \
    opus/celt/fixed_debug.h \
    opus/celt/fixed_generic.h \
    opus/celt/float_cast.h \
    opus/celt/kiss_fft.h \
    opus/celt/_kiss_fft_guts.h \
    opus/celt/laplace.h \
    opus/celt/mathops.h \
    opus/celt/mdct.h \
    opus/celt/mfrngcod.h \
    opus/celt/modes.h \
    opus/celt/os_support.h \
    opus/celt/pitch.h \
    opus/celt/quant_bands.h \
    opus/celt/rate.h \
    opus/celt/stack_alloc.h \
    opus/celt/static_modes_fixed.h \
    opus/celt/static_modes_float.h \
    opus/celt/vq.h \
    opus/silk/API.h \
    opus/silk/control.h \
    opus/silk/debug.h \
    opus/silk/define.h \
    opus/silk/errors.h \
    opus/silk/Inlines.h \
    opus/silk/MacroCount.h \
    opus/silk/MacroDebug.h \
    opus/silk/macros.h \
    opus/silk/main.h \
    opus/silk/pitch_est_defines.h \
    opus/silk/PLC.h \
    opus/silk/resampler_private.h \
    opus/silk/resampler_rom.h \
    opus/silk/resampler_structs.h \
    opus/silk/SigProc_FIX.h \
    opus/silk/structs.h \
    opus/silk/tables.h \
    opus/silk/tuning_parameters.h \
    opus/silk/typedef.h \
    opus/silk/float/main_FLP.h \
    opus/silk/float/SigProc_FLP.h \
    opus/silk/float/structs_FLP.h \
    opus/src/analysis.h \
    opus/src/mlp.h \
    opus/src/opus_private.h \
    opus/src/tansig_table.h \
    include/config.h \
    include/version.h

 


