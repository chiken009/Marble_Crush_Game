class Block{
 private:
  int posX, posY; // Block's position
  int colnum;
  int colnum2;

 public:
  void Create();
  void Draw(int a);
  void Destroy();
  
  Block();
  virtual ~Block();
  // Get position
  int GetPosX();
  int GetPosY();
  int GetCol();

  // Set position
  void setPos(int co);
  void SetPosX(int x);
  void SetPosY(int y);
  void delpos();
  // Transformation
  int Rotate(int direction, int originX, int originY);
  int CanRotate(int direction, int originX, int originY);
  int Translate(int offsetX, int offsetY);
  int CanTranslate(int offsetX, int offsetY);
  
  
  // Assignment operator
  Block & operator = (Block & other){
    if(this!=&other){
      SetPosX(other.GetPosX());
      SetPosY(other.GetPosY());
    }
    return *this;
  }
};


class Figure{
 private:
  int posX, posY;
  int canRotate;
  int cnum;
  int cnum2;
 public:
  Block *data;
  void Create(int numFigure); // Create figures, 
  void Draw();
  void Destroy();

  Figure(int numFigure);
  Figure();
  virtual ~Figure();
  
  // Get/Set figure
  int GetPosX();
  int GetPosY();
  int GetCol();
  int GetCol2();
  void SetPosX(int x);
  void SetPosY(int y);
  
  Block *GetFigure();
  void New(int numFigure);
  void Clear();


  // Transformation
  int Rotate(int direction);
  int Translate(int offsetX, int offsetY);
};

class Game{
 private:
  int num_row, num_col;
  int map[100][100];
  float mapcol[100][100][3];
  int mapcont[100][100];
  int conum, conum2;
  int n;
  int dnum;
  int sleepnum;
 public:
  // Constructor, Destructor
  Game();
  virtual ~Game();
  
  // Draw
  int boundding();
  void Draw();
  void graymap();
  void Count(int x, int y, int *n);
  void Vanish(int x, int y);
  int FallPuyo(void);
  void drawmap();
  void GrayCount();
  // Update
  void SetMap(int x, int y, int col);
  void DeleteMap(int px, int py);
  int DeletePuyo(void);
  int Update(Figure &figure);
  int RowIsFull(int row);
  void ClearRow(int row);
  void New();
  void SetConum(int b);
  void SetConum2(int b);
  void Print();
  int GetMap(int x, int y);
};
