// -*- C++ -*-
//
// $Id$

// ****  Code generated by the The ACE ORB (TAO) IDL Compiler ****
// TAO and the TAO IDL Compiler have been developed by:
//       Center for Distributed Object Computing
//       Washington University
//       St. Louis, MO
//       USA
//       http://www.cs.wustl.edu/~schmidt/doc-center.html
// and
//       Distributed Object Computing Laboratory
//       University of California at Irvine
//       Irvine, CA
//       USA
//       http://doc.ece.uci.edu/
// and
//       Institute for Software Integrated Systems
//       Vanderbilt University
//       Nashville, TN
//       USA
//       http://www.isis.vanderbilt.edu/
//
// Information about TAO is available at:
//     http://www.cs.wustl.edu/~schmidt/TAO.html

// TAO_IDL - Generated from
// ../../../ACE_wrappers/TAO/TAO_IDL/be/be_codegen.cpp:1196

#include "CorbaLib.hpp"
#include "CorbaTypeTransporter.hpp"
#include "OperationRepositoryI.h"
#include "AnyDataSource.hpp"
#include "../../rtt-detail-fwd.hpp"
#include "../../internal/MethodC.hpp"
#include "../../internal/SendHandleC.hpp"

using namespace RTT;
using namespace RTT::detail;
using namespace std;

RTT_corba_CSendHandle_i::RTT_corba_CSendHandle_i (SendHandleC const& sh, OperationRepositoryPart* ofp)
: mhandle(sh), morig(sh), mofp(ofp)
{
    // this will always be correct:
    for (unsigned int i = 1; i <= mofp->collectArity(); ++i) {
        const TypeInfo* ti = mofp->getCollectType(i); // retrieve 1..collectArity()
        assert(ti);
        cargs.push_back( ti->buildValue() );
        mhandle.arg( cargs.back() );
    }
    assert( mhandle.ready() );
}

RTT_corba_CSendHandle_i::~RTT_corba_CSendHandle_i (void)
{
}

/**
 * Helper function to convert a sequence of anys to a vector of data sources.
 * @param sources
 * @param anys
 * @return
 */
bool anysequence_to_sourcevector( CAnyArguments const& anys, vector<DataSourceBase::shared_ptr>& sources) {
    return false;
}

/**
 * Helper function to convert a vector of data sources to a sequence of anys.
 * @param sources
 * @param anys
 * @return
 */
bool sourcevector_to_anysequence( vector<DataSourceBase::shared_ptr> const& sources, CAnyArguments & anys ) {
    bool valid = true;
    anys.length( sources.size() );
    for(unsigned int i = 0; i != sources.size(); ++i) {
        const TypeInfo* ti = sources[i]->getTypeInfo();
        CorbaTypeTransporter* ctt = dynamic_cast<CorbaTypeTransporter*> ( ti->getProtocol(ORO_CORBA_PROTOCOL_ID) );
        ctt->updateAny(sources[i], anys[i]);
    }
    return valid;
}

::RTT::corba::CSendStatus RTT_corba_CSendHandle_i::collect (
    ::RTT::corba::CAnyArguments_out args)
{
    SendStatus ss = mhandle.collect();
    args = new CAnyArguments();
    if (ss == SendSuccess) {
        sourcevector_to_anysequence( cargs, *args.ptr() );
    }
    return CSendStatus(ss);
}

::RTT::corba::CSendStatus RTT_corba_CSendHandle_i::collectIfDone (
    ::RTT::corba::CAnyArguments_out args)
{
    SendStatus ss = mhandle.collectIfDone();
    args = new CAnyArguments();
    if (ss == SendSuccess) {
        sourcevector_to_anysequence( cargs, *args.ptr() );
    }
    return CSendStatus(ss);
}

::RTT::corba::CSendStatus RTT_corba_CSendHandle_i::checkStatus (
    void)
{
    return CSendStatus( mhandle.collectIfDone() );
}

::CORBA::Any * RTT_corba_CSendHandle_i::ret (
    void)
{
    SendStatus ss = mhandle.collectIfDone();
    // We just copy over the first collectable argument. In
    // case of a void operation, we will thus return the first
    // reference argument.
    if (ss == SendSuccess) {
        if ( cargs.size() > 0) {
            CorbaTypeTransporter* ctt = dynamic_cast<CorbaTypeTransporter*> (cargs[0]->getTypeInfo()->getProtocol(ORO_CORBA_PROTOCOL_ID));
            return ctt->createAny( cargs[0] );
        }
    }
    return new CORBA::Any();
}

void RTT_corba_CSendHandle_i::checkArguments (
    const ::RTT::corba::CAnyArguments & args)
{
    try {
        SendHandleC shc(morig);
        for (unsigned int i = 0; i != mofp->collectArity(); ++i) {
            const TypeInfo* ti = mofp->getCollectType(i + 1);
            assert(ti);
            CorbaTypeTransporter* ctt = dynamic_cast<CorbaTypeTransporter*> (ti->getProtocol(ORO_CORBA_PROTOCOL_ID));
            shc.arg(ctt->createDataSource(&args[i]));
        }
        shc.check();
    } catch (name_not_found_exception& nnf) {
        throw ::RTT::corba::CNoSuchNameException(nnf.name.c_str());
    } catch (wrong_number_of_args_exception& wna) {
        throw ::RTT::corba::CWrongNumbArgException(wna.wanted, wna.received);
    } catch (wrong_types_of_args_exception& wta) {
        throw ::RTT::corba::CWrongTypeArgException(wta.whicharg, wta.expected_.c_str(), wta.received_.c_str());
    }
}


