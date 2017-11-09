#pragma once
class CPHReqComparerV;
#include "../xrphysics/iphworld.h"
class IPhysicsShellEx;

class CPHReqBase
{
public:
	virtual						~CPHReqBase						()									{}
	virtual bool 				obsolete						()							const	=0;
	virtual bool				compare							(const CPHReqComparerV* v)	const	{return false;};
};

class CPHCondition : public CPHReqBase
{
public:
	virtual bool 			is_true							()=0;
};

class CPHAction: public CPHReqBase
{
public:
	virtual void 			run								()=0;
};

class CPHOnesCondition: public CPHCondition
{
	bool isCalled;
public:
							CPHOnesCondition				(){isCalled=false;}
	virtual bool 			is_true							(){isCalled =true;return true;}
	virtual bool 			obsolete						()const{return isCalled;}
};

class CPHDummiAction:
	public CPHAction
{
public:
	virtual void 			run								(){;}
	virtual bool 			obsolete						()const	{return false;}
};

class CPHCall
{
	CPHAction*		m_action;
	CPHCondition*	m_condition;
public:
					CPHCall							(CPHCondition* condition,CPHAction* action);
					~CPHCall						();
	void 			check							();
	bool 			obsolete						();
	bool			equal							(CPHReqComparerV* cmp_condition,CPHReqComparerV* cmp_action);
	bool			is_any							(CPHReqComparerV* v);
#ifdef DEBUG
const CPHAction		*action							()const{ return m_action;}
const CPHCondition	*condition						()const{ return m_condition;}
#endif
};

using PHCALL_STORAGE = xr_vector<CPHCall*>;
using PHCALL_I = PHCALL_STORAGE::iterator;
class CPHCommander: public IPHWorldUpdateCallbck
{
	std::recursive_mutex lock;
	PHCALL_STORAGE	m_calls;
public:
						~CPHCommander				()																;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool				add_call_unique				(CPHCondition* condition,CPHReqComparerV* cmp_condition,CPHAction* action,CPHReqComparerV* cmp_action);
	void				add_call					(CPHCondition* condition,CPHAction* action);
	void				add_call_threadsafety		(CPHCondition* condition,CPHAction* action);

	void				remove_call					(PHCALL_I i);
	bool				has_call					(CPHReqComparerV* cmp_condition,CPHReqComparerV* cmp_action);	
	PHCALL_I			find_call					(CPHReqComparerV* cmp_condition,CPHReqComparerV* cmp_action);				
	void				remove_call					(CPHReqComparerV* cmp_condition,CPHReqComparerV* cmp_action);
	void				remove_calls				(CPHReqComparerV* cmp_object);
	void				remove_calls_threadsafety	(CPHReqComparerV* cmp_object);

	void				clear						();
	void				update  					();
	void				update_threadsafety 		();

private:
	virtual	void		update_step					() { update_threadsafety(); }
	virtual	void		phys_shell_relcase			(IPhysicsShellEx* sh);
};