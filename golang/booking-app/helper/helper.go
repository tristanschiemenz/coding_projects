package helper

import "strings"

func ValidateUser(firstName string, lastName string, userEmail string, ticketNumber uint, remaingTickets uint) (bool, bool, bool) {
	var isValidName bool = len(firstName) >= 3 && len(lastName) >= 3
	var isValidEmail bool = strings.Contains(userEmail, "@")
	var isValidTickes bool = ticketNumber > 0 && ticketNumber <= remaingTickets
	return isValidName, isValidEmail, isValidTickes
}
