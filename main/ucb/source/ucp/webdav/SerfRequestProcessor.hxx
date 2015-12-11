/**************************************************************
 * 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 * 
 *************************************************************/


#ifndef INCLUDED_SERFREQUESTPROCESSOR_HXX
#define INCLUDED_SERFREQUESTPROCESSOR_HXX

#include <apr_errno.h>
#include <apr_pools.h>

#include <serf.h>

#include "DAVTypes.hxx"
#include "DAVResource.hxx"
#include "DAVException.hxx"

#include "SerfTypes.hxx"
#include "SerfInputStream.hxx"
#include <com/sun/star/io/XOutputStream.hpp>

namespace http_dav_ucp
{

class SerfSession;
class SerfRequestProcessorImpl;

class SerfRequestProcessor
{
public:
    SerfRequestProcessor( SerfSession& rSerfSession,
                          const rtl::OUString & inPath,
                          const bool bUseChunkedEncoding );
    ~SerfRequestProcessor();

    // PROPFIND - allprop & named
    bool processPropFind( const Depth inDepth,
                          const std::vector< ::rtl::OUString > & inPropNames,
                          std::vector< DAVResource > & ioResources,
                          apr_status_t& outSerfStatus );

    // PROPFIND - property names
    bool processPropFind( const Depth inDepth,
                          std::vector< DAVResourceInfo > & ioResInfo,
                          apr_status_t& outSerfStatus );

    // PROPPATCH
    bool processPropPatch( const std::vector< ProppatchValue > & inProperties,
                           const com::sun::star::ucb::Lock  inLock,
                           apr_status_t& outSerfStatus );

    // GET
    bool processGet( const com::sun::star::uno::Reference< SerfInputStream >& xioInStrm, 
                     apr_status_t& outSerfStatus );

    // GET inclusive header fields
    bool processGet( const com::sun::star::uno::Reference< SerfInputStream >& xioInStrm, 
                     const std::vector< ::rtl::OUString > & inHeaderNames,
                     DAVResource & ioResource,
                     apr_status_t& outSerfStatus );

    // GET
    bool processGet( const com::sun::star::uno::Reference< com::sun::star::io::XOutputStream >& xioOutStrm,
                     apr_status_t& outSerfStatus );

    // GET inclusive header fields
    bool processGet( const com::sun::star::uno::Reference< com::sun::star::io::XOutputStream >& xioOutStrm,
                     const std::vector< ::rtl::OUString > & inHeaderNames,
                     DAVResource & ioResource,
                     apr_status_t& outSerfStatus );

    // HEAD
    bool processHead( const std::vector< ::rtl::OUString > & inHeaderNames,
                      DAVResource & ioResource,
                      apr_status_t& outSerfStatus );

    // PUT
    bool processPut( const char* inData,
                     apr_size_t inDataLen,
                     const com::sun::star::ucb::Lock  inLock,
                     apr_status_t& outSerfStatus );

    // POST
    bool processPost( const char* inData,
                      apr_size_t inDataLen,
                      const rtl::OUString & inContentType,
                      const rtl::OUString & inReferer,
                      const com::sun::star::ucb::Lock  inLock,
                      const com::sun::star::uno::Reference< SerfInputStream >& xioInStrm,
                      apr_status_t& outSerfStatus );

    // POST
    bool processPost( const char* inData,
                      apr_size_t inDataLen,
                      const rtl::OUString & inContentType,
                      const rtl::OUString & inReferer,
                      const com::sun::star::ucb::Lock  inLock,
                      const com::sun::star::uno::Reference< com::sun::star::io::XOutputStream >& xioOutStrm,
                      apr_status_t& outSerfStatus );

    // DELETE
    bool processDelete( const com::sun::star::ucb::Lock inLock,
                        apr_status_t& outSerfStatus );

    // MKCOL
    bool processMkCol( const com::sun::star::ucb::Lock inLock,
                       apr_status_t& outSerfStatus );

    // COPY
    bool processCopy( const rtl::OUString & inDestinationPath,
                      const bool inOverwrite,
                      const com::sun::star::ucb::Lock inLock,
                      apr_status_t& outSerfStatus );

    // MOVE
    bool processMove( const rtl::OUString & inDestinationPath,
                      const bool inOverwrite,
                      const com::sun::star::ucb::Lock inLock,
                      apr_status_t& outSerfStatus );

    // LOCK
    bool processLock( const rtl::OUString & inDestinationPath,
                      const com::sun::star::ucb::Lock& inLock,
                      DAVPropertyValue & outLock,
                      apr_status_t& outSerfStatus );

    // LOCK refresh
    bool processLockRefresh( const rtl::OUString & inDestinationPath,
                      const com::sun::star::ucb::Lock& inLock,
                      DAVPropertyValue & outLock,
                      apr_status_t& outSerfStatus );

    //UNLOCK
    bool processUnlock( const rtl::OUString & inDestinationPath,
                        const com::sun::star::ucb::Lock& inLock,
                        apr_status_t& outSerfStatus );

    apr_status_t provideSerfCredentials( char ** outUsername, 
                                         char ** outPassword,
                                         serf_request_t * inRequest, 
                                         int inCode, 
                                         const char *inAuthProtocol,
                                         const char *inRealm,
                                         apr_pool_t *inAprPool );

    apr_status_t setupSerfRequest( serf_request_t * inSerfRequest,
                                   serf_bucket_t ** outSerfRequestBucket,
                                   serf_response_acceptor_t * outSerfResponseAcceptor,
                                   void ** outSerfResponseAcceptorBaton,
                                   serf_response_handler_t * outSerfResponseHandler,
                                   void ** outSerfResponseHandlerBaton,
                                   apr_pool_t * inAprPool );

    serf_bucket_t* acceptSerfResponse( serf_request_t * inSerfRequest,
                                       serf_bucket_t * inSerfStreamBucket,
                                       apr_pool_t* inAprPool );

    apr_status_t handleSerfResponse( serf_request_t * inSerfRequest,
                                     serf_bucket_t * inSerfResponseBucket,
                                     apr_pool_t * inAprPool );

//private:
    void prepareProcessor();
    apr_status_t runProcessor();
    void postprocessProcessor( const apr_status_t inStatus );

    SerfSession& mrSerfSession;
    const char* mPathStr;
    const bool mbUseChunkedEncoding;
    const char* mDestPathStr;
    const char* mContentType;
    const char* mReferer;
    SerfRequestProcessorImpl* mpProcImpl;

    bool mbProcessingDone;

    DAVException* mpDAVException; 
    sal_uInt16 mnHTTPStatusCode;
    rtl::OUString mHTTPStatusCodeText;
    rtl::OUString mRedirectLocation; 

    sal_uInt8 mnSuccessfulCredentialAttempts;
    bool mbInputOfCredentialsAborted;
    bool mbSetupSerfRequestCalled;
    bool mbAcceptSerfResponseCalled;
    bool mbHandleSerfResponseCalled;
};

} // namespace http_dav_ucp

#endif // INCLUDED_SERFREQUESTPROCESSOR_HXX