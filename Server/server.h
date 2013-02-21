
/**
 * @brief Display on the standard output the array of connected players.
 */
void display_online_players();

/**
 * @brief Interprete the action wanted by the client and execute it.
 * @param sock
 */
void * client_manager(void * sock);

/**
 * @brief Interprete the action wanted by the client and execute it.
 * @param sock
 */
void * client_manager_cmd(void * sock);

/**
 * @brief Send an information (determinize by the command) to all the clients.
 * @param command
 */
void alert_all_client(char * command);