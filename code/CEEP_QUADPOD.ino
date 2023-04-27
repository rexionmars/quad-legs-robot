/*     __                                    ___ 
 *    / /   ___  ____  ____  ____ __________/ (_
 *   / /   / _ \/ __ \/ __ \/ __ `/ ___/ __  / /
 *  / /___/  __/ /_/ / / / / /_/ / /  / /_/ / /
 * /_____/\___/\____/_/ /_/\__,_/_/   \__,_/_/
 * Email: opensource.leonardi@gmail.com
 * Google Dev: g.dev/leonardi
 * Github: rexionmars
 * Licensa: MIT
 */

#include <IRremote.h> // Importa a biblioteca do controle remoto IR
#include <Servo.h>    // Importa a biblioteca do Servo Motor

// Define os pinos e variaveis USRF
#define trigPin A3
#define echoPin A2
#define INCH 0
#define CM 1

// Define os codigos dos botões IR Remote
#define irUp  16736925
#define irDown 16754775
#define irRight 16761405
#define irLeft 16720605
#define irOK 16712445
#define ir1 16738455
#define ir2 16750695
#define ir3 16756815
#define ir4 16724175
#define ir5 16718055
#define ir6 16743045
#define ir7 16716015
#define ir8 16726215
#define ir9 16734885
#define ir0 16730805
#define irStar 16728765
#define irPound 16732845
#define irRepeat 4294967295

// Calibração inicial
int da =  -12, // Pivô dianteiro esquerdo
    db =   10, // Pivô traseiro esquerdo
    dc =  -18, // Pivô traseiro direito
    dd =   12; // Pivô dianteiro direito

// Posição do servo inicial + calibração inicial
int a90  = (90  + da),
    a120 = (120 + da),
    a150 = (150 + da),
    a180 = (180 + da);

int b0   = (0   + db),
    b30  = (30  + db),
    b60  = (60  + db),
    b90  = (90  + db);

int c90  = (90  + dc),
    c120 = (120 + dc),
    c150 = (150 + dc),
    c180 = (180 + dc);

int d0   = (0   + dd),
    d30  = (30  + dd),
    d60  = (60  + dd),
    d90  = (90  + dd);

// Inicia os pontos para servo motor
int s11 = 90; // Pivô dianteiro esquerdo Servo
int s12 = 90; // Levantamento frontal esquerdo Servo
int s21 = 90; // Pivô traseiro esquerdo Servo
int s22 = 90; // Levantamento traseiro esquerdo Servo
int s31 = 90; // Pivô traseiro direito Servo
int s32 = 90; // Levantamento traseiro direito Servo
int s41 = 90; // Pivô dianteiro direito Servo
int s42 = 90; // Levantamento frontal direito Servo

int f    = 0;
int b    = 0;
int l    = 0;
int r    = 0;
int spd  = 3; // Velocidade do movimento de caminhada; quanto maior o número, mais lenta a velocidade
int high = 0; // A altura em que o robô está

// Define os 8 servo motores
Servo myServo1; // Servo do pivô dianteiro esquerdo
Servo myServo2; // Servo de elevação dianteiro esquerdo
Servo myServo3; // Servo do pivô traseiro esquerdo
Servo myServo4; // Servo de elevação traseiro esquerdo
Servo myServo5; // Servo do pivô traseiro direito
Servo myServo6; // Back Right Lift Servo
Servo myServo7; // Servo do pivô dianteiro direito
Servo myServo8; // Servo de elevação dianteiro direito

// Inicia o IR Sensor
int irReceiver = 11;       // Usa pino D12 para Sensor IR
IRrecv irrecv(irReceiver); // Cria uma nova instancia para o Sensor IR
decode_results results;

// Inicia a configuração global
void setup()
{
  // Conecta os servos aos pinos do Arduino
  myServo1.attach(2);
  myServo2.attach(3);
  myServo3.attach(4);
  myServo4.attach(5);
  myServo5.attach(6);
  myServo6.attach(7);
  myServo7.attach(8);
  myServo8.attach(9);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  irrecv.enableIRIn(); // Inicia o receptor de sinais

  Serial.begin (9600);

}

