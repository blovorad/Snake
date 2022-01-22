#ifndef __PROTOTYPE__H__
#define __PROTOTYPE__H__

#include "structure.h"

//CLEANUP FUNCTION
extern void cleanUp(void);
extern void cleanAudio(void);
extern void cleanSnake(void);
extern void cleanMap(void);
extern void cleanGame(void);
extern void cleanFont1(void);
extern void cleanGameGui(void);
extern void cleanMainMenu(void);
extern void cleanOption(void);
extern void cleanSelectDifficulty(void);
extern void cleanBouleDeFeu(void);
extern void cleanFx(void);

//INIT FUNCTION
extern void init(void);
extern void initMouse(void);
extern void initAudio(int nbMusic, int nbFx);
extern void initSnake(void);
extern void initMap(SDL_bool activeQuadrillage, int pMap);
extern void initTrainer(void);
extern void initFont1(void);
extern void initGame(void);
extern void initGameGui(void);
extern void initMainMenu(void);
extern void initSceneManager(void);
extern void initOption(void);
extern void initEvent(void);
extern void initSelectDifficulty(void);
extern void initBouleDeFeu(int x, int y, Vecteur vitesse);

//UPDATE FUNCTION
extern void update(Input *input);
extern void updateSnake(Input *input);
extern void updateGame(Input *input);
extern void updateTrainer(void);
extern void updateAudio(void);
extern void updateMainMenu(void);
extern void updateOption(void);
extern void updateSelectDifficulty(void);
extern void updateBouleDeFeu(void);

//DRAW FUNCTION
extern void draw(void);
extern void drawSnake(void);
extern void drawMap(void);
extern void drawTrainer(void);
extern void drawGame(void);
extern void drawRect(SDL_Rect *r, SDL_bool *fill, SDL_Color *couleur);
extern void drawTexture(SDL_Texture *texture, SDL_Rect *dst, SDL_Rect *src);
extern void drawTextureEx(SDL_Texture *texture, SDL_Rect *dst, SDL_Rect *src, int angle);
extern void setRenderColor(SDL_Color *couleur);
extern void drawLine(int *x1, int *y1, int *x2, int *y2, SDL_Color *couleur);
extern void drawPoint(int *x, int *y, SDL_Color *couleur);
extern void drawGameGui(void);
extern void drawMainMenu(void);
extern void drawOption(void);
extern void drawSelectDifficulty(void);
extern void drawBouleDeFeu(void);

//GUI FUNCTION
extern Panel createPanel(int x, int y, int w, int h, char *texture, SDL_Color color, SDL_bool pFill);
extern Texte createTexte(int x, int y, int w, int h, char *texte, SDL_Color color, TTF_Font *font);
extern Barre createBarre(int x, int y, int w, int h, SDL_Color color);
extern Bouton createBouton(int x, int y, int w, int h, char *panelTexture, SDL_Color panelColor, char *ptexte, SDL_Color texteColor, TTF_Font *font, SDL_bool pFill, int event);

//COLOR FUNCTION
extern SDL_Color getVert(int alpha);
extern SDL_Color getVertFoncer(int alpha);
extern SDL_Color getGris(int alpha);
extern SDL_Color getRouge(int alpha);
extern SDL_Color getBleu(int alpha);
extern SDL_Color getBlanc(int alpha);
extern SDL_Color getNoir(int alpha);
extern SDL_Color getMarron(int alpha);
extern SDL_Color getJaune(int alpha);

//SCENEMANAGER FUNCTION
extern SDL_bool isActiveMainMenu(void);
extern SDL_bool isActiveGame(void);
extern SDL_bool isActiveOption(void);
extern SDL_bool isActiveSelectDifficulty(void);
extern void setPrintOption(SDL_bool active);
extern void setPrintMainMenu(SDL_bool active);
extern void setPrintGame(SDL_bool active);
extern void setPrintSelectDifficulty(SDL_bool active);

//SCREEN FUNCTION
extern SDL_Renderer *getRenderer(void);
extern SDL_Window *getWindow(void);
extern SDL_bool getFullscreen(void);
extern void changeFullscreen(SDL_bool active);
extern void changeLangue(int n);
extern void createNewRendererAndWindow(void);
extern void saveConfig(void);
extern int getWidth(void);
extern int getHeight(void);
extern int getLangue(void);
extern float getScaleX(void);
extern float getScaleY(void);

//INPUT FUNCTION
extern void getInput(Input *input);

//FONT FUNCTION
extern TTF_Font *getFont1(void);

//GAME FUNCTION
extern void addScore(int pScore);
extern void manageExitGame(void);
extern void activeEnd(void);
extern void loadHighScore(void);
extern void saveHighScore(void);

//TRAINER FUNCTION
extern void removeTrainer(void);
extern void addTrainer(int x, int y, int vie, int vx, int vy, SDL_Color couleur);

//MAP FUNCTION
extern void removeApple(int x, int y);
extern void addApple(void);
extern void removeBlock(int x, int y);
extern int getTileAt(int x, int y);
extern int getMapHeight(void);
extern int getMapWidth(void);

//MOUSE FUNCTION
extern SDL_bool getStateOfRightButton(void);
extern SDL_bool getStateOfLeftButton(void);
extern SDL_bool getStateOfOldRightButton(void);
extern SDL_bool getStateOfOldLeftButton(void);
extern void getMousePos(void);
extern void actualiseRightButton(SDL_bool newActualisation);
extern void actualiseLeftButton(SDL_bool newActualisation);
extern void actualiseOldRightButton(void);
extern void actualiseOldLeftButton(void);
extern int getMouseX(void);
extern int getMouseY(void);

//SNAKE FUNCTION
extern SDL_bool isBlock(void);
extern Vecteur getSnakeVitesse(void);
extern void addNewCorps(void);
extern void movingSnake(Input *input);
extern int getXPosSnake(int i, int diviseur);
extern int getYPosSnake(int i, int diviseur);
extern int getSnakeSize(void);

//EVENT FUNCTION
extern void startGame(void);
extern void quitGame(void);
extern void setQuadrillage(void);
extern void setEasy(void);
extern void setMedium(void);
extern void setHard(void);
extern void setFullscreen(void);
extern void goToOption(void);
extern void goToMenu(void);
extern void backToMenu(void);
extern void addVolumeMusique(void);
extern void addVolumeFx(void);
extern void setLangue(void);
extern void removeVolumeMusique(void);
extern void removeVolumeFx(void);
extern void playEvent(int event);

//SELECTDIFFICULTY FUNCTION
extern SDL_bool getQuadrillageActive(void);
extern void changeQuadrillage(void);
extern void setSelectLevel(int level);
extern int getLevel(void);

//BOULEDEFEU FUNCTION
extern SDL_bool isActiveBouleDeFeu(void);
extern void createExplosion(void);

//AUDIO FUNCTION
extern void playFx(int fx);
extern void startMusic(int music, SDL_bool loop);
extern void upVolumeFx(void);
extern void downVolumeFx(void);
extern void upVolumeMusic(void);
extern void downVolumeMusic(void);
extern int getVolumeMusic(void);
extern int getVolumeFx(void);

//TEXTURE FUNCTION
SDL_Texture *createTexture(char *chemin, SDL_Rect *rect);

//MATH FUNCTION
extern SDL_bool collide(SDL_Rect *a, SDL_Rect *b);
extern int absolue(int *a, int *b);

#endif