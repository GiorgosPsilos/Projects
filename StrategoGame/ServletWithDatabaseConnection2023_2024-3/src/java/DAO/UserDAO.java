package DAO;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class UserDAO {

    private Connection connection;

    public UserDAO(Connection connection) {
        this.connection = connection;
    }

    public boolean updateUser(String username, String newPassword, String newFirstName, String newLastName, String newCountry, String newJob, String newCity, String newAddress, String newPersonalPage, String newTelephone)
            throws SQLException {
        boolean isUpdated = false;
        PreparedStatement preparedStatement = null;

        try {
            String updateQuery = "UPDATE petkeepers SET password=?, firstname=?, lastname=?, country=?, job=?, city=?, address=?, personalpage=?, telephone=? WHERE username=?";
            preparedStatement = connection.prepareStatement(updateQuery);

            preparedStatement.setString(1, newPassword);
            preparedStatement.setString(2, newFirstName);
            preparedStatement.setString(3, newLastName);
            preparedStatement.setString(4, newCountry);
            preparedStatement.setString(5, newJob);
            preparedStatement.setString(6, newCity);
            preparedStatement.setString(7, newAddress);
            preparedStatement.setString(8, newPersonalPage);
            preparedStatement.setString(9, newTelephone);
            preparedStatement.setString(10, username);


            int rowsAffected = preparedStatement.executeUpdate();
            connection.commit();

            isUpdated = rowsAffected > 0;
        } finally {
            if (preparedStatement != null) {
                preparedStatement.close();
            }
        }

        return isUpdated;
    }

}