// Inicia o LOOP 
void loop()
{
  unsigned long value;
  unsigned long lastValue;
  
  center_servos();  // Centraliza todos os cervos
  high = 15;        // Configura a altura para 15
  spd = 3;          // Configura a velocidade para 3

  while (1 == 1)    // Loop infinito
  {
    if (irrecv.decode(&results)) // Se tivermos recebido um sinal de infravermelho
    {
      value = results.value;

      if (value == irRepeat)
        value = lastValue;

      switch (value)
      {
        case irUp:
          lastValue = irUp;
          forward();
          break;

        case irDown:
          lastValue = irDown;
          back();
          break;

        case irRight:
          lastValue = irRight;
          turn_right();
          break;

        case irLeft:
          lastValue = irLeft;
          turn_left();
          break;

        case irOK:
          lastValue = irOK;
          break;

        case ir1:
          lastValue = ir1;
          bow();
          break;

        case ir2:
          lastValue = ir2;
          wave();
          break;

        case ir3:
          lastValue = ir3;
          increase_speed();
          break;

        case ir4:
          lastValue = ir4;
          break;

        case ir5:
          lastValue = ir5;
          break;

        case ir6:
          lastValue = ir6;
          decrease_speed();
          break;

        case ir7:
          lastValue = ir7;
          break;

        case ir8:
          lastValue = ir8;
          dance();
          break;

        case ir9:
          lastValue = ir9;
          break;

        case ir0:
          lastValue = ir0;
          center_servos();
          break;

        case irStar:
          lastValue = irStar;
          trim_left();
          break;

        case irPound:
          lastValue = irPound;
          trim_right();
          break;

        default:
          break;
      }

      irrecv.resume(); // Proximo valor
      delay(50); // Pausa de 50 milisegundos antes de executar o próximo movimento

    }
  }

}

void dance()
{
  center_servos();
  delay(100);
  lean_left();
  delay(300);
  lean_right();
  delay(300);
  lean_left();
  delay(300);
  lean_right();
  delay(300);
  lean_left();
  delay(300);
  lean_right();
  delay(300);
  lean_left();
  delay(300);
  lean_right();
  delay(800);
  center_servos();
  delay(300);
  bow();
  center_servos();
}

// Movimento de wave
void wave()
{
  center_servos();
  myServo4.write(45);
  myServo6.write(45);
  delay(200);
  myServo8.write(0);
  delay(200);
  myServo7.write(180);
  delay(200);
  myServo7.write(30);
  delay(300);
  myServo7.write(180);
  delay(300);
  myServo7.write(30);
  delay(300);
  myServo7.write(s41);
  delay(300);
  myServo8.write(s42);
  center_servos();

}

// Movimento bow
void bow()
{
  center_servos();
  delay(200);
  myServo2.write(15);
  myServo8.write(15);
  delay(700);
  myServo2.write(90);
  myServo8.write(90);
  delay(700);
}

// Inclinar-se para a esquerda
void lean_left()
{
  myServo2.write(15);
  myServo4.write(15);
  myServo6.write(150);
  myServo8.write(150);
}

// Inclina-se para a direita
void lean_right()
{
  myServo2.write(150);
  myServo4.write(150);
  myServo6.write(15);
  myServo8.write(15);
}

// Inclinar-se para a esquerda (corte)
void trim_left()
{
  da--;
  db--;
  dc--;
  dd--;
}

// Inclina-se para a direita (cote)
void trim_right()
{
  da++;
  db++;
  dc++;
  dd++;
}

// Avançar (moviento para frente)
void forward()
{
  // Calculo de pontos
  // Pivô dianteiro esquerdo
  a90 = (90 + da),
  a120 = (120 + da),
  a150 = (150 + da),
  a180 = (180 + da);

  // Pivô traseiro esquerdo
  b0 = (0 + db),
  b30 = (30 + db),
  b60 = (60 + db),
  b90 = (90 + db);

  // Pivô traseiro direito
  c90 = (90 + dc),
  c120 = (120 + dc),
  c150 = (150 + dc),
  c180 = (180 + dc);

  // Pivô dianteiro direito
  d0 = (0 + dd),
  d30 = (30 + dd),
  d60 = (60 + dd),
  d90 = (90 + dd);

  // Definir as posições dos servos e as velocidades necessárias para dar um passo à frente
  // (LFP,  LBP, RBP,  RFP, LFL, LBL, RBL, RFL, S1, S2, S3, S4)
  srv(a180, b0 , c120, d60, 42,  33,  33,  42,  1,  3,  1,  1);
  srv( a90, b30, c90,  d30, 6,   33,  33,  42,  3,  1,  1,  1);
  srv( a90, b30, c90,  d30, 42,  33,  33,  42,  3,  1,  1,  1);
  srv(a120, b60, c180, d0,  42,  33,  6,   42,  1,  1,  3,  1);
  srv(a120, b60, c180, d0,  42,  33,  33,  42,  1,  1,  3,  1);
  srv(a150, b90, c150, d90, 42,  33,  33,  6,   1,  1,  1,  3);
  srv(a150, b90, c150, d90, 42,  33,  33,  42,  1,  1,  1,  3);
  srv(a180, b0,  c120, d60, 42,  6,   33,  42,  1,  3,  1,  1);
  //srv(a180, b0,  c120, d60, 42,  15,  33,  42,  1,  3,  1,  1);
  
}

