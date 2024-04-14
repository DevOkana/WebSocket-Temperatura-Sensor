#include "confor_tmp_hum.h"



String EvaluateConfor( double hum){
    if(hum > MAXHUME){
            return Confor.WEET.toString();        
    }else if(hum < MINHUME){
            return Confor.DRY.toString();        
    }else{
        return Confor.CONFORT.toString();        
    }
}

