from stockfish import Stockfish

def chess_bot(obs):
    """
    Simple chess bot that prioritizes checkmates, then captures, queen promotions, then randomly moves.

    Args:
        obs: An object with a 'board' attribute representing the current board state as a FEN string.

    Returns:
        A string representing the chosen move in UCI notation (e.g., "e2e4")
    """
    # Initialize the Stockfish engine
    stockfish_path = r"C:\Users\USER\Desktop\Supahotfile\Kaggle\GoogleChessAI\kaggle\input\stockfish\stockfish-windows-x86-64-avx2.exe"
    stockfish = Stockfish(path=stockfish_path)

    # Set the board position using the FEN string from observation
    fen = obs.board  # FEN string representing the current board state
    stockfish.set_fen_position(fen)

    # Get the best move from Stockfish
    best_move = stockfish.get_best_move(1000)

    return best_move