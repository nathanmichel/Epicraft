//
// EPITECH PROJECT, 2019
// Epitain
// File description:
// main
//

#include "Epitain.hpp"
#include "TcpServer.hpp"

int	main()
{
	net::TcpServer server(25565);

	server.run();
	return 0;
}