// Implementation skeleton constructor
RTT_corba_COperationRepository_i::RTT_corba_COperationRepository_i (OperationRepository* gmf, PortableServer::POA_ptr the_poa)
    :mfact(gmf), mpoa( PortableServer::POA::_duplicate(the_poa))
{
}

PortableServer::POA_ptr RTT_corba_COperationRepository_i::_default_POA()
{
    return PortableServer::POA::_duplicate(mpoa);
}


// Implementation skeleton destructor
RTT_corba_COperationRepository_i::~RTT_corba_COperationRepository_i (void)
{
}

::RTT::corba::COperationRepository::COperationList * RTT_corba_COperationRepository_i::getOperations (
    void)
{
    RTT::corba::COperationRepository::COperationList_var rlist = new RTT::corba::COperationRepository::COperationList();

    vector<string> flist = mfact->getNames();
    rlist->length( flist.size() );
    for (size_t i=0; i != flist.size(); ++i)
        rlist[i] = CORBA::string_dup( flist[i].c_str() );
    return rlist._retn();
}

::RTT::corba::CDescriptions * RTT_corba_COperationRepository_i::getArguments (
    const char * operation)
{
    CDescriptions_var ret = new CDescriptions();
    if ( mfact->hasMember( string( operation ) ) == false )
        throw ::RTT::corba::CNoSuchNameException( operation );
    // operation found, convert args:
    OperationRepository::Descriptions args = mfact->getArgumentList( string(operation) );
    ret->length( args.size() );
    for (size_t i =0; i != args.size(); ++i) {
        ret[i].name = CORBA::string_dup( args[i].name.c_str() );
        ret[i].description = CORBA::string_dup( args[i].description.c_str() );
        ret[i].type = CORBA::string_dup( args[i].type.c_str() );
    }
    return ret._retn();
}

char * RTT_corba_COperationRepository_i::getResultType (
    const char * operation)
{
    if ( mfact->hasMember( string( operation ) ) == false )
        throw ::RTT::corba::CNoSuchNameException( operation );
    return CORBA::string_dup( mfact->getResultType( string(operation) ).c_str() );
}

char* RTT_corba_COperationRepository_i::getArgumentType(
        const char* operation,
        CORBA::UShort nbr)
{
    if ( mfact->hasMember( string( operation ) ) == false )
        throw ::RTT::corba::CNoSuchNameException( operation );
    if ( nbr > mfact->getPart(operation)->arity() )
        throw ::RTT::corba::CWrongArgumentException( nbr, mfact->getPart(operation)->arity() );
    return CORBA::string_dup( mfact->getPart( operation )->getArgumentType(nbr)->getTypeName().c_str() );
}

char* RTT_corba_COperationRepository_i::getCollectType(
        const char* operation,
        CORBA::UShort nbr)
{
    if ( mfact->hasMember( string( operation ) ) == false )
        throw ::RTT::corba::CNoSuchNameException( operation );
    if ( nbr > mfact->getPart(operation)->collectArity() )
        throw ::RTT::corba::CWrongArgumentException( nbr, mfact->getPart(operation)->collectArity() );
    return CORBA::string_dup( mfact->getPart( operation )->getCollectType(nbr)->getTypeName().c_str() );

}

::CORBA::UShort RTT_corba_COperationRepository_i::getArity (
    const char * operation)
{
    if ( mfact->hasMember( string( operation ) ) == false )
        throw ::RTT::corba::CNoSuchNameException( operation );
    return mfact->getPart(operation)->arity();
}

::CORBA::UShort RTT_corba_COperationRepository_i::getCollectArity (
    const char * operation)
{
    if ( mfact->hasMember( string( operation ) ) == false )
        throw ::RTT::corba::CNoSuchNameException( operation );
    return mfact->getPart(operation)->collectArity();
}

char * RTT_corba_COperationRepository_i::getDescription (
    const char * operation)
{
    if ( mfact->hasMember( string( operation ) ) == false )
        throw ::RTT::corba::CNoSuchNameException( operation );
    return CORBA::string_dup( mfact->getDescription( string(operation) ).c_str() );
}

