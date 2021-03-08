#ifndef COR_UNICHANNEL_CLIENT_HPP
#define COR_UNICHANNEL_CLIENT_HPP

#include "cor/resources/uni_channel.hpp"

#include <hpx/hpx.hpp>



namespace cor {

template <typename T>
class UniChannel_Client : hpx::components::client_base<UniChannel_Client<T>, UniChannel<T>> 
{

public:
	typedef hpx::components::client_base<UniChannel_Client<T>, UniChannel<T>> base_type;

	friend class hpx::serialization::access;

	typedef nullptr_t organizer;

	// Default construct an empty client side representation (not
	// connected to any existing component). Also needed for serialization
    UniChannel_Client()
    {}

	// Create a client side representation for the existing
	// UniChannel instance with the given GID
    UniChannel_Client(hpx::future<hpx::id_type> && id) :
        base_type(std::move(id)),
		_idp(IdpGlobal())
    {}

    UniChannel_Client(hpx::shared_future<hpx::id_type> && id) :
        base_type(std::move(id)),
		_idp(IdpGlobal())
    {}

    UniChannel_Client(hpx::id_type && id) :
        base_type(std::move(id)),
		_idp(IdpGlobal())
    {}

	// Constructor for replicas
    UniChannel_Client(idp_t idp, hpx::future<hpx::id_type> && id) :
        base_type(std::move(id)),
		_idp(idp)
    {}

    UniChannel_Client(idp_t idp, hpx::shared_future<hpx::id_type> && id) :
        base_type(std::move(id)),
		_idp(idp)
    {}

    UniChannel_Client(idp_t idp, hpx::id_type && id) :
        base_type(std::move(id)),
		_idp(idp)
    {}

	// Standard constructor with parameters
    UniChannel_Client(idp_t idp) :
        base_type(create_server(idp)),
		_idp(idp)
    {}

    // UniChannel_Client(idp_t idp, hpx::id_type locality) :
    //     base_type(create_server_remote(idp, locality)),
	// 	_idp(idp)
    // {}



	/** Resource's interface **/
	// method that returns the global idp of the resource, which is present in the class Resource
	hpx::future<idp_t> IdpGlobal(hpx::launch::async_policy)
	{
		typedef Resource::Idp_action_Resource action_type;
		return hpx::async<action_type>(base_type::get_id());
	}

	idp_t IdpGlobal()
	{
		typedef Resource::Idp_action_Resource action_type;
		return action_type()(base_type::get_id());
	}

	// method that returns the GID(hpx::id_type) of this resource locality
	hpx::future<hpx::id_type> GetLocalityGID(hpx::launch::async_policy)
	{
		typedef Resource::GetLocalityGID_action_Resource action_type;
		return hpx::async<action_type>(base_type::get_id());
	}

	hpx::id_type GetLocalityGID()
	{
		typedef Resource::GetLocalityGID_action_Resource action_type;
		return action_type()(base_type::get_id());
	}

	// method that returns the number of this resource locality
	hpx::future<unsigned int> GetLocalityID(hpx::launch::async_policy)
	{
		typedef Resource::GetLocalityID_action_Resource action_type;
		return hpx::async<action_type>(base_type::get_id());
	}

	unsigned int GetLocalityID()
	{
		typedef Resource::GetLocalityID_action_Resource action_type;
		return action_type()(base_type::get_id());	
	}




	/** UniChannel's interface **/
    hpx::future<T> Get(std::size_t step) 
	{
		typedef typename UniChannel<T>::Get_action_UniChannel action_type;
		return action_type()(this->get_id(), step); 	
	}

    void Set(T&& t, std::size_t step) 
	{
		typedef typename UniChannel<T>::Set_action_UniChannel action_type;
		return action_type()(this->get_id(), std::move(t), step); 	
	}








	/** Local Client's interface **/
	// local idp of this resource
	hpx::future<idp_t> Idp(hpx::launch::async_policy) {
		return hpx::make_ready_future(_idp);
	}

	idp_t Idp() {
		return _idp;
	}

	// Returns component's GID
	hpx::future<hpx::id_type> GetGid(hpx::launch::async_policy) {
	  	return hpx::make_ready_future(this->get_id());
	}

	hpx::id_type GetGid() {
	  	return this->get_id();
	}

	hpx::future<int> GetComponentType(hpx::launch::async_policy)
	{
		/* Resource identification
		1 - Domain
		2 - Group
		3 - Clousure
		4 - ProtoAgent
		5 - Agent
		6 - UniChannel
		7 - Barrier
		8 - Mutex
		9 - RWMutex
		10 - UniChannel
		*/
		return hpx::make_ready_future(10);
	}

	int GetComponentType()
	{
		return 10;
	}

	// For compilation purposes only, it is never used here!
	hpx::future<hpx::id_type> GetMailboxGid(hpx::launch::async_policy) {
		return hpx::make_ready_future(hpx::find_here());
	}

	hpx::id_type GetMailboxGid() {
		return hpx::find_here();
	}
	

private:
	hpx::future<hpx::id_type> create_server(idp_t idp) {
		return hpx::local_new<UniChannel<T>>(idp);
	}

	hpx::future<hpx::id_type> create_server_remote(idp_t idp, hpx::id_type locality) {
		return hpx::new_<UniChannel<T>>(locality, idp);
	}

	template <typename Archive>
	void serialize(Archive& ar, unsigned) {   
		ar & _idp;
	}

	idp_t _idp;

};

	
}


#endif
