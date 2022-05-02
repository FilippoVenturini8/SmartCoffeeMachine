package coffe_machine_manager;

import java.util.ArrayList;
import java.util.List;

import javax.swing.*;

public class CoffeeMachineManager {

	public static void main(String[] args) throws Exception{
		
		SerialCommChannel channel = new SerialCommChannel(args[0],9600);
		System.out.println("Waiting Arduino for rebooting...");		
		Thread.sleep(4000);
		System.out.println("Ready.");	
		
		
		final JFrame frame = new JFrame();
		frame.setTitle("Coffee Machine Manager");
		frame.setSize(750, 500) ;
		frame.setLocationRelativeTo(null);
		
		final JPanel panel = new JPanel();
		
		panel.setLayout(null);
		
		frame.getContentPane().add( panel );
		
		JLabel lblModality = new JLabel("Modality: ");

		JLabel lblTea = new JLabel("Tea: ");
		JLabel lblCoffee = new JLabel("Coffee: ");
		JLabel lblChocolate = new JLabel("Chocolate: ");
		JLabel lblNSelfTest = new JLabel("Self tests: ");
		
		JButton btnRefill = new JButton("Refill");
		JButton btnReset = new JButton("Reset");
		
		lblModality.setBounds(325, 50, 200, 50);
		lblTea.setBounds(325, 100, 100, 50);
		lblCoffee.setBounds(325, 140, 100, 50);
		lblChocolate.setBounds(325, 180, 100, 50);
		lblNSelfTest.setBounds(325, 350, 100, 50);
		btnRefill.setBounds(230, 300, 100, 50);
		btnReset.setBounds(430, 300, 100, 50);
		
		panel.add(lblModality);
		panel.add(lblCoffee);
		panel.add(lblTea);
		panel.add(lblChocolate);
		panel.add(lblNSelfTest);
		panel.add(btnRefill);
		panel.add(btnReset);
		
		frame.setVisible(true);
		
		String lastMsg = "";
		String modality = "";
		String nSelfTest = "";
		String[] quantityList = new String[3];
		String[] splittedMsg; 
		
		while(true) {
			String msg = channel.receiveMsg();
			
			if(!msg.equals(lastMsg) && msg.contains("|")) {
				System.out.println(msg);
				splittedMsg = msg.split("\\|");
				modality = splittedMsg[0];
				nSelfTest = splittedMsg[1];
				quantityList[0] = splittedMsg[2];
				quantityList[1] = splittedMsg[3];
				quantityList[2] = splittedMsg[4];
				lblModality.setText("Modality: "+modality);
				lblTea.setText("Tea: "+quantityList[0]);
				lblCoffee.setText("Coffee: "+quantityList[1]);
				lblChocolate.setText("Chocolate: "+quantityList[2]);
				lblNSelfTest.setText("Self tests: "+nSelfTest);
				lastMsg = msg;

			}
			
			Thread.sleep(50);
		}
		

	}

}
