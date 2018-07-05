﻿using System;
using System.Windows.Forms;

namespace xrPostprocessEditor
{
    public partial class KeyFrameBox
    {
        private decimal _kfCoef;

        public event EventHandler SelectedIndexChanged;
        public event EventHandler AddButtonClick;
        public event EventHandler RemoveButtonClick;
        public event EventHandler ClearButtonClick;
        public event EventHandler KeyFrameTimeChanged;

        public ContextMenu CopyMenu => btnCopyFrom.Menu;

        public ListBox.ObjectCollection Items => lbKeyFrames.Items;

        public int SelectedIndex
        {
            get => lbKeyFrames.SelectedIndex;
            set => lbKeyFrames.SelectedIndex = value;
        }

        public KeyFrameBox()
        {
            InitializeComponent();
            // Работаем по мотивам ПЫС, нужен коэф для названий в ListBox
            _kfCoef = 0;

            // Завезём обработчики событий
            AddButtonClick += OnAddButtonClick;
            SelectedIndexChanged += OnSelectedIndexChanged;
            RemoveButtonClick += OnRemoveButtonClick;
            ClearButtonClick += OnClearButtonClick;
            KeyFrameTimeChanged += OnKeyFrameTimeChanged;
        }
        public void OnSelectedIndexChanged(object sender, EventArgs e)
        {
            // Временно, для тестов
        }
        public void OnRemoveButtonClick(object sender, EventArgs e)
        {
            try
            {
                int size = lbKeyFrames.Items.Count - 1;
                lbKeyFrames.Items.RemoveAt(size);
            }
            catch(Exception)
            {
                MessageBox.Show("KeyFrames is empty!");
            }
        }
        public void OnKeyFrameTimeChanged(object sender, EventArgs e)
        {

        }
        public void OnClearButtonClick(object sender, EventArgs e)
        {
            lbKeyFrames.Items.Clear();
            _kfCoef = 0;
        }

        public void OnAddButtonClick(object sender, EventArgs e)
        {
            _kfCoef = numKeyFrameTime.Value;
            lbKeyFrames.Items.Add(_kfCoef.ToString());
        }

        private void LbKeyFrames_SelectedIndexChanged(object sender, EventArgs e) => SelectedIndexChanged?.Invoke(this, e);

        public void BtnAdd_Click(object sender, EventArgs e) => AddButtonClick?.Invoke(this, e);

        private void BtnRemove_Click(object sender, EventArgs e) => RemoveButtonClick?.Invoke(this, e);

        private void BtnClear_Click(object sender, EventArgs e) => ClearButtonClick?.Invoke(this, e);

        private void NumKeyFrameTime_ValueChanged(object sender, EventArgs e) => KeyFrameTimeChanged?.Invoke(this, e);
    }
}
