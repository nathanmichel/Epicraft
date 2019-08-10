//
// EPITECH PROJECT, 2019
// Epicraft
// File description:
// Login
//

#include "Login.hpp"
#include "Manager.hpp"

prot::Login::Login(mgr::Manager &manager, prot::Play &play) : _manager(manager), _play(play)
{

}

void	prot::Login::loginSuccess(const std::string uuid, const std::string name, const net::request_t *request)
{
	net::response_t *response = new net::response_t;
	std::size_t uuidLen = uuid.size();
	std::size_t nameLen = name.size();

	misc::writeVarInt(1 + misc::getVarIntSize(uuidLen) + uuidLen + misc::getVarIntSize(nameLen) + nameLen,
			  response->data);
	response->data.push_back(0x02);
	misc::writeVarInt(uuidLen, response->data);
	std::copy(uuid.begin(), uuid.end(), std::back_inserter<std::vector<char>> (response->data));
	misc::writeVarInt(nameLen, response->data);
	std::copy(name.begin(), name.end(), std::back_inserter<std::vector<char>> (response->data));
	response->size = response->data.size();
	response->id = request->id;
	_manager.callback(response);
	misc::toLog("Login", name + " (" + uuid + ") join the server");
	_play.joinGame(request);
}

void	prot::Login::parseLogin(const net::request_t *request)
{
	std::size_t offset = 1;

	try {
		int nameLength = misc::readVarInt(request->data, offset, request->size);
		if (nameLength > 16) {
			std::cerr << "Invalid request (the username is too long)" << std::endl;
			return;
		}
		std::string name(request->data.begin() + offset, request->data.begin() + offset + nameLength);

		_mojangAPI.getUUID(name);
		loginSuccess("6f02141b-c5fa-40b2-b24d-5687562e37db", name, request);
	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
		return;
	}
}

void	prot::Login::parseProtocol(const net::request_t *request)
{
	if (request->data[0] != 0x00) {
		std::cerr << "Invalid Login" << std::endl;
		return;
	}
	parseLogin(request);
}
