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




#ifndef ADC_CPP_PE_TYPE_HXX
#define ADC_CPP_PE_TYPE_HXX



// USED SERVICES
	// BASE CLASSES
#include "cpp_pe.hxx"
	// COMPONENTS
#include <ary/cpp/usedtype.hxx>
#include <semantic/callf.hxx>
#include <semantic/sub_peu.hxx>
	// PARAMETERS
#include <ary/cpp/c_types4cpp.hxx>



namespace cpp {

class PE_Class;
class PE_Enum;
class PE_Expression;

class PE_Type : public Cpp_PE
{
  public:
	enum E_State
	{
		start,
		expect_namesegment,
		after_namesegment,
		afterclass_expect_semicolon,
		within_template,
		within_indirection,
		size_of_states
	};
	enum E_KindOfResult
	{
		is_none,
		is_type,
		is_constructor,
		is_explicit_class_declaration,
        is_class_predeclaration,
		is_explicit_enum_declaration
	};

						PE_Type(
							Cpp_PE *			i_pParent );
						~PE_Type();

    void                Init_AsCastOperatorType();

	virtual void		Call_Handler(
							const cpp::Token &	i_rTok );

	E_KindOfResult		Result_KindOf() const;
	const ary::cpp::Type &
						Result_Type() const;
  private:
	typedef SubPe< PE_Type, PE_Type >		    SP_Type;
	typedef SubPe< PE_Type, PE_Class >		    SP_Class;
	typedef SubPe< PE_Type, PE_Enum >		    SP_Enum;
	typedef SubPeUse< PE_Type, PE_Type >	    SPU_Type;
	typedef SubPeUse< PE_Type, PE_Class >	    SPU_Class;
	typedef SubPeUse< PE_Type, PE_Enum >	    SPU_Enum;

	void				Setup_StatusFunctions();
	virtual void		InitData();
	virtual void		TransferData();
	void  				Hdl_SyntaxError( const char *);

	void				SpReturn_Type_TemplateParameter();
	void				SpReturn_Class();
	void				SpReturn_Enum();

	void				On_EndOfType(const char *);

	void				On_start_Identifier(const char *);
	void				On_start_class(const char *);
	void				On_start_enum(const char *);
	void				On_start_const(const char *);
	void				On_start_volatile(const char *);
	void				On_start_Bracket_Right(const char *);
	void				On_start_DoubleColon(const char *);
	void				On_start_BuiltInType(const char *);
	void				On_start_TypeSpecializer(const char *);
	void				On_start_typename(const char *);

	void				On_expect_namesegment_Identifier(const char *);

	void				On_after_namesegment_const(const char *);
	void				On_after_namesegment_volatile(const char *);
    void                On_after_namesegment_Bracket_Left(const char *);
	void				On_after_namesegment_DoubleColon(const char *);
	void				On_after_namesegment_Less(const char *);
	void				On_after_namesegment_Asterix(const char *);
	void				On_after_namesegment_AmpersAnd(const char *);

	void				On_afterclass_expect_semicolon_Semicolon(const char *);

	void				On_within_template_Comma(const char *);
	void				On_within_template_Greater(const char *);
	void				On_within_template_Constant(const char *);
	void				On_within_template_TypeStart(const char *);

	void				On_within_indirection_const(const char *);
	void				On_within_indirection_volatile(const char *);
	void				On_within_indirection_Asterix(const char *);
	void				On_within_indirection_AmpersAnd(const char *);

	bool				IsType() const;

	// DATA
	Dyn< PeStatusArray<PE_Type> >
						pStati;

	Dyn<SP_Type>	    pSpType;
	Dyn<SPU_Type>	 	pSpuType_TemplateParameter;
	Dyn<SP_Class>	    pSpClass;
	Dyn<SPU_Class>	 	pSpuClass;
	Dyn<SP_Enum>	    pSpEnum;
	Dyn<SPU_Enum>	 	pSpuEnum;

	Dyn<ary::cpp::UsedType>
						pType;
    ary::cpp::ut::List_TplParameter *
                        pCurTemplate_ParameterList;
	String              sOwningClassName;
    String 				sParsedClass_Name;

	const ary::cpp::Type *
						pResult_Type;
	E_KindOfResult		eResult_KindOf;
    bool                bIsCastOperatorType;
};



// IMPLEMENTATION


inline const ary::cpp::Type &
PE_Type::Result_Type() const
	{ csv_assert(pResult_Type != 0);
	  return *pResult_Type; }
inline PE_Type::E_KindOfResult
PE_Type::Result_KindOf() const
	{ return eResult_KindOf; }


}   // namespace cpp


#endif



