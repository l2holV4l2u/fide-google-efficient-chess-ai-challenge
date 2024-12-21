from Chessnut import Game
import subprocess
import os

class ChessEngine:
    def __init__(self, engine_path):
        # Check if the engine file exists
        if not os.path.exists(engine_path):
            raise FileNotFoundError(f"Engine file not found at {engine_path}")

        #  Initialize the subprocess
        self.engine = subprocess.Popen(
            [engine_path],
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True
        )

    def _send_command(self, command):
        self.engine.stdin.write(command + "\n")
        self.engine.stdin.flush()

    def _read_output(self):
        output = self.engine.stdout.readline().strip()
        return output

    def get_best_move(self, fen, movetime=100):
        self._send_command(fen)
        best_move = None
        while True:
            best_move = self._read_output()
            if best_move:
                break
        return best_move

    def stop(self):
        self._send_command("q")
        self.engine.terminate()
        self.engine.wait()


engine_path = r'C:\Users\USER\Desktop\Supahotfile\fide-google-efficient-chess-ai-challenge\engine\main.exe'
engine = None

def chess_bot(obs):    
    global engine
    fen = obs['board']
    if engine is None:
        engine = ChessEngine(engine_path)
    best_move = engine.get_best_move(fen)
    print(best_move)
    return best_move
