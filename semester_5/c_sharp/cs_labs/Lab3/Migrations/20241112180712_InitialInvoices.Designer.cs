﻿// <auto-generated />
using System;
using Lab3.Data.Context;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Infrastructure;
using Microsoft.EntityFrameworkCore.Migrations;
using Microsoft.EntityFrameworkCore.Storage.ValueConversion;
using Npgsql.EntityFrameworkCore.PostgreSQL.Metadata;

#nullable disable

namespace Lab3.Migrations
{
    [DbContext(typeof(InvoicesContext))]
    [Migration("20241112180712_InitialInvoices")]
    partial class InitialInvoices
    {
        /// <inheritdoc />
        protected override void BuildTargetModel(ModelBuilder modelBuilder)
        {
#pragma warning disable 612, 618
            modelBuilder
                .HasAnnotation("ProductVersion", "9.0.0-rc.2.24474.1")
                .HasAnnotation("Relational:MaxIdentifierLength", 63);

            NpgsqlModelBuilderExtensions.UseIdentityByDefaultColumns(modelBuilder);

            modelBuilder.Entity("Lab3.Data.Entities.Hotel.Hotel", b =>
                {
                    b.Property<long>("Id")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("bigint");

                    NpgsqlPropertyBuilderExtensions.UseIdentityByDefaultColumn(b.Property<long>("Id"));

                    b.Property<string>("Address")
                        .IsRequired()
                        .HasColumnType("text");

                    b.Property<double>("Area")
                        .HasColumnType("double precision");

                    b.Property<string>("Email")
                        .IsRequired()
                        .HasColumnType("text");

                    b.Property<string>("Name")
                        .IsRequired()
                        .HasColumnType("text");

                    b.Property<long>("OwnerId")
                        .HasColumnType("bigint");

                    b.Property<string>("Phone")
                        .IsRequired()
                        .HasColumnType("text");

                    b.Property<string>("YearOpenedIn")
                        .IsRequired()
                        .HasColumnType("text");

                    b.HasKey("Id");

                    b.HasIndex("OwnerId");

                    b.ToTable("Hotel");
                });

            modelBuilder.Entity("Lab3.Data.Entities.Hotel.Invoices.Fee", b =>
                {
                    b.Property<long>("Id")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("bigint");

                    NpgsqlPropertyBuilderExtensions.UseIdentityByDefaultColumn(b.Property<long>("Id"));

                    b.Property<double>("Cash")
                        .HasColumnType("double precision");

                    b.Property<long>("ClientId")
                        .HasColumnType("bigint");

                    b.Property<DateTime>("CreatedAt")
                        .HasColumnType("timestamp with time zone");

                    b.Property<int>("Type")
                        .HasColumnType("integer");

                    b.HasKey("Id");

                    b.HasIndex("ClientId");

                    b.ToTable("Fees");
                });

            modelBuilder.Entity("Lab3.Data.Entities.Hotel.Invoices.Invoice", b =>
                {
                    b.Property<long>("Id")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("bigint");

                    NpgsqlPropertyBuilderExtensions.UseIdentityByDefaultColumn(b.Property<long>("Id"));

                    b.Property<double>("Cash")
                        .HasColumnType("double precision");

                    b.Property<long>("ClientId")
                        .HasColumnType("bigint");

                    b.Property<DateTime>("CreatedAt")
                        .HasColumnType("timestamp with time zone");

                    b.Property<string>("Discriminator")
                        .IsRequired()
                        .HasMaxLength(21)
                        .HasColumnType("character varying(21)");

                    b.Property<int>("Type")
                        .HasColumnType("integer");

                    b.HasKey("Id");

                    b.HasIndex("ClientId");

                    b.ToTable("Invoices");

                    b.HasDiscriminator().HasValue("Invoice");

                    b.UseTphMappingStrategy();
                });

            modelBuilder.Entity("Lab3.Data.Entities.Hotel.Rooms.RoomFeature", b =>
                {
                    b.Property<long>("Id")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("bigint");

                    NpgsqlPropertyBuilderExtensions.UseIdentityByDefaultColumn(b.Property<long>("Id"));

                    b.Property<string>("Description")
                        .HasColumnType("text");

                    b.Property<string>("Name")
                        .IsRequired()
                        .HasColumnType("text");

                    b.Property<long?>("RoomPropertiesId")
                        .HasColumnType("bigint");

                    b.HasKey("Id");

                    b.HasIndex("RoomPropertiesId");

                    b.ToTable("RoomFeature");
                });

            modelBuilder.Entity("Lab3.Data.Entities.Hotel.Rooms.RoomProperties", b =>
                {
                    b.Property<long>("Id")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("bigint");

                    NpgsqlPropertyBuilderExtensions.UseIdentityByDefaultColumn(b.Property<long>("Id"));

                    b.Property<int>("Class")
                        .HasColumnType("integer");

                    b.Property<long>("HotelId")
                        .HasColumnType("bigint");

                    b.Property<int>("Size")
                        .HasColumnType("integer");

                    b.HasKey("Id");

                    b.HasIndex("HotelId");

                    b.ToTable("RoomProperties");
                });

            modelBuilder.Entity("Lab3.Data.Entities.Hotel.Service", b =>
                {
                    b.Property<long>("Id")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("bigint");

                    NpgsqlPropertyBuilderExtensions.UseIdentityByDefaultColumn(b.Property<long>("Id"));

                    b.Property<double>("AveragePrice")
                        .HasColumnType("double precision");

                    b.Property<string>("Description")
                        .IsRequired()
                        .HasColumnType("text");

                    b.Property<string>("Name")
                        .IsRequired()
                        .HasColumnType("text");

                    b.Property<long?>("ServiceInvoiceId")
                        .HasColumnType("bigint");

                    b.HasKey("Id");

                    b.HasIndex("ServiceInvoiceId");

                    b.ToTable("Service");
                });

            modelBuilder.Entity("Lab3.Data.Entities.Hotel.Stays.Staying", b =>
                {
                    b.Property<long>("Id")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("bigint");

                    NpgsqlPropertyBuilderExtensions.UseIdentityByDefaultColumn(b.Property<long>("Id"));

                    b.Property<DateTime>("CheckedInAt")
                        .HasColumnType("timestamp with time zone");

                    b.Property<DateTime>("CheckedOutAt")
                        .HasColumnType("timestamp with time zone");

                    b.Property<long>("ClientId")
                        .HasColumnType("bigint");

                    b.Property<long>("RoomId")
                        .HasColumnType("bigint");

                    b.HasKey("Id");

                    b.HasIndex("ClientId");

                    b.HasIndex("RoomId");

                    b.ToTable("Staying");
                });

            modelBuilder.Entity("Lab3.Entities.Hotel.People.Client", b =>
                {
                    b.Property<long>("Id")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("bigint");

                    NpgsqlPropertyBuilderExtensions.UseIdentityByDefaultColumn(b.Property<long>("Id"));

                    b.Property<string>("FullName")
                        .IsRequired()
                        .HasColumnType("text");

                    b.Property<long>("HotelId")
                        .HasColumnType("bigint");

                    b.Property<string>("Passport")
                        .IsRequired()
                        .HasColumnType("text");

                    b.HasKey("Id");

                    b.HasIndex("HotelId");

                    b.ToTable("Client");
                });

            modelBuilder.Entity("Lab3.Entities.Hotel.People.Owner", b =>
                {
                    b.Property<long>("Id")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("bigint");

                    NpgsqlPropertyBuilderExtensions.UseIdentityByDefaultColumn(b.Property<long>("Id"));

                    b.Property<string>("FullName")
                        .IsRequired()
                        .HasColumnType("text");

                    b.HasKey("Id");

                    b.ToTable("Owner");
                });

            modelBuilder.Entity("Lab3.Entities.Hotel.Rooms.Room", b =>
                {
                    b.Property<long>("Id")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("bigint");

                    NpgsqlPropertyBuilderExtensions.UseIdentityByDefaultColumn(b.Property<long>("Id"));

                    b.Property<int>("Floor")
                        .HasColumnType("integer");

                    b.Property<long>("PropertiesId")
                        .HasColumnType("bigint");

                    b.Property<long>("RoomNumber")
                        .HasColumnType("bigint");

                    b.HasKey("Id");

                    b.HasIndex("PropertiesId");

                    b.ToTable("Room");
                });

            modelBuilder.Entity("Lab3.Data.Entities.Hotel.Invoices.LivingInvoice", b =>
                {
                    b.HasBaseType("Lab3.Data.Entities.Hotel.Invoices.Invoice");

                    b.Property<long>("StayingId")
                        .HasColumnType("bigint");

                    b.HasIndex("StayingId");

                    b.HasDiscriminator().HasValue("LivingInvoice");
                });

            modelBuilder.Entity("Lab3.Data.Entities.Hotel.Invoices.ServiceInvoice", b =>
                {
                    b.HasBaseType("Lab3.Data.Entities.Hotel.Invoices.Invoice");

                    b.HasDiscriminator().HasValue("ServiceInvoice");
                });

            modelBuilder.Entity("Lab3.Data.Entities.Hotel.Hotel", b =>
                {
                    b.HasOne("Lab3.Entities.Hotel.People.Owner", "Owner")
                        .WithMany("Hotels")
                        .HasForeignKey("OwnerId")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.Navigation("Owner");
                });

            modelBuilder.Entity("Lab3.Data.Entities.Hotel.Invoices.Fee", b =>
                {
                    b.HasOne("Lab3.Entities.Hotel.People.Client", "Client")
                        .WithMany()
                        .HasForeignKey("ClientId")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.Navigation("Client");
                });

            modelBuilder.Entity("Lab3.Data.Entities.Hotel.Invoices.Invoice", b =>
                {
                    b.HasOne("Lab3.Entities.Hotel.People.Client", "Client")
                        .WithMany()
                        .HasForeignKey("ClientId")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.Navigation("Client");
                });

            modelBuilder.Entity("Lab3.Data.Entities.Hotel.Rooms.RoomFeature", b =>
                {
                    b.HasOne("Lab3.Data.Entities.Hotel.Rooms.RoomProperties", null)
                        .WithMany("Features")
                        .HasForeignKey("RoomPropertiesId");
                });

            modelBuilder.Entity("Lab3.Data.Entities.Hotel.Rooms.RoomProperties", b =>
                {
                    b.HasOne("Lab3.Data.Entities.Hotel.Hotel", "Hotel")
                        .WithMany()
                        .HasForeignKey("HotelId")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.Navigation("Hotel");
                });

            modelBuilder.Entity("Lab3.Data.Entities.Hotel.Service", b =>
                {
                    b.HasOne("Lab3.Data.Entities.Hotel.Invoices.ServiceInvoice", null)
                        .WithMany("Services")
                        .HasForeignKey("ServiceInvoiceId");
                });

            modelBuilder.Entity("Lab3.Data.Entities.Hotel.Stays.Staying", b =>
                {
                    b.HasOne("Lab3.Entities.Hotel.People.Client", "Client")
                        .WithMany()
                        .HasForeignKey("ClientId")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.HasOne("Lab3.Entities.Hotel.Rooms.Room", "Room")
                        .WithMany()
                        .HasForeignKey("RoomId")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.Navigation("Client");

                    b.Navigation("Room");
                });

            modelBuilder.Entity("Lab3.Entities.Hotel.People.Client", b =>
                {
                    b.HasOne("Lab3.Data.Entities.Hotel.Hotel", "Hotel")
                        .WithMany()
                        .HasForeignKey("HotelId")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.Navigation("Hotel");
                });

            modelBuilder.Entity("Lab3.Entities.Hotel.Rooms.Room", b =>
                {
                    b.HasOne("Lab3.Data.Entities.Hotel.Rooms.RoomProperties", "Properties")
                        .WithMany()
                        .HasForeignKey("PropertiesId")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.Navigation("Properties");
                });

            modelBuilder.Entity("Lab3.Data.Entities.Hotel.Invoices.LivingInvoice", b =>
                {
                    b.HasOne("Lab3.Data.Entities.Hotel.Stays.Staying", "Staying")
                        .WithMany()
                        .HasForeignKey("StayingId")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.Navigation("Staying");
                });

            modelBuilder.Entity("Lab3.Data.Entities.Hotel.Rooms.RoomProperties", b =>
                {
                    b.Navigation("Features");
                });

            modelBuilder.Entity("Lab3.Entities.Hotel.People.Owner", b =>
                {
                    b.Navigation("Hotels");
                });

            modelBuilder.Entity("Lab3.Data.Entities.Hotel.Invoices.ServiceInvoice", b =>
                {
                    b.Navigation("Services");
                });
#pragma warning restore 612, 618
        }
    }
}