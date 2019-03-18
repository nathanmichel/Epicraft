//
// EPITECH PROJECT, 2019
// Epicraft
// File description:
// Play
//

#include "Play.hpp"
#include "Manager.hpp"

prot::Play::Play(mgr::Manager &manager) : _manager(manager)
{

}

void	prot::Play::playerPositionAndLook(const net::request_t *request)
{
	net::response_t *response = new net::response_t;

	response->data.reserve(36);
	response->data[0] = 0x23;
	response->data[1] = 0x32;
	std::memset(&response->data[2], 1, 34);
	response->size = response->data.size();
	response->id = request->id;
	_manager.callback(response);
}

void	prot::Play::playerAbilities(const net::request_t *request)
{
	net::response_t *response = new net::response_t;

	response->data.reserve(11);
	response->data[0] = 0x0a;
	response->data[1] = 0x2e;
	std::memset(&response->data[2], 0, 9);
	response->size = response->data.size();
	response->id = request->id;
	_manager.callback(response);
	playerPositionAndLook(request);
}

void	prot::Play::spawnPosition(const net::request_t *request)
{
	net::response_t *response = new net::response_t;

	response->data.push_back(0x09);
	response->data.push_back(0x49);
	response->data.push_back(0x00);
	response->data.push_back(0x00);
	response->data.push_back(0x00);
	response->data.push_back(0x00);
	response->data.push_back(0x00);
	response->data.push_back(0x00);
	response->data.push_back(0x00);
	response->data.push_back(0x00);
	response->size = response->data.size();
	response->id = request->id;
	_manager.callback(response);
	playerAbilities(request);
}

void	prot::Play::joinGame(const net::request_t *request)
{
	request->status = prot::play;
	net::response_t *response = new net::response_t;
	int eid = 1;
	unsigned char gamemode = 0;
	int dimension = 0;
	unsigned char difficulty = 1;
	unsigned char maxPlayers = 10;
	std::string level("default");
	bool reducedDebug = 0;

	misc::writeVarInt(13 + misc::getVarIntSize(level.size()) + level.size(), response->data);
	response->data.push_back(0x25);
	response->data.push_back(0x00);
	response->data.push_back(0x00);
	response->data.push_back(0x00);
	response->data.push_back(0x01);
	response->data.push_back(0x00);
	response->data.push_back(0x00);
	response->data.push_back(0x00);
	response->data.push_back(0x00);
	response->data.push_back(0x00);
	response->data.push_back(0x00);
	response->data.push_back(10);
	misc::writeVarInt(level.size(), response->data);
	std::copy(level.begin(), level.end(), std::back_inserter<std::vector<char>> (response->data));
	response->data.push_back(0x00);
	response->size = response->data.size();
	response->id = request->id;
	_manager.callback(response);
	spawnPosition(request);
}

void	prot::Play::parseProtocol(const net::request_t *request)
{

}
