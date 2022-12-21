#include <systemc.h>
#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"

using namespace sc_core;

SC_MODULE(MyInitiator) {
    tlm_utils::simple_initiator_socket<MyInitiator> socket;

    SC_HAS_PROCESS(MyInitiator);
    MyInitiator(sc_module_name name) : sc_module(name) {
        SC_THREAD(send);
    }

    ~MyInitiator() {
        if (payload) {
            delete payload;
        }
    }

    private:
        tlm::tlm_generic_payload *payload;
        void send();
};

void MyInitiator::send()
{
    payload = new tlm::tlm_generic_payload();
    if (payload == nullptr) {
        std::cout << "payload is nullptr." << std::endl;
        return;
    }

    const char *data{"Target has received the msg from Initiator!"};

    payload->set_data_ptr((unsigned char *) data);

    sc_time delay = SC_ZERO_TIME;

    socket->b_transport(*payload, delay);
}

SC_MODULE(MyTarget) {
    tlm_utils::simple_target_socket<MyTarget> tgt_socket;
    
    SC_HAS_PROCESS(MyTarget);
    MyTarget(sc_module_name name) : sc_module(name) {
        tgt_socket.register_b_transport(this, &MyTarget::recieve);
    }    

    private:
        void recieve(tlm::tlm_generic_payload &payload, sc_core::sc_time &delay_time);
};

void MyTarget::recieve(tlm::tlm_generic_payload &payload, sc_core::sc_time &delay_time)
{
    const char *data = reinterpret_cast<const char *>(payload.get_data_ptr());
    
    std::cout << data << std::endl;
}

int sc_main(int argc, char* argv[]){
    MyInitiator init("MyInitiator");
    MyTarget    targ("MyTarget");

    //init.socket(targ.tgt_socket);
    init.socket.bind(targ.tgt_socket);

    sc_start(10, SC_NS);

    return 0;
 }