// Movimento de Voltar
void back()
{
  // set servo positions and speeds needed to walk backward one step
  // (LFP,  LBP, RBP,  RFP, LFL, LBL, RBL, RFL, S1, S2, S3, S4)
  srv(180, 0,  120, 60, 42, 33, 33, 42, 3,  1, 1, 1);
  srv(150, 90, 150, 90, 42, 18, 33, 42, 1,  3, 1, 1);
  srv(150, 90, 150, 90, 42, 33, 33, 42, 1,  3, 1, 1);
  srv(120, 60, 180, 0,  42, 33, 33, 6,  1,  1, 1, 3);
  srv(120, 60, 180, 0,  42, 33, 33, 42, 1,  1, 1, 3);
  srv(90,  30, 90,  30, 42, 33, 18, 42, 1,  1, 3, 1);
  srv(90,  30, 90,  30, 42, 33, 33, 42, 1,  1, 3, 1);
  srv(180, 0,  120, 60, 6,  33, 33, 42, 3,  1, 1, 1);

}

// Movimento para a esquerda
void turn_left()
{
  // Definir as posições dos servos e as velocidades necessárias para virar um passo à esquerda
  // (LFP,  LBP, RBP,  RFP, LFL, LBL, RBL, RFL, S1, S2, S3, S4)
  srv(150,  90, 90,  30, 42, 6,  33, 42, 1, 3, 1, 1);
  srv(150,  90, 90,  30, 42, 33, 33, 42, 1, 3, 1, 1);
  srv(120,  60, 180, 0,  42, 33, 6,  42, 1, 1, 3, 1);
  srv(120,  60, 180, 0,  42, 33, 33, 24, 1, 1, 3, 1);
  srv(90,   30, 150, 90, 42, 33, 33, 6,  1, 1, 1, 3);
  srv(90,   30, 150, 90, 42, 33, 33, 42, 1, 1, 1, 3);
  srv(180,  0,  120, 60, 6,  33, 33, 42, 3, 1, 1, 1);
  srv(180,  0,  120, 60, 42, 33, 33, 33, 3, 1, 1, 1);
}

// Movimento para a direita
void turn_right ()
{
  // Definir as posições dos servos e as velocidades necessárias para girar um passo para a direita
  // (LFP,  LBP, RBP,  RFP, LFL, LBL, RBL, RFL, S1, S2, S3, S4)
  srv( 90, 30, 150, 90, 6,  33, 33, 42, 3, 1, 1, 1);
  srv( 90, 30, 150, 90, 42, 33, 33, 42, 3, 1, 1, 1);
  srv(120, 60, 180, 0,  42, 33, 33, 6,  1, 1, 1, 3);
  srv(120, 60, 180, 0,  42, 33, 33, 42, 1, 1, 1, 3);
  srv(150, 90, 90,  30, 42, 33, 6,  42, 1, 1, 3, 1);
  srv(150, 90, 90,  30, 42, 33, 33, 42, 1, 1, 3, 1);
  srv(180, 0,  120, 60, 42, 6,  33, 42, 1, 3, 1, 1);
  srv(180, 0,  120, 60, 42, 33, 33, 42, 1, 3, 1, 1);
}

// Centraliza os Servos Motores
void center_servos()
{
  myServo1.write(90);
  myServo2.write(90);
  myServo3.write(90);
  myServo4.write(90);
  myServo5.write(90);
  myServo6.write(90);
  myServo7.write(90);
  myServo8.write(90);

  int s11 = 90; // Servo do pivô dianteiro esquerdo
  int s12 = 90; // Servo de elevação dianteiro esquerdo
  int s21 = 90; // Servo do pivô traseiro esquerdo
  int s22 = 90; // Servo de elevação traseiro esquerdo
  int s31 = 90; // Servo do pivô traseiro direito
  int s32 = 90; // Servo de elevação traseiro direito
  int s41 = 90; // Servo do pivô dianteiro direito
  int s42 = 90; // Servo de elevação dianteiro direito
}

// Almenta a velocidade
void increase_speed()
{
  if (spd > 3)
    spd--;
}

// Diminui a velocidade
void decrease_speed()
{
  if (spd < 50)
    spd++;
}

