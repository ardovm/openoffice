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


#ifndef _L10N_TRANSLITERATION_CHARTONUM_HXX_
#define _L10N_TRANSLITERATION_CHARTONUM_HXX_

#include <transliteration_Numeric.hxx>

namespace com { namespace sun { namespace star { namespace i18n {

#define TRANSLITERATION_CHARTONUM( name ) \
class CharToNum##name : public transliteration_Numeric \
{ \
public: \
        CharToNum##name (); \
};

#ifdef TRANSLITERATION_ALL
TRANSLITERATION_CHARTONUM(Lower_zh_CN)
TRANSLITERATION_CHARTONUM(Upper_zh_CN)
TRANSLITERATION_CHARTONUM(Lower_zh_TW)
TRANSLITERATION_CHARTONUM(Upper_zh_TW)
TRANSLITERATION_CHARTONUM(Upper_ko)
TRANSLITERATION_CHARTONUM(Hangul_ko)
TRANSLITERATION_CHARTONUM(Lower_ko)
TRANSLITERATION_CHARTONUM(KanjiShort_ja_JP)
TRANSLITERATION_CHARTONUM(KanjiTraditional_ja_JP)
TRANSLITERATION_CHARTONUM(Fullwidth)
TRANSLITERATION_CHARTONUM(Indic_ar)
TRANSLITERATION_CHARTONUM(EastIndic_ar)
TRANSLITERATION_CHARTONUM(Indic_hi)
TRANSLITERATION_CHARTONUM(_th)
#endif
#undef TRANSLITERATION_CHARTONUM

} } } }
        
#endif // _L10N_TRANSLITERATION_CHARTONUM_HXX_
