#include "fir.h"
#include "tb.h"

SC_MODULE(SYSTEM) {
    TB*  tb0;
    FIR* fir0;

    sc_signal< bool >       rst_sig;
    sc_signal< sc_int<16> > inp_sig;
    sc_signal< bool >       inp_sig_vld;
    sc_signal< bool >       inp_sig_rdy;
    
    sc_signal< sc_int<16> > outp_sig;
    sc_signal< bool >       outp_sig_vld;
    sc_signal< bool >       outp_sig_rdy;

    sc_clock clk_sig;

    SC_CTOR(SYSTEM) : clk_sig("clk_sig", 10, SC_NS) {
        tb0 = new TB("tb0");
        tb0->clk(clk_sig);
        tb0->rst(rst_sig);
        tb0->inp(inp_sig);
        tb0->inp_vld(inp_sig_vld);
        tb0->inp_rdy(inp_sig_rdy);
        tb0->outp(outp_sig);
        tb0->outp_vld(outp_sig_vld);
        tb0->outp_rdy(outp_sig_rdy);

        fir0 = new FIR("fir0");
        fir0->clk(clk_sig);
        fir0->rst(rst_sig);
        fir0->inp(inp_sig);
        fir0->inp_vld(inp_sig_vld);
        fir0->inp_rdy(inp_sig_rdy);
        fir0->outp(outp_sig);
        fir0->outp_vld(outp_sig_vld);
        fir0->outp_rdy(outp_sig_rdy);
    }

    ~SYSTEM() {
        delete tb0;
        delete fir0;
    }
};

SYSTEM* top = nullptr;

int sc_main(int argc, char* argv[])
{
    top = new SYSTEM("top");
    sc_start();

    return 0;
}