// Servos
void srv( int  p11, int p21, int p31, int p41, int p12, int p22, int p32, int p42, int sp1, int sp2, int sp3, int sp4)
{
  /*
  p11: Pivô dianteiro esquerdo do Servo
  p21: Pivô traseiro esquerdo do Servo
  p31: Pivô traseiro direito do Servo
  p41: Pivô dianteiro direito do Servo
  p12: Levantamento frontal esquerdo do Servo
  p22: Levantamento traseiro esquerdo do Servo
  p32: Levantamento traseiro direito do Servo
  p42: Levantamento frontal direito do Servo
  sp1: velocidade 1
  sp2: velocidade 2
  sp3: velocidade 3
  sp4: velocidade 4
  */

  // Multiplicar as posições do servo do elevador pelo ajuste manual da altura
  p12 = p12 + high * 3;
  p22 = p22 + high * 3;
  p32 = p32 + high * 3;
  p42 = p42 + high * 3;

  while ((s11 != p11) || (s21 != p21) || (s31 != p31) || (s41 != p41) || (s12 != p12) || (s22 != p22) || (s32 != p32) || (s42 != p42))
  {
    // Pivô dianteiro esquerdo do Servo
    if (s11 < p11) // se a posição do servo for menor que a posição programada
    {
      if ((s11 + sp1) <= p11)
        s11 = s11 + sp1; // definir a posição do servo igual à posição do servo mais a constante de velocidade
      else
        s11 = p11;
    }

    if (s11 > p11) // se a posição do servo for maior que a posição programada
    {
      if ((s11 - sp1) >= p11)
        s11 = s11 - sp1; // definir a posição do servo igual à posição do servo menos a constante de velocidade
      else
        s11 = p11;
    }

    // Servo do pivô traseiro esquerdo
    if (s21 < p21)
    {
      if ((s21 + sp2) <= p21)
        s21 = s21 + sp2;
      else
        s21 = p21;
    }

    if (s21 > p21)
    {
      if ((s21 - sp2) >= p21)
        s21 = s21 - sp2;
      else
        s21 = p21;
    }

    // Servo do pivô traseiro direito
    if (s31 < p31)
    {
      if ((s31 + sp3) <= p31)
        s31 = s31 + sp3;
      else
        s31 = p31;
    }

    if (s31 > p31)
    {
      if ((s31 - sp3) >= p31)
        s31 = s31 - sp3;
      else
        s31 = p31;
    }

    // Servo do pivô dianteiro direito
    if (s41 < p41)
    {
      if ((s41 + sp4) <= p41)
        s41 = s41 + sp4;
      else
        s41 = p41;
    }

    if (s41 > p41)
    {
      if ((s41 - sp4) >= p41)
        s41 = s41 - sp4;
      else
        s41 = p41;
    }

    // Servo de levantamento dianteiro esquerdo
    if (s12 < p12)
    {
      if ((s12 + sp1) <= p12)
        s12 = s12 + sp1;
      else
        s12 = p12;
    }

    if (s12 > p12)
    {
      if ((s12 - sp1) >= p12)
        s12 = s12 - sp1;
      else
        s12 = p12;
    }

    // Servo de levantamento traseiro esquerdo
    if (s22 < p22)
    {
      if ((s22 + sp2) <= p22)
        s22 = s22 + sp2;
      else
        s22 = p22;
    }

    if (s22 > p22)
    {
      if ((s22 - sp2) >= p22)
        s22 = s22 - sp2;
      else
        s22 = p22;
    }

    // Servo de levantamento traseiro direito
    if (s32 < p32)
    {
      if ((s32 + sp3) <= p32)
        s32 = s32 + sp3;
      else
        s32 = p32;
    }

    if (s32 > p32)
    {
      if ((s32 - sp3) >= p32)
        s32 = s32 - sp3;
      else
        s32 = p32;
    }

    // Servo de levantamento dianteiro direito
    if (s42 < p42)
    {
      if ((s42 + sp4) <= p42)
        s42 = s42 + sp4;
      else
        s42 = p42;
    }

    if (s42 > p42)
    {
      if ((s42 - sp4) >= p42)
        s42 = s42 - sp4;
      else
        s42 = p42;
    }

    // Gravar valores do servo de pivô
    myServo1.write(s11 + da);
    myServo3.write(s21 + db);
    myServo5.write(s31 + dc);
    myServo7.write(s41 + dd);

    // Gravar valores dos servos de elevação
    myServo2.write(s12);
    myServo4.write(s22);
    myServo6.write(s32);
    myServo8.write(s42);

    delay(spd); // Atraso antes do próximo movimento
  }
}

// função USRF 
long get_distance(bool unit)
{

  long duration = 0, 
       cm = 0, 
       inches = 0;
  
  /*
  O sensor é acionado por um pulso HIGH (alto) de 10 ou mais microssegundos.
  Dê um pulso LOW curto antes para garantir um pulso HIGH limpo:
  */
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  /*
  Ler o sinal do sensor: um pulso ALTO cuja
  duração é o tempo (em microssegundos) entre o envio
  do ping até a recepção de seu eco em um objeto.
  */
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  // converter o tempo em uma distância
  cm = (duration / 2) / 29.1;
  inches = (duration / 2) / 74;

  if (unit == INCH)
    return inches;
  else
    return cm;
}
