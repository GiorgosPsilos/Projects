package strategogame.gui.board;

import javafx.scene.layout.GridPane;

import strategogame.game.board.ClientBoard;
import strategogame.media.ImageConstants;

/**
 * A graphical representation of the Stratego board.
 */
public class BoardPane extends GridPane {
    
    /**
     * Creates a new instance of BoardPane.
     * @param board the Stratego board model
     */
    public BoardPane(ClientBoard board) {
        final int numRows = 8;
        final int numCols = 10;
        
        // Initiate board pane.
        for (int row = 0; row < numRows; ++row) {
            for (int col = 0; col < numCols; ++col) {
                add(board.getSquare(row, col).getPiecePane(), col, row);
            }
        }
        
        // Add the two lakes.
        board.getSquare(3, 2).getPiecePane().setPiece(ImageConstants.LAKE_1_1);
        board.getSquare(3, 3).getPiecePane().setPiece(ImageConstants.LAKE_1_2);
        board.getSquare(4, 2).getPiecePane().setPiece(ImageConstants.LAKE_1_3);
        board.getSquare(4, 3).getPiecePane().setPiece(ImageConstants.LAKE_1_4);
        
        board.getSquare(3, 6).getPiecePane().setPiece(ImageConstants.LAKE_2_1);
        board.getSquare(3, 7).getPiecePane().setPiece(ImageConstants.LAKE_2_2);
        board.getSquare(4, 6).getPiecePane().setPiece(ImageConstants.LAKE_2_3);
        board.getSquare(4, 7).getPiecePane().setPiece(ImageConstants.LAKE_2_4);
    }
}