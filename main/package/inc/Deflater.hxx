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


#ifndef _DEFLATER_HXX_
#define _DEFLATER_HXX_

#include <com/sun/star/uno/Sequence.hxx>
#include <com/sun/star/uno/RuntimeException.hpp>

extern "C" 
{
	typedef struct z_stream_s z_stream;
}

/** Provides general purpose compression using the ZLIB compression
 * library.
 */
class Deflater
{
protected:
	com::sun::star::uno::Sequence< sal_Int8 > sInBuffer;
	sal_Bool				bFinish;
	sal_Bool				bFinished;
	sal_Bool				bSetParams;
	sal_Int32				nLevel, nStrategy;
	sal_Int32				nOffset, nLength;
	z_stream*				pStream;

	sal_Int32 doDeflateBytes (com::sun::star::uno::Sequence < sal_Int8 > &rBuffer, sal_Int32 nNewOffset, sal_Int32 nNewLength);
		
public:
	~Deflater();
    /** Constructor
     *
     * @param nSetLevel [0-9 or DEFAULT_COMPRESSION] compression level.
     *
     * @exception ::com::sun::star::uno::RuntimeException in case of problems.
     */
	Deflater(sal_Int32 nSetLevel, sal_Bool bNowrap);
    /** Indicate the data to be compressed.
     *
     * @param rBuffer buffer.
     * @param nNewOffset offset inside rBuffer.
     * @param nNewLength number of bytes to be compressed.
     *
     * @exception ::com::sun::star::uno::RuntimeException if the data is
     * not valid.
     */
    void SAL_CALL setInputSegment( const ::com::sun::star::uno::Sequence< sal_Int8 >& rBuffer, sal_Int32 nNewOffset, sal_Int32 nNewLength );
    /** Set the compression level
     *
     * @param nNewLevel [0-9 or DEFAULT_COMPRESSION] compression level.
     *
     * @exception ::com::sun::star::uno::RuntimeException in case of problems.
     */
    void SAL_CALL setLevel( sal_Int32 nNewLevel );
    sal_Bool SAL_CALL needsInput(  );
    void SAL_CALL finish(  );
    sal_Bool SAL_CALL finished(  );
    sal_Int32 SAL_CALL doDeflateSegment( ::com::sun::star::uno::Sequence< sal_Int8 >& rBuffer, sal_Int32 nNewOffset, sal_Int32 nNewLength );
    sal_Int32 SAL_CALL getTotalIn(  );
    sal_Int32 SAL_CALL getTotalOut(  );
    void SAL_CALL reset(  );
    void SAL_CALL end(  );
};

#endif
