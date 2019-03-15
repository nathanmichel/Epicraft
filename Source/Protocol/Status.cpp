//
// EPITECH PROJECT, 2019
// Epicraft
// File description:
// Status
//

#include "Status.hpp"
#include "Manager.hpp"
#include "Protocol.hpp"

const std::string JSON = "{\"version\":{\"name\":\"1.13.2\",\"protocol\":404},\"players\":{\"max\":10,\"online\":0},\"description\":{\"extra\":[{\"text\":\"Localhost\",\"color\":\"red\",\"bold\":true},{\"text\":\" test\",\"color\":\"green\",\"bold\":false}],\"text\":\"\"},\"favicon\":\"data:image/png;base64,";

prot::Status::Status(mgr::Manager &manager) : _manager(manager)
{

}

void	prot::Status::getServerInformation(const std::size_t id)
{
	net::response_t *response = new net::response_t;
	std::string json = JSON + misc::base64Encode("../server-icon.png") + "\"}";

	misc::writeVarInt(json.size() + 1 + misc::getVarIntSize(json.size()), response->data);
	response->data.push_back(0);
        misc::writeVarInt(json.size(), response->data);
	std::copy(json.begin(), json.end(), std::back_inserter<std::vector<char>> (response->data));
	response->size = response->data.size();
	response->id = id;
	_manager.callback(response);
}

void	prot::Status::parsePing(const net::request_t *request)
{
	net::response_t *response = new net::response_t;

	misc::writeVarInt(request->size, response->data);
	std::copy(request->data.begin(), request->data.end(),
		  std::back_inserter<std::vector<char>> (response->data));
	response->size = response->data.size();
	response->id = request->id;
	_manager.callback(response);
}

void	prot::Status::parseProtocol(const net::request_t *request)
{
	if (request->data[0] == 0x00)
		getServerInformation(request->id);
	else if (request->data[0] == 0x01)
		parsePing(request);
}
