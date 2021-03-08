// #ifndef COR_MAILER_HPX_HPP
// #define COR_MAILER_HPX_HPP

// #include <thread>
// #include <map>
// #include <deque>
// #include <queue>
// #include <mutex>
// #include <condition_variable>

// #include "cor/utils/utils.hpp"

// #include <ssrc/spread.h>
// #include "cor/external/event/event.hpp"

// #include "cor/system/macros.hpp"
// #include "cor/message.hpp"

// namespace cor {

// class Mailer_hpx
// {

// friend class ResourceManager;

// public:
//     explicit Mailer_hpx(std::string const& id, std::string const& app_group);
//     ~Mailer_hpx();

//     void StartService();
//     void StopService();

//     void operator()();

//     void SendMessage(idp_t idp, idp_t dest, Message& msg);
//     void SendMessage(idp_t idp, std::vector<idp_t> const& dests, Message& msg);

//     Message ReceiveMessage(idp_t idp);
//     Message ReceiveMessage(idp_t idp, idp_t source);

//     // HPX
//     void SendMessage_hpx(idp_t idp, idp_t dest, Message& msg);
//     void SendMessage_hpx(idp_t idp, std::vector<idp_t> const& dests, Message& msg);

//     Message ReceiveMessage_hpx(idp_t idp);
//     Message ReceiveMessage_hpx(idp_t idp, idp_t source);

//     Mailer_hpx(Mailer_hpx const&) = delete;
//     Mailer_hpx& operator=(Mailer_hpx const&) = delete;
//     Mailer_hpx(Mailer_hpx&&) = delete;
//     Mailer_hpx& operator=(Mailer_hpx&&) = delete;

// protected:
//     // accessed by ResourceManager
//     void CreateMailbox(idp_t idp);
//     void DeleteMailbox(idp_t idp);

// private:
//     void Connect(std::string const& id);
//     void Close();

//     void HandleRead();
//     void HandleWrite();

//     void JoinGroup(std::string const& group);
//     void LeaveGroup(std::string const& group);

//     void JoinMessageGroup(idp_t idp);
//     void LeaveMessageGroup(idp_t idp);

//     std::string GetMessageGroup(idp_t idp);
//     idp_t GetIdpFromMessageGroup(std::string const& group);

//     enum class MsgType: std::int16_t
//     {
//         Message
//     };

//     constexpr typename std::underlying_type<MsgType>::type underlying_cast(MsgType t) const noexcept
//     {
//         return static_cast<typename std::underlying_type<MsgType>::type>(t);
//     }

//     std::string _app_group;

//     // service thread
//     std::thread _th_svc;

//     // communication system
//     ssrc::spread::Mailbox *_mbox;
//     ev::EventBase *_base;
//     ev::Event *_evread;
//     ev::Event *_evwrite;

//     ssrc::spread::ScatterMessage _in_smsg;
//     ssrc::spread::GroupList _in_groups;
//     ssrc::spread::Message _in_msg;

//     ssrc::spread::ScatterMessage _out_smsg;
//     ssrc::spread::GroupList _out_groups;

//     // resources mailboxes
//     std::map<idp_t, std::deque<Message>> _mailboxes;
//     std::map<idp_t, std::condition_variable> _rwq;
//     std::mutex _mtx;

//     struct Out
// 	{
//         bool ongoingWrite = false;
// 		std::queue<std::pair<std::vector<std::string>, std::string>> q;
// 	};
// 	utils::Monitor<Out> _out_queue;

// 	// Hold the currently outgoing message
// 	std::vector<std::string> _outgoing_groups;
// 	std::string _outgoing_msg;

// };

// }

// #endif
