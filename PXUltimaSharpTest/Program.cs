﻿using System;

namespace PXTest
{
    class Hello
    {
        public static void SocketDataSendEvent(ulong pxSocket, byte[] buffer)
        {
            string result = System.Text.Encoding.UTF8.GetString(buffer);

            Console.WriteLine("[C#] Message " + result);
        }

        public static void SocketDataReceiveEvent(ulong pxSocket, byte[] buffer)
        {
            string result = System.Text.Encoding.UTF8.GetString(buffer);

            Console.WriteLine("[C#] Message " + result);
        }

        static void Main(string[] args)
        {

            ///Window window = new Window();

            //window.Create("Test");

#if false

            Console.WriteLine("Test");
            DataStream dataStream = new DataStream();
            ActionResult x = dataStream.MapToMemoryReadOnly("B:/Daten/Hello.txt");
#endif

            PX.Server server = new PX.Server();
            server.OnDataReceive += SocketDataReceiveEvent;
            server.OnDataSend += SocketDataSendEvent;
            server.Start(25565);
            


            while (true)
            {

            }


                /*

            PX.Directory.Create("Hallo i bims");

            Image image = new Image();

            int result = image.Load("B:/Layers.png");

            Console.WriteLine("Result:" + result + "  Width:" + image.Width + "  Height:" + image.Height);
                */
        }
    }
}