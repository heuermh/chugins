//-----------------------------------------------------------------------------
// Entaro ChucK Developer!
// This is a Chugin boilerplate, generated by chuginate!
//-----------------------------------------------------------------------------

// this should align with the correct versions of these ChucK files
#include "chugin.h"

// general includes
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#include "perlin-noise.h"

#ifdef _WIN32
#include <time.h>
static long random() { return rand(); }
static void srandom( unsigned s ) { srand( s ); }
#endif // _WIN32


// declaration of chugin constructor
CK_DLL_CTOR(perlin_ctor);
// declaration of chugin desctructor
CK_DLL_DTOR(perlin_dtor);

// example of getter/setter
CK_DLL_MFUN(perlin_setFreq);
CK_DLL_MFUN(perlin_getFreq);

// for Chugins extending UGen, this is mono synthesis function for 1 sample
CK_DLL_TICK(perlin_tick);

CK_DLL_MFUN(perlin_noise1);
CK_DLL_MFUN(perlin_noise2);
CK_DLL_MFUN(perlin_noise3);

// this is a special offset reserved for Chugin internal data
t_CKINT perlin_data_offset = 0;


class Perlin
{
public:
    // constructor
    Perlin( t_CKFLOAT fs )
    {
        m_fs = fs;
        m_phase = 0;
        m_freq = 220;
        
        srandom(time(NULL));
    }

    // for Chugins extending UGen
    SAMPLE tick( SAMPLE in )
    {
        // default: this passes whatever input is patched into Chugin
        SAMPLE out = m_perlin.noise1(m_phase);
        m_phase += m_freq/m_fs;
        return out;
    }

    // set parameter example
    float setFreq( t_CKFLOAT f )
    {
        m_freq = f;
        return f;
    }

    // get parameter example
    float getFreq() { return m_freq; }
    
    float noise1(double x) { return m_perlin.noise1(x); }
    
    float noise2(double x[]) { return m_perlin.noise2(x); }
    
    float noise3(double x[]) { return m_perlin.noise3(x); }
    
private:
    // instance data
    PerlinNoise m_perlin;
    float m_fs;
    float m_freq;
    double m_phase;
};


// query function: chuck calls this when loading the Chugin
// NOTE: developer will need to modify this function to
// add additional functions to this Chugin
CK_DLL_QUERY( Perlin )
{
    // hmm, don't change this...
    QUERY->setname(QUERY, "Perlin");
    
    // begin the class definition
    // can change the second argument to extend a different ChucK class
    QUERY->begin_class(QUERY, "Perlin", "UGen");

    // register the constructor (probably no need to change)
    QUERY->add_ctor(QUERY, perlin_ctor);
    // register the destructor (probably no need to change)
    QUERY->add_dtor(QUERY, perlin_dtor);
    
    // for UGen's only: add tick function
    QUERY->add_ugen_func(QUERY, perlin_tick, NULL, 1, 1);
    
    QUERY->add_mfun(QUERY, perlin_setFreq, "float", "freq");
    QUERY->add_arg(QUERY, "float", "f");
    
    QUERY->add_mfun(QUERY, perlin_getFreq, "float", "freq");
    
    QUERY->add_mfun(QUERY, perlin_noise1, "float", "noise1");
    QUERY->add_arg(QUERY, "float", "x1");
    
    QUERY->add_mfun(QUERY, perlin_noise2, "float", "noise2");
    QUERY->add_arg(QUERY, "float", "x1");
    QUERY->add_arg(QUERY, "float", "x2");
    
    QUERY->add_mfun(QUERY, perlin_noise3, "float", "noise3");
    QUERY->add_arg(QUERY, "float", "x1");
    QUERY->add_arg(QUERY, "float", "x2");
    QUERY->add_arg(QUERY, "float", "x3");
        
    perlin_data_offset = QUERY->add_mvar(QUERY, "int", "@p_data", false);

    // end the class definition
    // IMPORTANT: this MUST be called!
    QUERY->end_class(QUERY);

    // wasn't that a breeze?
    return TRUE;
}


// implementation for the constructor
CK_DLL_CTOR(perlin_ctor)
{
    // get the offset where we'll store our internal c++ class pointer
    OBJ_MEMBER_INT(SELF, perlin_data_offset) = 0;
    
    // instantiate our internal c++ class representation
    Perlin * p_obj = new Perlin(API->vm->srate(VM));
    
    // store the pointer in the ChucK object member
    OBJ_MEMBER_INT(SELF, perlin_data_offset) = (t_CKINT) p_obj;
}


// implementation for the destructor
CK_DLL_DTOR(perlin_dtor)
{
    // get our c++ class pointer
    Perlin * p_obj = (Perlin *) OBJ_MEMBER_INT(SELF, perlin_data_offset);
    // check it
    if( p_obj )
    {
        // clean up
        delete p_obj;
        OBJ_MEMBER_INT(SELF, perlin_data_offset) = 0;
        p_obj = NULL;
    }
}


// implementation for tick function
CK_DLL_TICK(perlin_tick)
{
    // get our c++ class pointer
    Perlin * p_obj = (Perlin *) OBJ_MEMBER_INT(SELF, perlin_data_offset);
 
    // invoke our tick function; store in the magical out variable
    if(p_obj) *out = p_obj->tick(in);

    // yes
    return TRUE;
}


// example implementation for setter
CK_DLL_MFUN(perlin_setFreq)
{
    // get our c++ class pointer
    Perlin * p_obj = (Perlin *) OBJ_MEMBER_INT(SELF, perlin_data_offset);
    // set the return value
    RETURN->v_float = p_obj->setFreq(GET_NEXT_FLOAT(ARGS));
}


// example implementation for getter
CK_DLL_MFUN(perlin_getFreq)
{
    // get our c++ class pointer
    Perlin * p_obj = (Perlin *) OBJ_MEMBER_INT(SELF, perlin_data_offset);
    // set the return value
    RETURN->v_float = p_obj->getFreq();
}


CK_DLL_MFUN(perlin_noise1)
{
    Perlin * p_obj = (Perlin *) OBJ_MEMBER_INT(SELF, perlin_data_offset);
    t_CKFLOAT x = GET_NEXT_FLOAT(ARGS);
    RETURN->v_float = p_obj->noise1(x);
}

CK_DLL_MFUN(perlin_noise2)
{
    Perlin * p_obj = (Perlin *) OBJ_MEMBER_INT(SELF, perlin_data_offset);
    t_CKFLOAT x[2];
    x[0] = GET_NEXT_FLOAT(ARGS);
    x[1] = GET_NEXT_FLOAT(ARGS);
    RETURN->v_float = p_obj->noise2(x);
}

CK_DLL_MFUN(perlin_noise3)
{
    Perlin * p_obj = (Perlin *) OBJ_MEMBER_INT(SELF, perlin_data_offset);
    t_CKFLOAT x[3];
    x[0] = GET_NEXT_FLOAT(ARGS);
    x[1] = GET_NEXT_FLOAT(ARGS);
    x[2] = GET_NEXT_FLOAT(ARGS);
    RETURN->v_float = p_obj->noise3(x);
}

