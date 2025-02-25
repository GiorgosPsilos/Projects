package strategogame.gui.board;

import javafx.scene.layout.GridPane;

import strategogame.game.board.ClientBoard;

/**
 * Layered directly on top of the BoardPane. Allows the player to interact with 
 * the board.
 */
public class BoardEventPane extends GridPane {
    
    /**
     * Creates a new instance of BoardPane.
     * @param board the Stratego board model
     */
    public BoardEventPane(ClientBoard board) {
        final int numRows = 8;
        final int numCols = 10;
        
        // Initiate piece layer.
        for (int row = 0; row < numRows; ++row) {
            for (int col = 0; col < numCols; ++col) {
                BoardSquareEventPane square = board.getSquare(row, col).getEventPane();
                
                add(square, col, row);
                GridPane.setRowIndex(square.getHover(), row);
                GridPane.setColumnIndex(square.getHover(), col);
            }
        }
    }
}