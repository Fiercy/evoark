﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using SGP;

namespace Editor
{
    public partial class Form1 : Form
    {
        CSGP_Direct3D D3D = CSGP_Direct3D.GetInstance();
        CSGP_TextureManager TM = CSGP_TextureManager.GetInstance();

        Random rand = new Random(100);

        Size worldSize = new Size(4, 4);
        Quad[,] world = new Quad[4, 4];
        Size quadSize = new Size(100, 100);
        Quad selected = new Quad(0, 0);


        bool looping = true;

        public bool Looping
        {
            get { return looping; }
            set { looping = value; }
        }

        public Form1()
        {
            InitializeComponent();

            D3D.Initialize(panel1, false);

            TM.Initialize(D3D.Device, D3D.Sprite);

            comboBox1.DataSource = Enum.GetValues(typeof(ObjectSpawn.Object));
            numericUpDownX.Maximum = worldSize.Width * quadSize.Width;
            numericUpDownY.Maximum = worldSize.Height * quadSize.Height;
            //panel1.AutoScroll = true;

            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                {
                    world[i, j] = new Quad();
                    world[i, j].X = i;
                    world[i, j].Y = j;
                    world[i, j].Spawns.Clear();
                }

                    panel1.AutoScrollMinSize = new Size(worldSize.Width * quadSize.Width,
                        worldSize.Height * quadSize.Height);
        }

        public new void Update()
        {

        }

