#ifndef __TB_H__
#define __TB_H__

#include <systemc.h>

SC_MODULE(TB) {
    sc_in<bool>        clk;
    sc_out<bool>       rst;
    sc_out<sc_int<16>> inp;
    sc_out<bool>       inp_vld;
    sc_in<bool>        inp_rdy;

    sc_in<sc_int<16>>  outp;
    sc_in<bool>        outp_vld;
    sc_out<bool>       outp_rdy;

    sc_time            start_time[64];
    sc_time            end_time[64];
    sc_time            clock_period;

    FILE* outfp;

    void source();
    void sink();

    SC_CTOR(TB) {
        SC_THREAD(source);
        sensitive << clk.pos();

        SC_THREAD(sink);
        sensitive << clk.pos();
    }
};


#endif