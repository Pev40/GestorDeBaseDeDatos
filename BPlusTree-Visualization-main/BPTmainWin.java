import java.awt.*;
import java.awt.event.*;

import javax.swing.*;
import javax.swing.border.*;

public class BPTmainWin extends JFrame {

    private final int width = 1000;

    private JPanel contentPane;
    private JButton btnNewButton;
    private JButton btnOrderButton;
    private JButton btnDeleteButton;
    private JPanel drawPanel;
    private JTextField textField;
    private JTextField textField1;
    private JTextField textField2;
    private JLabel listLabel;

    private int order;

    private BPTree tree;
    private Graphics g;

    /**
     * Launch the application.
     */
    public static void main(String[] args) {
        EventQueue.invokeLater(new Runnable() {
            public void run() {
                try {
                    BPTmainWin frame = new BPTmainWin();
                    frame.setVisible(true);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });
    }

    private void customInit() {
        order = 3;
    }

    /**
     * Create the frame.
     */
    public BPTmainWin() {
        customInit();

        addWindowListener(new WindowAdapter() {
            @Override
            public void windowActivated(WindowEvent e) {
                redrawAll();
            }
        });
        setResizable(false);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setBounds(100, 100, width, 500);
        contentPane = new JPanel();
        contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));

        setContentPane(contentPane);
        contentPane.setLayout(new BorderLayout(0, 0));

        drawPanel = new JPanel();
        drawPanel.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                redrawAll();
            }
        });
        drawPanel.setFont(new Font("Tahoma", Font.PLAIN, 10));
        drawPanel.setBorder(new TitledBorder(null, "Tree", TitledBorder.LEADING, TitledBorder.TOP, null, null));
        contentPane.add(drawPanel);
        drawPanel.setLayout(null);

        JPanel leftPanel = new JPanel();
        contentPane.add(leftPanel, BorderLayout.WEST);
        leftPanel.setLayout(new GridLayout(15, 1, 0, 0));

        JPanel bottomPanel = new JPanel();
        contentPane.add(bottomPanel, BorderLayout.SOUTH);
        bottomPanel.setLayout(new FlowLayout());

        listLabel = new JLabel("");
        bottomPanel.add(listLabel);

        JLabel lblNewLabel2 = new JLabel("order");
        lblNewLabel2.setAlignmentX(Component.CENTER_ALIGNMENT);
        leftPanel.add(lblNewLabel2);

        textField1 = new JTextField();
        textField1.setAlignmentX(Component.LEFT_ALIGNMENT);
        textField1.setColumns(8);
        leftPanel.add(textField1);

        btnOrderButton = new JButton("Set");
        btnOrderButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                setOrder();
                enableElements(true);
            }
        });
        leftPanel.add(btnOrderButton);

        JLabel lblNewLabel = new JLabel("add");
        lblNewLabel.setAlignmentX(Component.CENTER_ALIGNMENT);
        leftPanel.add(lblNewLabel);

        textField = new JTextField();
        textField.setAlignmentX(Component.LEFT_ALIGNMENT);
        textField.setColumns(8);
        leftPanel.add(textField);

        btnNewButton = new JButton("Add");
        btnNewButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                addButton();
            }
        });
        leftPanel.add(btnNewButton);

        JLabel lblNewLabel3 = new JLabel("delete");
        lblNewLabel3.setAlignmentX(Component.CENTER_ALIGNMENT);
        leftPanel.add(lblNewLabel3);

        textField2 = new JTextField();
        textField2.setAlignmentX(Component.LEFT_ALIGNMENT);
        textField2.setColumns(8);
        leftPanel.add(textField2);

        btnDeleteButton = new JButton("Delete");
        btnDeleteButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                deleteButton();
            }
        });
        leftPanel.add(btnDeleteButton);
        enableElements(false);
    }

    void setOrder() {
        String msg = textField1.getText();
        if (!validateNumber(msg)) {
            return;
        }
        order = Integer.parseInt(msg);
        drawPanel.setBorder(
                new TitledBorder(null, "Tree, orden:" + msg, TitledBorder.LEADING, TitledBorder.TOP, null, null));

        tree = new BPTree(order);
    }

    void setGraphics() {
        g = drawPanel.getGraphics();
    }

    void clearGraphics() {
        g.clearRect(0, 20, width - 140, 430);
    }

    void drawTree() {
        listLabel.setText("Elements : " + tree.visualizationList());
        
        clearGraphics();
        tree.visualizationTree(g, width);
    }

    void enableElements(boolean b) {
        textField.setEnabled(b);
        btnNewButton.setEnabled(b);
        textField2.setEnabled(b);
        btnDeleteButton.setEnabled(b);
    }

    boolean validateNumber(String s) {
        boolean ok = s.matches("[0-9]+");
        if (!ok) {
            JOptionPane.showMessageDialog(null, "Invalid number!");
        }
        return ok;
    }

    void redrawAll() {
        if (g != null) {
            tree.visualizationTree(g, width);
        }
    }
    
    void addButton() {
        String snum = textField.getText();
        textField.setText("");

        if (!validateNumber(snum)) {
            return;
        }

        setGraphics();
        int num = Integer.parseInt(snum);
        tree.insert(num);
        tree.print();
        drawTree();
    }
    
    void deleteButton() {
        String snum = textField2.getText();
        textField2.setText("");

        if (!validateNumber(snum)) {
            return;
        }

        setGraphics();
        int num = Integer.parseInt(snum);
        tree.delete(num);
        tree.print();
        drawTree();
    }
}