void RTT_corba_COperationRepository_i::checkOperation (
    const char * operation,
    const ::RTT::corba::CAnyArguments & args)
{
    try {
        OperationRepositoryPart* mofp = mfact->getPart(operation);
        MethodC mc(mofp, operation, 0);
        for (unsigned int i = 0; i < mofp->arity() && i < args.length(); ++i) {
            const TypeInfo* ti = mofp->getArgumentType(i+1);
            assert(ti);
            CorbaTypeTransporter* ctt = dynamic_cast<CorbaTypeTransporter*> (ti->getProtocol(ORO_CORBA_PROTOCOL_ID));
            DataSourceBase::shared_ptr ds = ctt->createDataSource(&args[i]);
            if (ds)
                mc.arg(ds);
        }
        mc.check();
    } catch (name_not_found_exception& nnf) {
        throw ::RTT::corba::CNoSuchNameException(nnf.name.c_str());
    } catch (wrong_number_of_args_exception& wna) {
        throw ::RTT::corba::CWrongNumbArgException(wna.wanted, wna.received);
    } catch (wrong_types_of_args_exception& wta) {
        throw ::RTT::corba::CWrongTypeArgException(wta.whicharg, wta.expected_.c_str(), wta.received_.c_str());
    }
}

::CORBA::Any * RTT_corba_COperationRepository_i::callOperation (
    const char * operation,
    ::RTT::corba::CAnyArguments & args)
{
    if ( mfact->hasMember( string( operation ) ) == false )
        throw ::RTT::corba::CNoSuchNameException( operation );
    // convert Corba args to C++ args.
    try {
        MethodC orig(mfact->getPart(operation), operation, 0);
        vector<DataSourceBase::shared_ptr> results;
        for (size_t i =0; i != args.length(); ++i) {
            const TypeInfo* ti = mfact->getPart(operation)->getArgumentType( i + 1);
            CorbaTypeTransporter* ctt = dynamic_cast<CorbaTypeTransporter*> ( ti->getProtocol(ORO_CORBA_PROTOCOL_ID) );
            // we need to store the results for returning them to caller (args is inout!) after the call()
            results.push_back( ctt->createDataSource( &args[i] ) );
            orig.arg( results[i] );
        }
        if ( orig.ready() ) {
            DataSourceBase::shared_ptr ds = orig.getCallDataSource();
            // Call nomatter what:
            ds->evaluate(); // equivalent to orig.call()
            // Return results into args:
            for (size_t i =0; i != args.length(); ++i) {
                const TypeInfo* ti = mfact->getPart(operation)->getArgumentType( i + 1);
                CorbaTypeTransporter* ctt = dynamic_cast<CorbaTypeTransporter*> ( ti->getProtocol(ORO_CORBA_PROTOCOL_ID) );
		ctt->updateAny(results[i], args[i]);
            }

            // Try to return result:
            const TypeInfo* ti = ds->getTypeInfo();
            CorbaTypeTransporter* ctt = dynamic_cast<CorbaTypeTransporter*> ( ti->getProtocol(ORO_CORBA_PROTOCOL_ID) );
            if ( !ctt ) {
                log(Warning) << "Could not return results of call to " << operation << ": unknown return type by CORBA transport."<<endlog();
                return new CORBA::Any();
            }
            return ctt->createAny( ds );
        } else {
            orig.check(); // will throw
        }
    } catch ( name_not_found_exception& nnf ) {
        throw ::RTT::corba::CNoSuchNameException( operation );
    } catch ( wrong_number_of_args_exception& wna ) {
        throw ::RTT::corba::CWrongNumbArgException( wna.wanted, wna.received );
    } catch (wrong_types_of_args_exception& wta ) {
        throw ::RTT::corba::CWrongTypeArgException( wta.whicharg, wta.expected_.c_str(), wta.received_.c_str() );
    }
    return new ::CORBA::Any();
}

::RTT::corba::CSendHandle_ptr RTT_corba_COperationRepository_i::sendOperation (
    const char * operation,
    const ::RTT::corba::CAnyArguments & args)
{
    // This implementation is 90% identical to callOperation above, only deviating in the orig.ready() part.
    if ( mfact->hasMember( string( operation ) ) == false )
        throw ::RTT::corba::CNoSuchNameException( operation );
    // convert Corba args to C++ args.
    try {
        MethodC orig(mfact->getPart(operation), operation, 0);
        for (size_t i =0; i != args.length(); ++i) {
            const TypeInfo* ti = mfact->getPart(operation)->getArgumentType( i + 1);
            CorbaTypeTransporter* ctt = dynamic_cast<CorbaTypeTransporter*> ( ti->getProtocol(ORO_CORBA_PROTOCOL_ID) );
            orig.arg( ctt->createDataSource( &args[i] ));
        }
        if ( orig.ready() ) {
            SendHandleC resulthandle = orig.send();
            RTT_corba_CSendHandle_i* ret_i = new RTT_corba_CSendHandle_i( resulthandle, mfact->getPart(operation) );
            CSendHandle_var ret = ret_i->_this();
            return ret._retn();
        } else {
            orig.check(); // will throw
        }
    } catch ( name_not_found_exception& nnf ) {
        throw ::RTT::corba::CNoSuchNameException( operation );
    } catch ( wrong_number_of_args_exception& wna ) {
        throw ::RTT::corba::CWrongNumbArgException( wna.wanted, wna.received );
    } catch (wrong_types_of_args_exception& wta ) {
        throw ::RTT::corba::CWrongTypeArgException( wta.whicharg, wta.expected_.c_str(), wta.received_.c_str() );
    }
    return CSendHandle::_nil();
}
