package servlets;

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import database.DB_Connection;
import DAO.UserDAO;
import java.sql.SQLException;

public class LoginServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String action = request.getParameter("action");

        if ("edit".equals(action)) {
            String username = request.getParameter("username");
            String newPassword = request.getParameter("password");
            String newFirstName = request.getParameter("firstname");
            String newLastName = request.getParameter("lastname");
            String newCountry = request.getParameter("country");
            String newBirthdate = request.getParameter("birthdate");
            String newGender = request.getParameter("gender");
            String newCity = request.getParameter("city");
            String newAddress = request.getParameter("address");
            String newPersonalPage = request.getParameter("personalpage");
            String newJob = request.getParameter("job");
            String newTelephone = request.getParameter("telephone");
            String userType = request.getParameter("userType");
            String property = request.getParameter("property");
            String propertydescription = request.getParameter("propertydescription");
            String catkeeper = request.getParameter("catkeeper");
            String dogkeeper = request.getParameter("dogkeeper");
            String catprice = request.getParameter("catprice");
            String dogprice = request.getParameter("dogprice");
            DB_Connection dbConnection = new DB_Connection();

            try {
                UserDAO userDAO = new UserDAO(dbConnection.getConnection());

                // Implement logic to update user information in the database
                boolean isUpdated = userDAO.updateUser(username, newPassword, newFirstName, newLastName, newCountry, newJob, newCity, newAddress, newPersonalPage, newTelephone);

                // Send a response back to the client
                response.setContentType("text/html");
                PrintWriter out = response.getWriter();
                out.println("<html><body>");

                if (isUpdated) {
                    out.println("<h2>User information updated successfully!</h2>");
                } else {
                    out.println("<h2>Error updating user information.</h2>");
                }

                out.println("</body></html>");
            } catch (ClassNotFoundException | SQLException e) {
                // Handle exceptions appropriately
                e.printStackTrace();
            }
        }
    }

}
