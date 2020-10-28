void setup();
void loop();

__attribute((weak))
int main()
{
    setup();
    while(1) loop();
}