        public void Render()
        {
            Point offset = new Point(0, 0);
            offset.X += panel1.AutoScrollPosition.X;
            offset.Y += panel1.AutoScrollPosition.Y;

            D3D.Clear(panel1, Color.Black);
            D3D.DeviceBegin();
            D3D.SpriteBegin();
            for (int x = 0; x < worldSize.Width; x++ )
            {
                for (int y = 0; y < worldSize.Height; y++)
                {
                    Rectangle rect = Rectangle.Empty;
                    rect.X = x * quadSize.Width;
                    rect.X += panel1.AutoScrollPosition.X;
                    rect.Y = y * quadSize.Height;
                    rect.Y += panel1.AutoScrollPosition.Y;
                    rect.Size = quadSize;

                    D3D.DrawHollowRect(rect, Color.White, 1);

                    for (int z = 0; z < world[x, y].Spawns.Count; z++ )
                    {
                        if(world[x, y].Spawns[z] is ObjectSpawn)
                        {
                            ObjectSpawn oSpawn = (ObjectSpawn)world[x, y].Spawns[z];
                            Rectangle spawnRect = Rectangle.Empty;
                            spawnRect.Width = 20;
                            spawnRect.Height = 20;
                            spawnRect.X = world[x, y].Spawns[z].X + panel1.AutoScrollPosition.X;
                            spawnRect.Y = world[x, y].Spawns[z].Y + panel1.AutoScrollPosition.Y;
                            switch(oSpawn.Obj)
                            {
                                case ObjectSpawn.Object.None:
                                    break;
                                case ObjectSpawn.Object.Player:
                                    D3D.DrawRect(spawnRect, Color.White);
                                    break;
                                case ObjectSpawn.Object.Copperhead:
                                    D3D.DrawRect(spawnRect, Color.Orange);
                                    break;
                                case ObjectSpawn.Object.Cobra:
                                    D3D.DrawRect(spawnRect, Color.Yellow);
                                    break;
                                case ObjectSpawn.Object.Mamba:
                                    D3D.DrawRect(spawnRect, Color.Red);
                                    break;
                                case ObjectSpawn.Object.Coral:
                                    D3D.DrawRect(spawnRect, Color.Pink);
                                    break;
                                case ObjectSpawn.Object.Moccasin:
                                    D3D.DrawRect(spawnRect, Color.Cyan);
                                    break;
                                case ObjectSpawn.Object.Asteroid:
                                    D3D.DrawRect(spawnRect, Color.Gray);
                                    break;
                                case ObjectSpawn.Object.Planet:
                                    D3D.DrawRect(spawnRect, Color.Brown);
                                    break;
                                default:
                                    break;
                            }
                        }
                    }
                }
            }
            if (selected != null)
            {
                Rectangle s = new Rectangle(selected.X * quadSize.Width + panel1.AutoScrollPosition.X,
                    selected.Y * quadSize.Height + panel1.AutoScrollPosition.Y, quadSize.Width, quadSize.Height);
                D3D.DrawHollowRect(s, Color.Cyan, 2);
            }
            D3D.SpriteEnd();
            D3D.DeviceEnd();
            D3D.Present();
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            looping = false;
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void quadWidth_ValueChanged(object sender, EventArgs e)
        {
            int temp = Int32.Parse(quadWidth.Value.ToString());
            quadSize = new Size(temp, quadSize.Height);
            panel1.AutoScrollMinSize = new Size(worldSize.Width * quadSize.Width,
                worldSize.Height * quadSize.Height);
            numericUpDownX.Maximum = worldSize.Width * quadSize.Width;
            numericUpDownY.Maximum = worldSize.Height * quadSize.Height;
        }

        private void quadHeight_ValueChanged(object sender, EventArgs e)
        {
            int temp = Int32.Parse(quadHeight.Value.ToString());
            quadSize = new Size(quadSize.Width, temp);
            panel1.AutoScrollMinSize = new Size(worldSize.Width * quadSize.Width,
                worldSize.Height * quadSize.Height);
            numericUpDownX.Maximum = worldSize.Width * quadSize.Width;
            numericUpDownY.Maximum = worldSize.Height * quadSize.Height;
        }

        private void numRows_ValueChanged(object sender, EventArgs e)
        {
            int temp = Int32.Parse(numRows.Value.ToString());
            
            panel1.AutoScrollMinSize = new Size(worldSize.Width * quadSize.Width,
                temp * quadSize.Height);

            Quad[,] newWorld = new Quad[worldSize.Width, temp];

            for(int i = 0; i < worldSize.Width; i++)
                for(int j = 0; j < temp; j++)
                {
                    if (j < worldSize.Height)
                    {
                        newWorld[i, j] = world[i, j];
                    }
                    else
                        newWorld[i, j] = new Quad(i, j);
                }

            worldSize = new Size(worldSize.Width, temp);
            world = newWorld;
        }

        private void numCols_ValueChanged(object sender, EventArgs e)
        {
            int temp = Int32.Parse(numCols.Value.ToString());
            panel1.AutoScrollMinSize = new Size(worldSize.Width * quadSize.Width,
                worldSize.Height * quadSize.Height);

            Quad[,] newWorld = new Quad[temp, worldSize.Height];

            for (int i = 0; i < temp; i++)
                for (int j = 0; j < worldSize.Height; j++)
                {
                    if (i < worldSize.Width)
                    {
                        newWorld[i, j] = world[i, j];
                    }
                    else
                        newWorld[i, j] = new Quad(i, j);
                }
            worldSize = new Size(temp, worldSize.Height);
            world = newWorld;
        }

        private void panel1_MouseClick(object sender, MouseEventArgs e)
        {
            Point offset = new Point(0, 0);
            offset.X += panel1.AutoScrollPosition.X;
            offset.Y += panel1.AutoScrollPosition.Y;

            if (e.X > worldSize.Width * quadSize.Width ||
                e.Y > worldSize.Height * quadSize.Height)
                return;
            // Calculate the tile in which the mouse click occured.
            selected.X = (e.X - offset.X) / quadSize.Width;
            selected.Y = (e.Y - offset.Y) / quadSize.Height;

            world[selected.X, selected.Y].X = selected.X;
            world[selected.X, selected.Y].Y = selected.Y;

            numericUpDownX.Value = e.X - offset.X;
            numericUpDownY.Value = e.Y - offset.Y;

            listBox1.Items.Clear();

            if (world[selected.X, selected.Y].Spawns.Count != 0)
            {
                for (int i = 0; i < world[selected.X, selected.Y].Spawns.Count; i++)
                {
                    listBox1.Items.Add(world[selected.X, selected.Y].Spawns[i]);
                }
            }
            if(e.Button == MouseButtons.Left)
            {
                for (int i = 0; i < world[selected.X, selected.Y].Spawns.Count; i++)
                {
                    Rectangle r = new Rectangle(
                        world[selected.X, selected.Y].Spawns[i].X,
                        world[selected.X, selected.Y].Spawns[i].Y,
                        world[selected.X, selected.Y].Spawns[i].Width,
                        world[selected.X, selected.Y].Spawns[i].Height);
                    if(r.Contains(e.Location))
                    {
                        listBox1.SelectedIndex = i;
                    }
                }
            }
            // add right click to add objects to grid
            if(e.Button == MouseButtons.Right)
            {
                if (radioButtonObject.Checked == true)
                {
                    Spawn spawn = new ObjectSpawn();
                    if (spawn is ObjectSpawn)
                    {
                        ObjectSpawn oSpawn = new ObjectSpawn();
                        oSpawn.Obj = (ObjectSpawn.Object)comboBox1.SelectedItem;
                        oSpawn.Amount = (int)numericUpDown1.Value;
                        spawn = oSpawn;
                    }
                        spawn.X = e.X - offset.X;
                        spawn.Y = e.Y - offset.Y;
                        spawn.Width = 20;
                        spawn.Height = 20;
                    listBox1.Items.Add(spawn);
                    listBox1.SelectedIndex = world[selected.X, selected.Y].Spawns.Count - 1;
                    world[selected.X, selected.Y].Spawns.Add(spawn);
                }
                else if (radioButtonEvent.Checked == true)
                {
                    Spawn spawn = new EventSpawn();
                    if (spawn is EventSpawn)
                    {
                        EventSpawn eSpawn = new EventSpawn();
                        eSpawn.Evnt = (EventSpawn.Event)comboBox1.SelectedItem;
                        eSpawn.Width = (int)numericUpDownWidth.Value;
                        eSpawn.Height = (int)numericUpDownHeight.Value;
                        spawn = eSpawn;
                    }
                    spawn.X = e.X - offset.X;
                    spawn.Y = e.Y - offset.Y;
                    listBox1.Items.Add(spawn);
                    listBox1.SelectedIndex = world[selected.X, selected.Y].Spawns.Count - 1;
                    world[selected.X, selected.Y].Spawns.Add(spawn);

                }
            }
        }

        private void addEntity_Click(object sender, EventArgs e)
        {
            //Spawn spawn = new Spawn();
            if (radioButtonObject.Checked == true)
            {
                Spawn spawn = new ObjectSpawn();
                if (spawn is ObjectSpawn)
                {
                    ObjectSpawn oSpawn = new ObjectSpawn();
                    oSpawn.Obj = (ObjectSpawn.Object)comboBox1.SelectedItem;
                    oSpawn.Amount = (int)numericUpDown1.Value;
                    spawn = oSpawn;
                    // for now - needs to be updated with object sprites.
                    spawn.Width = 20;
                    spawn.Height = 20;
                }
                if (randomizeCheck.Checked == true)
                {
                    spawn.X = -1;
                    spawn.Y = -1;
                }
                else
                {
                    spawn.X = (int)numericUpDownX.Value;
                    spawn.Y = (int)numericUpDownY.Value;
                }
                listBox1.Items.Add(spawn);
                world[selected.X, selected.Y].Spawns.Add(spawn);
            }
            else if(radioButtonEvent.Checked == true)
            {
                Spawn spawn = new EventSpawn();
                if(spawn is EventSpawn)
                {
                    EventSpawn eSpawn = new EventSpawn();
                    eSpawn.Evnt = (EventSpawn.Event)comboBox1.SelectedItem;
                    eSpawn.Width = (int)numericUpDownWidth.Value;
                    eSpawn.Height = (int)numericUpDownHeight.Value;
                    spawn = eSpawn;
                }
                listBox1.Items.Add(spawn);
                world[selected.X, selected.Y].Spawns.Add(spawn);

            }
            
        }

        private void removeEntity_Click(object sender, EventArgs e)
        {
            if(listBox1.SelectedIndex != -1)
            {
                world[selected.X, selected.Y].Spawns.RemoveAt(listBox1.SelectedIndex);
                listBox1.Items.RemoveAt(listBox1.SelectedIndex);
                listBox1.Update();
            }
        }

        private void radioButtonEvent_Click(object sender, EventArgs e)
        {
            radioButtonObject.Checked = false;
            groupBoxPosition.Enabled = false;
            randomizeCheck.Enabled = false;
            comboBox1.DataSource = Enum.GetValues(typeof(EventSpawn.Event));
            groupBoxSize.Enabled = true;
            numericUpDown1.Enabled = false;
            label1.Text = "Event Type";
        }

        private void radioButtonObject_Click(object sender, EventArgs e)
        {
            radioButtonEvent.Checked = false;
            groupBoxPosition.Enabled = true;
            randomizeCheck.Enabled = true;
            comboBox1.DataSource = Enum.GetValues(typeof(ObjectSpawn.Object));
            groupBoxSize.Enabled = false;
            numericUpDown1.Enabled = true;
            label1.Text = "Object Type";
        }

        private void randomizeCheck_CheckedChanged(object sender, EventArgs e)
        {
            if (randomizeCheck.Checked == true)
            {
                groupBoxPosition.Enabled = false;
            }
            else
                groupBoxPosition.Enabled = true;
        }

        private void radioButtonGenerated_Click(object sender, EventArgs e)
        {
            radioButtonStatic.Checked = false;
        }

        private void radioButtonStatic_Click(object sender, EventArgs e)
        {
            radioButtonGenerated.Checked = false;
        }

        private void collisionCheck_Click(object sender, EventArgs e)
        {
            // possible.
            // make collision rectangles similar to selection boxes.
        }




    }
}
